import 'dart:convert';

class CodigoLinha {
  static List<int> Codificar(List<int> codigo) {
    var resultado = <int>[];
    var valores = <int>[];
    bool firstIteration = true;
    int idx = 1;
    codigo.forEach((element) {
      if (firstIteration) {
        resultado.add(element);

        valores.add(element);
        if (element == 0) {
          valores.addAll([1, 0, -1]);
        } else if (element == 1) {
          valores.addAll([0, -1, 0]);
        }
        firstIteration = false;
      } else {
        if (element == 1) {
          resultado.add(valores[idx]);
          idx = (idx + 1) % 4;
        } else if (element == 0) {
          resultado.add(resultado[resultado.length - 1]);
        }
      }
    });
    return resultado;
  }

  static List<int> Decodificar(List<int> codigo) {
    var resultado = <int>[];
    int anterior = 2;
    codigo.forEach((element) {
      if (anterior == 2) {
        resultado.add(element);
        anterior = element;
      } else {
        if (element == anterior) {
          resultado.add(0);
        } else {
          resultado.add(1);
          anterior = element;
        }
      }
    });
    return resultado;
  }
}

List<int> StringParaListaBinaria(String str) {
  //converte a string em uma lista que cada elemento é o numero binario em
  //formato string do caracteres de origem
  //exemplo "tt" vira ["1110100","1110100"]
  print(str);
  var listaBin =
      str.runes.map((e) => e.toRadixString(2).padLeft(7, "0")).toList();

  print("codeUnit : ${str.runes}");

  print("ListBin ${listaBin}");

  //converte a lista de string(numeros binarios) para uma lista em que cada
  // elemento é uma lista q cada elemento é um inteiro do original
  // exemplo: ["010","101"] vira [("0","1","0"),("1","0","1")]
  var listaStr = listaBin
      .map((e) => e.runes.map((char) => String.fromCharCode(char)))
      .toList();

  print("listaStr ${listaStr}");

  //converte cada elemento da lista anterior em inteiro
  var listaInt =
      listaStr.map((e) => e.map((str) => int.parse(str)).toList()).toList();

  print("listaInt ${listaInt}");

  //converte a lista de listas de inteiros em uma unica lista de inteiros
  var codigo = <int>[];
  listaInt.forEach((i) => {
        i.forEach((j) {
          codigo.add(j);
        })
      });

  print("codigo ${codigo}");

  print("codigo len: ${codigo.length}");
  return codigo;
}

String ListaBinariaParaString(List<int> listaBinaria) {
  //pega a lista recebida e converte pra binario
  listaBinaria = CodigoLinha.Decodificar(listaBinaria);
  var listaListaBinaria = <List<int>>[];
  var listaTemporaria = <int>[];
  var contador = 0;

  // pega a lista em binario e seperada cada elemento por 7bits
  //exemplo = [01100010110001] vira [(0110001,0110001)]
  listaBinaria.forEach((element) {
    listaTemporaria.add(element);
    contador++;
    if (contador == 7) {
      listaListaBinaria.add(listaTemporaria.toList());
      listaTemporaria.clear();
      contador = 0;
    }
  });

  //converte a lista em binaria pra um lista com inteiros em ascii
  listaListaBinaria.forEach((element) {
    listaTemporaria.add(int.parse(
        element
            .toString() //remover caracteres incovenientes para a transformação
            .replaceAll(", ", "")
            .replaceAll("[", "")
            .replaceAll("]", ""),
        radix: 2));
  });
  return utf8.decode(listaTemporaria);
}
