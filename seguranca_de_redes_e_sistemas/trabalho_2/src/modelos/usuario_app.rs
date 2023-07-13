use serde::{Deserialize, Serialize};

#[derive(Clone, Default, PartialEq, Debug, Serialize, Deserialize)]
pub struct UsuarioApp {
    pub nome: String,         //nome
    pub senha_local: String,  //HASH(senha local)
    pub semente_salt: String, // hahs(hash(semente)+hash(salt))
}
