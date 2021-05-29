use ndarray::{ArrayBase, Dim, Ix2, OwnedArcRepr,ArcArray};
use std::{fs::File, io::Read};

pub fn pegar_csv(caminho: &str) -> Vec<Vec<f64>> {
    let mut input = String::new();

    File::open(caminho)
        .unwrap()
        .read_to_string(&mut input)
        .unwrap();

    let csv = input
        .trim()
        .split("\n")
        .map(|x| {
            x.trim()
                .split(",")
                .map(|e| {
                    if e == "0" {
                        return 0 as f64;
                    } else {
                        return e.parse::<f64>().unwrap();
                    }
                })
                .collect::<Vec<f64>>()
        })
        .collect::<Vec<Vec<f64>>>();

    return csv;
}

pub fn pegar_matriz(caminho: &str) -> ArrayBase<OwnedArcRepr<f64>, Dim<[usize; 2]>> {
    let csv = pegar_csv(caminho);

    let height = csv.len();
    let width = csv[0].len();
    let mut array = ArcArray::from_elem(Ix2(height, width), 0 as f64);


    for i in 0..height {
        for j in 0..width {
            array[[i, j]] = csv[i][j];
        }
    }
    return array;
}
