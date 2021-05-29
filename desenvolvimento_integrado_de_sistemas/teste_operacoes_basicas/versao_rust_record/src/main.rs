use csv;
use std::time::Instant;
fn main() {
    let start = Instant::now();
    let N = "../csv/N.csv";
    let M = "../csv/M.csv";
    let a = "../csv/a.csv";
    let grande = "../../arquivos/H-1.txt";
    let rdr = csv::ReaderBuilder::new().delimiter(b';').has_headers(false).from_path(grande).unwrap();
    let mut matriz:Vec<Vec<f64>> = Vec::new();
    for record in rdr.into_records().into_iter(){
        let a = record.unwrap().as_slice().split(",").filter_map(|s| {
            if s == "0"{ Some(0.0)}
            else{ s.parse::<f64>().ok()}}).collect::<Vec<f64>>();
        matriz.push(a);
    }
    let tempo = start.elapsed();
    println!("{:?}",tempo)
}
