use trabalho_1::includes::caracter::Shift;
use std::{env,fs};
pub fn cifra_cesar(texto: &str, valor: isize) -> String {
        texto
            .chars()
            .map(|c| c.somar_valor(valor).expect("ocorreu um erro ao adicionar o caracter"))
            .collect()
}

fn main() {
    let nome_arquivo = env::args().nth(1).expect("não possue o primeiro argumento (arquivo)");
    let chave = env::args().nth(2).expect("não possui o segundo argumento (chave)").parse::<isize>().expect("segundo argumento não é um numero inteiro");
    
    let texto = fs::read_to_string(nome_arquivo).expect("nome/caminho do arquivo invalido");
    println!("{}",cifra_cesar(&texto,chave));

}

#[test]
fn cifra_cesar_test() {
    let ultimos = "z Z 9";
    let primeiros = "0 a A";
    assert!(primeiros == cifra_cesar(ultimos, 1));
    assert!(ultimos == cifra_cesar(primeiros, -1));
    // assert!(ultimos == cifra_cesar(primeiros, -1));
}
