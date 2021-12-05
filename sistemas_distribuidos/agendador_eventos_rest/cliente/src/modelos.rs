use chrono::NaiveDateTime;
use serde::{de, Deserialize, Deserializer, Serialize};

// a indicação "Debug" é para poder mostrar nos print,log,debug
// a indicação "Default" é para quando criar um novo, definir os valores padrões
// se for um int sera 0 se for string se string vazia...
#[derive(Debug, Deserialize, Serialize)]
pub struct Enquete {
    pub criador: String,
    pub titulo: String,
    pub local: String,
    pub datas: Vec<Datas>,
    #[serde(deserialize_with = "naive_date_time_from_str")]
    pub limite: NaiveDateTime,
    pub estado: String,
}

#[derive(Debug, Deserialize, Serialize)]
pub struct Datas {
    #[serde(deserialize_with = "naive_date_time_from_str")]
    pub data: NaiveDateTime,
    pub votos: u32,
}

#[derive(Debug, Serialize)]
pub struct Voto {
    pub usuario: String,
    pub titulo: String,
    pub datas: Vec<Datas>,
}

#[derive(Default, Debug, Serialize, Deserialize)]
pub struct Cliente {
    pub nome: String,
}

fn naive_date_time_from_str<'de, D>(deserializer: D) -> Result<NaiveDateTime, D::Error>
where
    D: Deserializer<'de>,
{
    let s: String = Deserialize::deserialize(deserializer)?;
    NaiveDateTime::parse_from_str(&s, "%Y-%m-%d %H:%M:%S").map_err(de::Error::custom)
}
