use std::collections::HashMap;

static FREQUENCIA_PORTUGUES: [(char, f32); 10] = [
    ('a', 14.63),
    ('e', 12.57),
    ('i', 6.18),
    ('o', 10.73),
    ('u', 4.63),
    ('s', 7.81), // aq ja da
    ('r', 6.53),
    ('n', 5.05),
    ('d', 4.99),
    ('m', 4.74),
];
// FREQUENCIA: H
const ALFABETO: &str = "abcdefghijklmnopqrstuvwxyz";
use std::{env, fs};
fn porcentagem(atual: i32, total: &f32) -> f32 {
    //trucar o valor de float pra uma casa decimal
    f32::trunc(((atual as f32 / *total) * 100.0) * 100.0) / 100.0
}

mod cesar;
fn contar_frequencia(texto: &str) -> HashMap<char, f32> {
    let mut verificados = HashMap::new();
    for i in texto.chars() {
        if i.is_alphanumeric() {
            verificados.entry(i).and_modify(|f| *f += 1).or_insert(1);
        }
    }
    let total = verificados.values().sum::<i32>() as f32;
    verificados
        .iter()
        .map(|(&chave, &valor)| (chave, porcentagem(valor, &total)))
        .collect()
}

fn diff(texto: &str) -> f64 {
    let frequencia = HashMap::from(FREQUENCIA_PORTUGUES);
    let calculado = contar_frequencia(texto);
    let diff_total: f64 = ALFABETO
        .chars()
        .map(|ch| {
            let frequencia_texto = calculado.get(&ch).unwrap_or(&0.0);
            let frequencia_portugues = frequencia.get(&ch).unwrap_or(&0.0);
            let diferenca_absoluta = ((frequencia_texto - frequencia_portugues) as f64).abs();
            diferenca_absoluta
        })
        .sum();
    diff_total

    // }
}
// https://medium.com/@momohakarish/caesar-cipher-and-frequency-analysis-with-python-635b04e0186f
fn quebrar_cifra(texto: &str) -> usize {
    let mut menor_diff = f64::MAX;
    let mut chave_final = 0;
    for chave_atual in 0..=ALFABETO.len() {
        let atual_texto = cesar::cifra_cesar(texto, -(chave_atual as isize));
        let atual_diff = diff(&atual_texto);
        if atual_diff < menor_diff {
            menor_diff = atual_diff;
            chave_final = chave_atual;
        }
    }
    println!("a chave para descriptografar provalmente é {}", chave_final);
    chave_final
}

fn ordernar_frequencia(frequencia: &HashMap<char, f32>) {
    let mut tmp = frequencia
        .iter()
        .map(|(&chave, &valor)| (chave, valor))
        .collect::<Vec<_>>();
    tmp.sort_by(|&(_, a), &(_, b)| b.partial_cmp(&a).unwrap());
    tmp.iter()
        .for_each(|(letra, quantidade)| println!("{} {}", letra, quantidade));
}
fn main() {
    let nome_arquivo = env::args()
        .nth(1)
        .expect("não possue o primeiro argumento (arquivo)");
    let texto = fs::read_to_string(nome_arquivo).expect("nome/caminho do arquivo invalido");
    let calculado = contar_frequencia(&texto);
    ordernar_frequencia(&calculado);
    let chave = quebrar_cifra(&texto) as isize * -1;
    fs::write(
        "original_descriptografado",
        cesar::cifra_cesar(&texto, chave),
    ).expect("erro ao salvar o arquivo_descriptografado");
}

#[test]
fn teste_analisador() {
    let lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do\neiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad\nminim veniam, quis nostrud exercitation ullamco laboris nisi ut\naliquip ex ea commodo consequat. Duis aute irure dolor in\nreprehenderit in voluptate velit esse cillum dolore eu fugiat nulla\npariatur. Excepteur sint occaecat cupidatat non proident, sunt in\nculpa qui officia deserunt mollit anim id est laborum.\n";
    let valor = 4;
    let criptografado = cesar::cifra_cesar(&lorem, valor);
    let chave = quebrar_cifra(&criptografado) as isize;
    assert_eq!(valor, chave);
}
