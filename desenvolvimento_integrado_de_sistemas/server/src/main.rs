#![allow(non_snake_case)]
#[macro_use]
extern crate diesel;

use core::time;
use std::{
    borrow::{Borrow, BorrowMut},
    cell::RefCell,
    sync::{mpsc, Arc, Mutex},
    thread,
};


mod calculo_algoritmos;
use calculo_algoritmos::{ccgn, fista, ler_csv, salvar_img};
// use crate::fista;
// use crate::ler_csv;
// use crate::salvar_img;
use actions::{find_all_requests, find_image, find_signal, insert_new_image, insert_new_signal};
use actix_web::{
    dev::{BodyEncoding, Decompress},
    get, middleware, post,
    rt::System,
    web, App, HttpRequest, HttpResponse, HttpServer, Responder,
};
use chrono::Utc;
use diesel::prelude::*;
use diesel::r2d2::{self, ConnectionManager};
use ndarray::{Array2, Ix2};
use rayon::{ThreadPool, ThreadPoolBuilder};
use serde::{Deserialize, Serialize};

use crate::{actions::update_signal, models::Image};

mod actions;
mod models;
mod schema;

type DbPool = r2d2::Pool<ConnectionManager<SqliteConnection>>;

#[derive(Serialize, Deserialize, Clone, Debug)]
struct SignalRequest {
    #[serde(rename = "token")]
    token: String,
    #[serde(rename = "signal")]
    signal: Vec<f64>,
    #[serde(rename = "algorithm")]
    algorithm: String,
    #[serde(rename = "datetime")]
    datetime: String,
}

#[derive(Serialize, Deserialize, Clone)]
struct SignalResponse {
    #[serde(rename = "token")]
    token: String,
    #[serde(rename = "status")]
    status: String,
}

async fn post_new_signal(
    mut data: web::Data<Data>,
    pool: web::Data<DbPool>,
    req: web::Json<SignalRequest>,
) -> impl Responder {
    let conn = pool.get().expect("couldn't get db connection from pool");

    let sig = models::Signal {
        algorithm: req.algorithm.clone(),
        datetime: req.datetime.clone(),
        status: String::from("Requisição criada."),
        token: req.token.clone(),
    };

    if let Ok(value) = insert_new_signal(sig, &conn) {
        if let Ok(mut mutex) = data.borrow_mut().pool.lock() {
            //.unwrap().push(req.to_owned());
            mutex.push(req.to_owned());
        } else {
            println!("Mutex Error");
        }
    } else {
        println!("Error inserting: {:?}", req.token);
    }

    HttpResponse::Ok()
}

async fn status_feedback(
    mut data: web::Data<Data>,
    pool: web::Data<DbPool>,
    req: web::Json<SignalRequest>,
) -> impl Responder {
    let conn = pool.get().expect("couldn't get db connection from pool");

    let sig = models::Signal {
        algorithm: req.algorithm.clone(),
        datetime: req.datetime.clone(),
        status: String::from("Requisição criada."),
        token: req.token.clone(),
    };

    // let mut signal_result = find_signal(sig, &conn).unwrap().unwrap();

    let mut response = SignalResponse {
        token: String::new(),
        status: String::new(),
    };

    if let Ok(query) = find_signal(sig, &conn) {
        if let Some(query_value) = query {
            response.token = query_value.token;
            response.status = query_value.status;
        } else {
            response.token = String::from("NOT FOUND");
            response.status = String::from("NOT FOUND");
        }
    } else {
        println!("Error in query (find_signal), for: {:?}", req);
    }

    HttpResponse::Ok().json(response)
    // let mut img = find_signal(img_req, &conn).unwrap().unwrap();
}

async fn get_image(
    mut data: web::Data<Data>,
    pool: web::Data<DbPool>,
    req: web::Json<SignalRequest>,
) -> impl Responder {
    let conn = pool.get().expect("couldn't get db connection from pool");

    let sig = models::Signal {
        algorithm: req.algorithm.clone(),
        datetime: req.datetime.clone(),
        status: String::from("Done?"),
        token: req.token.clone(),
    };

    let sig2 = sig.clone();

    if let Ok(query) = find_image(sig, &conn) {
        if let Some(query_value) = query {
            HttpResponse::Ok().json(query_value)
        } else {
            HttpResponse::Ok().json(sig2)
        }
    } else {
        HttpResponse::Ok().json(sig2)
    }
    // let mut img = find_signal(img_req, &conn).unwrap().unwrap();
}

#[derive(Clone)]
struct Data {
    pool: Arc<Mutex<Vec<SignalRequest>>>,
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    std::env::set_var("RUST_LOG", "actix_web=info");
    dotenv::dotenv().ok();

    let connspec = std::env::var("DATABASE_URL").expect("DATABASE_URL");
    let manager = ConnectionManager::<SqliteConnection>::new(connspec);
    let pool = r2d2::Pool::builder()
        .build(manager)
        .expect("Failed to create pool.");

    let mut p = Data {
        pool: Arc::from(Mutex::new(Vec::new())),
    };

    let mut t = p.clone();
    let mut y = pool.clone();

    let (tx, rx) = mpsc::channel();

    let x = thread::spawn(move || {
        let sys = System::new("http-server");

        let srv = HttpServer::new(move || {
            App::new()
                .data(pool.clone())
                .data(p.clone())
                .data(web::JsonConfig::default().limit(1024 * 1024 * 50))
                .route("/post_new_signal", web::post().to(post_new_signal))
                .route("/status_feedback", web::post().to(status_feedback))
                .route("/get_image", web::post().to(get_image))
        })
        .shutdown_timeout(1)
        .bind("127.0.0.1:8080")?
        .run();

        let _ = tx.send(srv);
        sys.run()
    });

    // ALGORITMOS

    let H = ler_csv::pegar_matriz("./csv/H-1.txt");
    //let c = (&H).t().dot(&H).mapv(|a| a.powi(2)).sum().sqrt();
    let c = 0.0000009664557880587876;
    let H_transposta = (&H).clone().reversed_axes();

    let z = thread::spawn(move || {
        let conn = y.get().expect("couldn't get db connection from pool");
        let pool = rayon::ThreadPoolBuilder::new()
            .num_threads(8)
            .build()
            .unwrap();

        rayon::scope(|s| {
            loop {
                if let Ok(mut vec_mutex) = t.pool.borrow_mut().lock() {
                    if let Some(value) = vec_mutex.pop() {
                        s.spawn(|_| {
                            let mut sig = models::Signal {
                                algorithm: value.algorithm.clone(),
                                datetime: value.datetime.clone(),
                                status: String::from("Processando Sinal."),
                                token: value.token.clone(),
                            };

                            if let Ok(query_result) = update_signal(
                                sig.clone(),
                                &y.get().expect("couldn't get db connection from pool"),
                            ) {
                                sig = query_result;
                            }

                            // Use CCGN or FISTA
                            let mut sig_client =
                                Array2::from_elem(Ix2(value.signal.len(), 1), 0 as f64);
                            for i in 0..value.signal.len() {
                                sig_client[[i, 0]] = value.signal[i];
                            }

                            let mut processing_resut: Vec<u8> = Vec::new();
                            if value.algorithm == "ccgn" {
                                processing_resut = ccgn::ccgn(&H, &H_transposta, sig_client);
                            } else if value.algorithm == "fista" {
                                processing_resut = fista::fista(&H, &H_transposta, sig_client, &c);
                            }

                            // END
                            sig.status = String::from("Processo completo.");
                            if let Err(er) = update_signal(
                                sig,
                                &y.get().expect("couldn't get db connection from pool"),
                            ) {
                                println!("Error upadting status, err: {:?}", er);
                            }

                            let img = Image {
                                token: value.token,
                                bytes: processing_resut,
                            };
                            if let Ok(img) = insert_new_image(
                                img,
                                &y.get().expect("couldn't get db connection from pool"),
                            ) {
                                // println!("Image created: {}", img.token);
                            }
                        });
                    }
                }
            }
        });
    });

    // resume accepting new connections

    let srv = rx.recv().unwrap();
    if let Ok(value) = z.join() {
        srv.stop(true);
    }
    if let Ok(value) = x.join() {}

    Ok(())
}
