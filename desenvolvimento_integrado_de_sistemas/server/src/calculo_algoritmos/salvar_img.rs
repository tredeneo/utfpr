use std::{
    fs::File,
    io::{Read, Write},
};


use ndarray::{ArrayBase, Dim, OwnedRepr};
use ndarray_stats::QuantileExt;

pub fn salvar_imagem(mut f: ArrayBase<OwnedRepr<f64>, Dim<[usize; 2]>>) -> Vec<u8> {
    let min = *(f).min().unwrap();
    let max = *(f).max().unwrap();
    // f = ((&f) / (max - min)) * (255 as f64);
    f = &f / (f.mapv(|a| a.powi(2)).sum().sqrt());
    f = f * 1000.0;
    f.par_mapv_inplace(|a| if a > 255.0 { 255.0 } else { a });
    //f.par_mapv_inplace(move |a| ((a-min)/(max-min))*255.0);
    f.par_mapv_inplace(|a| if a < 0.0 { 0.0 } else { a.round() });
    let img = f.into_raw_vec();
    let mut png_output = Vec::new();
    for x in img {
        png_output.push(x.to_string().parse::<u8>().unwrap());
    }

    image::save_buffer(
        "./image.png",
        png_output.as_slice(),
        60,
        60,
        image::ColorType::L8,
    )
    .unwrap();

    let mut result = Vec::new();

    let mut z = File::open("./image.png").unwrap();
    z.read_to_end(&mut result).unwrap();

    return result;
}
