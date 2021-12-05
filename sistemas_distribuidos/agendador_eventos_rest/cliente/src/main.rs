use chrono::{self, NaiveDateTime};
use eventsource_client as es;
use futures::{Stream, TryStreamExt};
use std::{str::from_utf8, time::Duration};

use reqwest::Response;
use std::collections::HashMap;
use std::io::stdin;
mod modelos;
use modelos::{Cliente, Enquete};

use crate::modelos::{Datas, Voto};

// em rust para ligar com erros é usado geralmente algum tipo de Enum,
// que pode retornar um erro ou o resultado da função, a função
// unwrap() basicamente pega o resultado e ignora o erro, é equivalente a
// throw ou ignore exceptio em linguagem orietadas a objetos

#[tokio::main]
async fn main() {
    let mut usuario = Cliente::default();
    // se cadastrar em segundo plano e ficar esperando notificação(não trava a main)
    tokio::spawn(novos_eventos());
    let menu = "MENU
        0 - sair
        1 - cadastrar usuario
        2 - cadastrar evento
        3 - consultar evento
        4 - cadastrar voto";
    loop {
        println!("{}", menu);
        let entrada = ler_entrada("escreva uma opção:");
        match entrada.parse::<u8>() {
            Ok(1) => usuario = cadastrar_usuario().await,
            Ok(2) => cadastrar_evento(&usuario).await,
            Ok(3) => consultar_evento().await,
            Ok(4) => votar(&usuario).await,
            Ok(0) => break,
            _ => println!("entrada ou numero invalido"),
        }
    }
}

/// função para ler entrada do teclado, apenas serve pra simplificar o processo
fn ler_entrada(mensagem: &str) -> String {
    println!("{}", mensagem);
    let mut entrada = String::new();
    stdin().read_line(&mut entrada).expect("erro");
    entrada.trim().to_string()
}
async fn consultar_evento() {
    let entrada = ler_entrada("digite o titulo do evento:");
    let map = HashMap::from([("titulo", entrada)]);
    let resposta = requisicao("consultar", map, "get")
        .await
        .unwrap()
        .text()
        .await
        .unwrap();
    let resposta = resposta.trim();
    let evento: Enquete = serde_json::from_str(&resposta).unwrap();
    println!(
        "titulo do evento: {},local:{},datas:",
        evento.titulo, evento.local
    );
    for data in evento.datas {
        println!("datas:{}, votos:{}", data.data, data.votos);
    }
}
async fn cadastrar_usuario() -> Cliente {
    let usuario = Cliente {
        nome: ler_entrada("escreva o nome de usuario"),
    };
    let _ = requisicao("cadastrar_usuario", &usuario, "post").await;
    usuario
}

async fn votar(usuario: &Cliente) {
    let titulo = ler_entrada("escreva o titulo do evento");
    let datas = pegar_datas();
    let voto = Voto {
        usuario: usuario.nome.clone(),
        titulo,
        datas,
    };
    let resposta = requisicao("votar", voto, "post").await.unwrap();
    tokio::spawn(fim_eventos(resposta.text().await.unwrap()));
}

fn pegar_entrada(usuario: &Cliente) -> Enquete {
    let titulo = ler_entrada("digite o titulo");
    let local = ler_entrada("digite o local");
    let entrada = ler_entrada("digite a data limite(dia/mes/ano hora:minutos)");
    let limite = NaiveDateTime::parse_from_str(&entrada, "%d/%m/%Y %H:%M").unwrap();
    let estado = "andamento".to_string();
    let datas = pegar_datas();
    let enviar = Enquete {
        criador: usuario.nome.clone(),
        titulo,
        local,
        limite,
        estado,
        datas,
    };
    enviar
}

fn pegar_datas() -> Vec<Datas> {
    let mut datas: Vec<Datas> = Vec::new();
    let quantidade = ler_entrada("digite a quantidade de datas:")
        .parse::<u8>()
        .unwrap();
    for _i in 0..quantidade {
        let entrada = ler_entrada("digite uma data(dia/mes/ano hora:minuto):");
        let tmp = Datas {
            data: NaiveDateTime::parse_from_str(&entrada, "%d/%m/%Y %H:%M").unwrap(),
            votos: 0,
        };
        datas.push(tmp)
    }
    datas
}

async fn cadastrar_evento(usuario: &Cliente) {
    let enviar: Enquete = pegar_entrada(usuario);
    let resposta = requisicao("cadastrar_enquete", enviar, "post")
        .await
        .unwrap();

    tokio::spawn(fim_eventos(resposta.text().await.unwrap()));
}

/// função generica criada para simplificar o codigo de fazer requisições
/// url: é a rota
/// metodo: é o tipo de requisição get,post
/// json: é o dado que sera enviado na requisição, ele é do tipo gerenerico T
/// o tipo T tem q ter implementado a interface Serialize(interface da biblioteca para serializar)
/// e a interface Sized que implementa tipos que tem tamanho conhecido em tempo de compilação
async fn requisicao<T>(url: &str, json: T, metodo: &str) -> Result<Response, &'static str>
where
    T: serde::ser::Serialize + Sized,
{
    let url = format!("http://127.0.0.1:5000/{}", url);
    let requisicao = reqwest::Client::new();
    if metodo == "get" {
        Ok(requisicao.get(url).json(&json).send().await.unwrap())
    } else if metodo == "post" {
        Ok(requisicao.post(url).json(&json).send().await.unwrap())
    } else {
        Err("deu_ruim")
    }
}

async fn fim_eventos(id: String) {
    let url = format!("http://127.0.0.1:5000/notifica_evento/{}", id);

    let client = es::Client::for_url(url.as_str())
        .unwrap()
        .reconnect(
            es::ReconnectOptions::reconnect(true)
                .retry_initial(false)
                .delay(Duration::from_secs(1))
                .backoff_factor(2)
                .delay_max(Duration::from_secs(60))
                .build(),
        )
        .build();

    let mut stream = Box::pin(mostrar_fim_evento(client));
    while let Ok(Some(_)) = stream.try_next().await {}
}

async fn novos_eventos() {
    let url = "http://127.0.0.1:5000/notificao";

    let client = es::Client::for_url(url)
        .unwrap()
        .reconnect(
            es::ReconnectOptions::reconnect(true)
                .retry_initial(false)
                .delay(Duration::from_secs(1))
                .backoff_factor(2)
                .delay_max(Duration::from_secs(60))
                .build(),
        )
        .build();

    let mut stream = Box::pin(mostrar_novo_evento(client));
    while let Ok(Some(_)) = stream.try_next().await {}
}
fn mostrar_novo_evento(
    client: es::Client<es::HttpsConnector>,
) -> impl Stream<Item = Result<(), ()>> {
    client
        .stream()
        .map_ok(move |event| {
            let tmp = from_utf8(event.field("data").unwrap_or_default()).unwrap_or_default();
            println!("novo evento cadastrado");
            println!("{:?}", tmp);
            println!();
        })
        .map_err(|err| eprintln!("error streaming events: {:?}", err))
}
fn mostrar_fim_evento(
    client: es::Client<es::HttpsConnector>,
) -> impl Stream<Item = Result<(), ()>> {
    client
        .stream()
        .map_ok(move |event| {
            let tmp = from_utf8(event.field("data").unwrap_or_default()).unwrap_or_default();
            println!("evento finalixado");
            println!("{:?}", tmp);
            println!();
        })
        .map_err(|err| eprintln!("error streaming events: {:?}", err))
}
