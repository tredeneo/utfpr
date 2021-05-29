import '../api/requisicao.dart'; 
import 'dart:io';
import 'dart:math';

  void processarGanhoSinal(String diretorio) {
    List<String> linhas;
    List<double> matriz;
    linhas = File(diretorio).readAsLinesSync();
    for (var i = 0; i < linhas.length; i++)
      if (linhas[i].contains(",")) {
        linhas = linhas.map((e) => e.replaceAll(",", ".")).toList();
        break;
      }
    try {
      matriz = linhas.map((e) => double.parse(e)).toList();
    } on FormatException catch (e) {
      print("formato invalido $e");
    }

    var contador = 0;
    double gama = 100 + 1 / 20 + 1 * sqrt(1);
    print(matriz.length);
    for (var i = 0; i < matriz.length; i++) {
      if (i % 795 == 0) {
        contador++;
        gama = 100 + 1 / 20 + contador * sqrt(contador);
      }
      matriz[i] = matriz[i] * gama;
    }

    mandarRequisicao(matriz);
      }