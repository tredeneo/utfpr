use serde::{Deserialize, Serialize};
#[derive(Debug, Deserialize, Serialize)]
pub struct UsuarioServidor {
    pub nome: String,
    pub senha: String, //(HASH(SenhaSemente)
    pub salt: String,  //(HASH(salt))
}
