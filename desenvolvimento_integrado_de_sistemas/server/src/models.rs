use serde::{Deserialize, Serialize};

use crate::schema::images;
use crate::schema::signals;

#[derive(Debug, Clone, Serialize, Deserialize, Queryable, Insertable)]
pub struct Signal {
    pub token: String,
    pub algorithm: String,
    pub datetime: String,
    pub status: String,
}

#[derive(Debug, Clone, Serialize, Deserialize, Queryable, Insertable)]
pub struct Image {
    pub token: String,
    pub bytes: Vec<u8>,
}
