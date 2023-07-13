use std::io;

pub fn input(texto: &str) -> String {
    println!("{texto}");
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).expect("erro ao ler a entrada");

    buffer.trim().to_string()
}
