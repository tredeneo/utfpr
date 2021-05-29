import 'dart:async';
import 'dart:io';
import 'dart:typed_data';
import 'package:dio/dio.dart';
import 'package:path_provider/path_provider.dart';
import 'package:intl/intl.dart';
import 'package:uuid/uuid.dart';

import '../processamento/global.dart' as global;
import 'modelos/Imagem.dart';
import 'modelos/Status.dart';

void mandarRequisicao(List<double> g) async {
  global.requisicaoSinal.token = Uuid().v1();
  global.requisicaoSinal.signal = g;
  global.requisicaoSinal.datetime =
      DateFormat('yyyy-MM-dd_HH-mm-ss').format(DateTime.now());

  var response = await Dio().post("http://127.0.0.1:8080/post_new_signal",
      data: global.requisicaoSinal.toJson());
  if (response.statusCode == 200) {
    global.requisicaoEnviada = true;
    global.imagemCriada = false;
  }
  global.requisicaoSinal.signal.clear();
}

Future<Status> pegarRequisicao() async {
  var response = await Dio().post("http://127.0.0.1:8080/status_feedback",
      data: global.requisicaoSinal.toJson());
  return Status.fromJson(response.data);
}

Future<Uint8List> pegarImage() async {
  var response = await Dio().post("http://127.0.0.1:8080/get_image",
      data: global.requisicaoSinal.toJson());
  var diretorio = await getDownloadsDirectory();
  global.diretorio = diretorio.path +
      "/cliente_imagens_" +
      global.requisicaoSinal.datetime +
      "_" +
      global.requisicaoSinal.algorithm +
      ".png";
  var imagem = Uint8List.fromList(Imagem.fromJson(response.data).bytes);
  if (!global.imagemCriada) {
    await File(global.diretorio).writeAsBytes(imagem);
    global.imagemCriada = true;
  }

  return imagem;
}
