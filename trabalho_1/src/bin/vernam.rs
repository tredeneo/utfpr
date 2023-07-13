use rand::{distributions::Alphanumeric, Rng};
use std::{env, fs};
use trabalho_1::includes::caracter::Shift;

fn vernam(texto_original: &str, texto_chave: &str, criptografar: bool) -> String {
    let cripto_decripto = if criptografar { 1 } else { -1 };
    texto_original
        .chars()
        .zip(texto_chave.chars())
        .map(|(orignal, chave)| {
            orignal
                .somar_valor(cripto_decripto * chave as isize)
                .unwrap()
        })
        .collect()
}
fn gerar_frase(tamanho: usize) -> String {
    rand::thread_rng()
        .sample_iter(&Alphanumeric)
        .take(tamanho)
        .map(char::from)
        .collect()
}
fn main() {
    let texto = env::args()
        .nth(1)
        .expect("não possue o primeiro argumento (arquivo)");
    let chave = env::args().nth(2);
    let texto_original = fs::read_to_string(texto).expect("nome/caminho do arquivo texto invalido");

    if chave.is_none() {
        let texto_chave = gerar_frase(texto_original.len());
        let texto_cripto = vernam(&texto_original, &texto_chave, true);
        fs::write("chave.dat", texto_chave).expect("erro ao salvar o arquivo da chave");
        fs::write("texto_criptografado.txt", texto_cripto)
            .expect("error ao salvar o arquivo do texto criptografado");
    } else {
        let texto_chave =
            fs::read_to_string(chave.unwrap()).expect("nome/caminho do arquivo de chave invalido");
        let texto_decripto = vernam(&texto_original, &texto_chave, false);
        fs::write("texto_descriptografado.txt", texto_decripto)
            .expect("erro ao salvar arquivo do texto descriptografado");
    }
    // dbg!();
}

#[test]
fn teste_vernam() {
    let lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do\neiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad\nminim veniam, quis nostrud exercitation ullamco laboris nisi ut\naliquip ex ea commodo consequat. Duis aute irure dolor in\nreprehenderit in voluptate velit esse cillum dolore eu fugiat nulla\npariatur. Excepteur sint occaecat cupidatat non proident, sunt in\nculpa qui officia deserunt mollit anim id est laborum.\n";
    let chave = gerar_frase(lorem.len());
    let criptografado = vernam(&lorem, &chave, true);
    let descriptografado = vernam(&criptografado, &chave, false);
    assert_eq!(lorem, descriptografado);
}
