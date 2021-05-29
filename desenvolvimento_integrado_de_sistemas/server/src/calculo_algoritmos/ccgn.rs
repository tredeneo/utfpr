#![allow(non_camel_case_types)]

use super::salvar_img;
use ndarray::{ArcArray, Array2, ArrayBase, Dim, Ix2, OwnedRepr};
type matriz = ArrayBase<OwnedRepr<f64>, Dim<[usize; 2]>>;
type matriz_compartilhada = ArcArray<f64, Dim<[usize; 2]>>;

pub fn ccgn(H: &matriz_compartilhada, H_transposta: &matriz_compartilhada, g: matriz) -> Vec<u8> {
    let altura = 60;
    let largura = 60;
    let mut f = Array2::from_elem(Ix2(altura * largura, 1), 0 as f64);
    let mut r = g - &H.dot(&f);
    let mut p = (&H_transposta).dot(&r);
    let mut e: f64;
    let mut rtr;
    loop {
        rtr = (&r).t().dot(&r);
        let alfa = &rtr / ((&p).t().dot(&p));
        f = f + &alfa * &p;
        let mut r_proximo = &r - &alfa * &H.dot(&p);
        let beta = ((&r_proximo).t().dot(&r_proximo)) / &rtr;
        p = (&H_transposta).dot(&r_proximo) + beta * &p;
        let r_aux1 = r.mapv(|a| a.powi(2));
        let r_aux2 = r_proximo.mapv(|a| a.powi(2));
        e = (&r_aux2).sum().sqrt() - (&r_aux1).sum().sqrt();
        r = r_proximo;
        if e > 10f64.powi(-4) {
            break;
        }
    }

    return salvar_img::salvar_imagem(f.clone());
}
