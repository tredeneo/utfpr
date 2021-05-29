import 'dart:async';
import 'dart:typed_data';

import 'package:cliente/api/modelos/Status.dart';
import 'package:flutter/material.dart';
import '../api/requisicao.dart';
import '../processamento/global.dart' as global;

class PaginaInicial extends StatefulWidget {
  @override
  EstadoInicial createState() => EstadoInicial();
}

class EstadoInicial extends State<PaginaInicial> {
  Future<Status> futureSinal;
  Future<Uint8List> futureImagem;
  @override
  void initState() {
    super.initState();
    new Timer.periodic(
      Duration(seconds: 1),
      (Timer t) => setState(() {
        if (global.requisicaoEnviada) {
          futureSinal = pegarRequisicao();
        }
      }),
    );
    new Timer.periodic(
      Duration(seconds: 1),
      (Timer t) => setState(() {
        if (!global.imagemCriada) {
          futureImagem = pegarImage();
        }
      }),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Center(child: Text("cliente de imagem")),
      ),
      body: Center(
        child: Container(
          width: MediaQuery.of(context).size.width * 0.50,
          child: ListView(
            children: [
              Center(
                child: ElevatedButton(
                  onPressed: () {
                    telaPegarArquivo(context);
                  },
                  child: Text("escolher arquivo"),
                ),
              ),
              Card(
                  child: Column(
                children: [mostrarProcesso(), mostrarImagem()],
              )),
            ],
          ),
        ),
      ),
    );
  }

  Card mostrarProcesso() {
    return Card(
      child: FutureBuilder(
          future: futureSinal,
          builder: (context, AsyncSnapshot<Status> snapshot) {
            return Column(children: [
              Center(
                child: Text("processo da imagem"),
              ),
              Center(
                child: (() {
                  if (snapshot.hasData) {
                    return Column(
                      children: [
                        ListTile(
                          leading: Icon(Icons.image),
                          title: Center(
                            child: Text("${snapshot.data.status}" ??
                                "${DateTime.now().second.toString()}"),
                          ),
                        ),
                        ListTile(
                          title: Center(
                            child: Text("arquivo salvo no diretorio:"),
                          ),
                          subtitle: Center(
                            child: Text(global.diretorio),
                          ),
                        ),
                      ],
                    );
                  } else {
                    global.imagemProcessada = false;
                    return Center(child: CircularProgressIndicator());
                  }
                }()),
              ),
            ]);
          }),
    );
  }

  Center mostrarImagem() {
    return Center(
      child: FutureBuilder(
          future: futureImagem,
          builder: (context, AsyncSnapshot<Uint8List> snapshot) {
            if (snapshot.hasData) {
              if (snapshot != null) {
                return Column(
                  children: [
                    Text("imagem previa"),
                    Image.memory(snapshot.data,width: MediaQuery.of(context).size.width * 0.40,fit: BoxFit.fill,filterQuality: FilterQuality.high),
                  ],
                );
              }
            } else {
              return Center(
                  child: Column(
                children: [
                  Text("imagem"),
                  CircularProgressIndicator(),
                ],
              ));
            }
          }),
    );
  }

  void telaPegarArquivo(BuildContext context) {
    Navigator.pushNamed(context, "/PegarArquivo");
  }
}
