use rand::Rng;
use trabalho_2::include::{aux, gerador};
use trabalho_2::modelos::usuario_app::UsuarioApp;

const BANCO: &str = "src/banco/app.json";

fn gerar_semente() -> String {
    let semente = rand::thread_rng().gen_range(1000..9999);
    println!("a semente gerada é: {}", &semente);
    semente.to_string()
}

fn main() {
    let menu = aux::input("1 - cadastrar usuario \n2 - gerar senha para usuario");
    let nome = aux::input("nome de usuario");
    let senha_local = sha256::digest(aux::input("senha local"));

    if menu.eq("1") {
        let senha_semente = sha256::digest(aux::input("senha semente"));
        let arquivo = std::fs::read_to_string(BANCO).expect("erro ao ler o arquivo");
        let mut json = match serde_json::from_str::<Vec<UsuarioApp>>(&arquivo) {
            Ok(a) => a,
            _ => Vec::new(),
        };
        if json.iter().filter(|usr| usr.nome.eq(&nome)).count().gt(&0) {
            println!("usuario ja cadastrado");
            return;
        }

        let mut semente_salt = String::new();
        semente_salt.push_str(&senha_semente);
        semente_salt.push_str(&sha256::digest(gerar_semente()));
        let usuario = UsuarioApp {
            nome,
            senha_local,
            semente_salt,
        };
        json.push(usuario);
        let arquivo = serde_json::to_string(&json).expect("erro ao converter pra json");
        std::fs::write(BANCO, arquivo).expect("erro ao salvar o json");
        println!("usuario cadastro com sucesso")
    } else {
        let arquivo = std::fs::read_to_string(BANCO).expect("erro ao ler o arquivo");
        let json = match serde_json::from_str::<Vec<UsuarioApp>>(&arquivo) {
            Ok(a) => a,
            _ => Vec::new(),
        };

        let usuario = json
            .into_iter()
            .filter(|usr| usr.nome.eq(&nome))
            .collect::<Vec<UsuarioApp>>();
        let usuario = usuario.first();
        if usuario.clone().is_none() {
            println!("usuario não cadastrado");
            return;
        }

        let usuario = usuario.unwrap();

        if !usuario.senha_local.eq(&senha_local) {
            println!("senha incorreta");
            return;
        }

        println!("{:?}", gerador::gerar_tokens(&usuario.semente_salt));
    }
}
