import 'dart:io';

import 'package:comunicao_de_dados/CodigoLinha.dart';
import 'package:flutter/material.dart';
import 'package:comunicao_de_dados/Grafico.dart';

class Cliente extends StatefulWidget {
  @override
  EstadoCliente createState() => EstadoCliente();
}

class EstadoCliente extends State<Cliente> {
  String entrada = "";
  String entradaCodificada = "";
  var entradaBinaria = "".codeUnits;
  var codificado = <int>[];

  @override
  Widget build(BuildContext context) {
    codificado = CodigoLinha.Codificar(entradaBinaria);
    return Scaffold(
      appBar: AppBar(),
      body: Container(
        alignment: Alignment.center,
        child: ListView(
          children: [
            Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                SizedBox(
                  height: 5,
                ),
                Text("Digite a mensagem: "),
                SizedBox(
                  height: 5,
                ),
                EntradaTexto(),
                SizedBox(
                  height: 20.0,
                ),
                SaidaTexto("Mensagem Criptografada", entrada),
                SaidaTexto("Mensagem em binario", entradaBinaria.toString()),
                SaidaTexto("Código de Linha", codificado.toString()),
                ElevatedButtonEnviarParaSocket(),
                // Grafico(ListIntToListSalesData(entradaBinaria)),
                Grafico(ListIntToListSalesData(codificado))
              ],
            ),
          ],
        ),
      ),
    );
  }

  ElevatedButton ElevatedButtonEnviarParaSocket() {
    return ElevatedButton(
        onPressed: () {
          Socket.connect('127.0.0.1', 4041).then(
            (socket) {
              socket.write(codificado);
            },
          );
        },
        child: Text("enviar"));
  }

  Container EntradaTexto() {
    return Container(
      width: 400.0,
      child: TextField(
        onChanged: (str) {
          var result = encrypt(str, 4);
          setState(
            () {
              entrada = result;
              entradaBinaria = StringParaListaBinaria(entrada);
            },
          );
        },
        decoration: InputDecoration(
            border: OutlineInputBorder(), hintText: 'Enter Text'),
      ),
    );
  }

  Container SaidaTexto(String titulo, String subtitulo) {
    return Container(
      width: 400.0,
      child: ListTile(
        title: Text(titulo),
        subtitle: Text(subtitulo),
      ),
    );
  }

  String encrypt(String text, int s) {
    String result = "";

    for (int i = 0; i < text.length; i++) {
      result += String.fromCharCode(((text.codeUnitAt(i) + s - 32) % 95 + 32));
    }

    return result;
  }
}
