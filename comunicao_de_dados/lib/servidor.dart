import 'dart:convert';
import 'dart:io';
import 'package:comunicao_de_dados/CodigoLinha.dart';
import 'package:flutter/material.dart';
import 'package:comunicao_de_dados/Grafico.dart';

class Servidor extends StatefulWidget {
  @override
  EstadoServidor createState() {
    return EstadoServidor();
  }
}

class EstadoServidor extends State<Servidor> {
  String entrada = "";
  String decodificado = "";
  List<int> entradaBin;
  var entradaInteiro = <int>[];

  EstadoServidor() {
    ServerSocket.bind('127.0.0.1', 4041).then((serverSocket) {
      serverSocket.listen((socket) {
        socket.listen((b) {
          setState(() {
            if (b != null)
              entrada = utf8.decode(b).replaceAll(RegExp(r"[\[\]]"), "");
            entradaInteiro =
                entrada.split(",").map((e) => int.parse(e.trim())).toList();
            decodificado = decrypt(ListaBinariaParaString(entradaInteiro), 4);
            entradaBin = StringParaListaBinaria(encrypt(decodificado, 4));
          });
        });
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(),
      body: Container(
        alignment: Alignment.center,
        child: ListView(
          children: [
            Column(
              children: [
                SaidaTexto("Entrada do socket", entrada),
                SaidaTexto("Binário", entradaBin.toString()),
                SaidaTexto("Decodificado", decodificado),
                Grafico(ListIntToListSalesData(entradaInteiro)),
              ],
            ),
          ],
        ),
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

  String decrypt(String text, int s) {
    String result = "";

    for (int i = 0; i < text.length; i++) {
      result += String.fromCharCode(((text.codeUnitAt(i) - s - 32) % 95 + 32));
    }

    return result;
  }

  String encrypt(String text, int s) {
    String result = "";

    for (int i = 0; i < text.length; i++) {
      result += String.fromCharCode(((text.codeUnitAt(i) + s - 32) % 95 + 32));
    }

    return result;
  }
}
