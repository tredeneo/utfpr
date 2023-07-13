use trabalho_2::include::{aux, gerador};
use trabalho_2::modelos::usuario_servidor::UsuarioServidor;

const BANCO: &str = "src/banco/servidor.json";

fn main() {
    let menu = aux::input("1 - cadastrar usuario \n2 - verificar senha para usuario");
    let nome = aux::input("nome de usuario");

    if menu.eq("1") {
        let senha_semente = sha256::digest(aux::input("senha semente"));
        let arquivo = std::fs::read_to_string(BANCO).expect("erro ao ler o arquivo");
        let mut json = match serde_json::from_str::<Vec<UsuarioServidor>>(&arquivo) {
            Ok(a) => a,
            _ => Vec::new(),
        };
        if json.iter().filter(|usr| usr.nome.eq(&nome)).count().gt(&0) {
            println!("usuario ja cadastrado");
            return;
        }

        let semente = sha256::digest(aux::input("digite o salt"));
        let usuario = UsuarioServidor {
            nome,
            senha: senha_semente,
            salt: semente,
        };
        json.push(usuario);
        let arquivo = serde_json::to_string(&json).expect("erro ao converter pra json");
        std::fs::write(BANCO, arquivo).expect("erro ao salvar o json");
        println!("usuario cadastro com sucesso")
    } else {
        let arquivo = std::fs::read_to_string(BANCO).expect("erro ao ler o arquivo");
        let json = match serde_json::from_str::<Vec<UsuarioServidor>>(&arquivo) {
            Ok(a) => a,
            _ => Vec::new(),
        };

        let usuario = json
            .into_iter()
            .filter(|usr| usr.nome.eq(&nome))
            .collect::<Vec<UsuarioServidor>>();
        let usuario = usuario.first();
        if usuario.clone().is_none() {
            println!("usuario não cadastrado");
            return;
        }

        let usuario = usuario.unwrap();

        let mut tmp = String::new();
        tmp.push_str(&usuario.senha);
        tmp.push_str(&usuario.salt);

        let tokens = gerador::gerar_tokens(&tmp);
        let token = aux::input("digite uma senha valida");
        if tokens.iter().any(|tok| tok == &token) {
            println!("senha valida");
            return;
        }
        println!("senha invalida");
    }
}
