import 'package:csv/csv.dart';

import 'dart:io';

List<List<double>> pegar_arquivo(String caminho) {
  // var caminho = '../csv/M.csv';
  var arquivo = File(caminho).readAsStringSync();
  var valores_cvs =
      CsvToListConverter(fieldDelimiter: ',', eol: '\n').convert(arquivo);
  var convertendo = valores_cvs
      .map((elemento) =>
          elemento.map((e) => e.toDouble()).cast<double>().toList())
      .toList();
  return convertendo;
}

double convert_double(dynamic e) {
  if (e is String) {
    return double.parse(e);
  } else if (e is int) {
    return e.toDouble();
  } else if (e is double) {
    return e;
  }
}
