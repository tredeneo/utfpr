#![allow(unused_imports)]
use sha2::{Digest, Sha256};
use std::time::{SystemTime, UNIX_EPOCH};

pub fn gerar_tokens(hash: &str) -> Vec<String> {
    let mut tokens: Vec<String> = Vec::new();
    let hash = gerar_senhas(hash, pegar_hora_atual());
    let mut senha_atual = hash[0..6].to_string();

    for _ in 0..5 {
        tokens.push(senha_atual.clone());
        let hash_temporario = Sha256::new().chain_update(&senha_atual).finalize();
        senha_atual = format!("{:x}", hash_temporario)[0..6].to_string();
    }
    tokens
}

pub fn pegar_hora_atual() -> u64 {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .expect("erro ao pegar tempo")
        .as_secs()
        / 60
        / 3
}

fn gerar_senhas(semente_salt: &str, hora_atual_em_minutos: u64) -> String {
    use sha2::{Digest, Sha256};
    let cript = Sha256::new()
        .chain_update(semente_salt)
        .chain_update(hora_atual_em_minutos.to_string())
        .finalize();
    format!("{:x}", cript)
}

#[cfg(test)]
#[test]
fn teste_hash_mesmo_minuto() {
    let senha = "123567";
    let minuto_atual = pegar_hora_atual();
    let primeiro_hash = gerar_senhas(&senha, minuto_atual);
    let segundo_hash_mesmo_minuto = gerar_senhas(&senha, minuto_atual);
    let hash_proximo_minuto = gerar_senhas(&senha, minuto_atual + 1);
    let segundo_hash_proximo_minuto = gerar_senhas(&senha, minuto_atual + 1);
    assert_eq!(primeiro_hash, segundo_hash_mesmo_minuto);
    assert_ne!(primeiro_hash, hash_proximo_minuto);
    assert_eq!(hash_proximo_minuto, segundo_hash_proximo_minuto);
}
