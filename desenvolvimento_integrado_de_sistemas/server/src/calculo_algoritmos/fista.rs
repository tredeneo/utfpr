#![allow(non_camel_case_types)]
#![allow(unused_variables)]

use super::salvar_img;
use ndarray::{ArcArray, Array2, ArrayBase, Dim, Ix2, OwnedRepr};
use ndarray_stats::QuantileExt;
type matriz = ArrayBase<OwnedRepr<f64>, Dim<[usize; 2]>>;
type matriz_compartilhada = ArcArray<f64, Dim<[usize; 2]>>;

pub fn fista(
    H: &matriz_compartilhada,
    H_transposta: &matriz_compartilhada,
    g: matriz,
    c: &f64,
) -> Vec<u8> {
    let altura = 60;
    let largura = 60;
    let mut f = Array2::from_elem(Ix2(altura * largura, 1), 0 as f64);
    let mut ultimo_f = Array2::from_elem(Ix2(altura * largura, 1), 0 as f64);
    let mut aux = (&H_transposta).dot(&g);
    aux.par_mapv_inplace(|a| a.abs());
    let lambda = aux.max().unwrap() * 0.1;
    let mut y = Array2::from_elem(Ix2(altura * largura, 1), 0 as f64);
    let mut a = 1.0;
    let mut ultimo_a = 1.0;
    println!("Lambda: {}", lambda);
    for _ in 0..4 {
        f = reducao(
            lambda / c,
            &y + (((1.0 / c) * (H_transposta)).dot(&(&g - (H).dot(&y)))),
        );
        a = (1.0 + (1.0 + 4.0 * (&a * &a) as f64).sqrt()) / 2.0;
        y = &f + ((&ultimo_a - 1.0) / &a) * (&f - &ultimo_f);
        ultimo_a = a;
        ultimo_f = f.clone();
    }

    return salvar_img::salvar_imagem(f.clone());
}
fn reducao(a: f64, mut array: matriz) -> matriz {
    let a_gambiarra = a / 5.0;
    array.par_mapv_inplace(move |i| {
        if i >= 0.0 {
            if i - a_gambiarra >= 0.0 {
                i - a_gambiarra
            } else {
                0.0
            }
        } else {
            i - a_gambiarra
        }
    });
    return array;
}
