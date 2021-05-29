import 'package:file_picker_cross/file_picker_cross.dart';
import 'package:flutter/material.dart';
import '../processamento/GanhoSinal.dart';
import '../processamento/global.dart' as global;

class PegarArquivo extends StatefulWidget {
  @override
  _PegarArquivoState createState() => _PegarArquivoState();
}

class _PegarArquivoState extends State<PegarArquivo> {
  String diretorio = "diretorio invalido";
  List<String> algoritmo = ['ccgn', 'fista'];
  String algoritmoInicial;

  @override
  void initState() {
    super.initState();
    algoritmoInicial = algoritmo.first;
    global.requisicaoSinal.algorithm = algoritmo.first;
    escolherArquivos();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text("gerenciar arquivo"),
        ),
        body: Center(
          child: Container(
            width: MediaQuery.of(context).size.width * 0.40,
            child: Column(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                escolherAlgoritmoDropDownButton(),
                ListTile(
                  leading: Icon(Icons.file_upload),
                    title: Center(child: Text("arquivo escolhida:")),
                    subtitle: Center(child: Text(diretorio ?? "diretorio não escolhido")),
                    isThreeLine: true,),
                ElevatedButton(
                    onPressed: (diretorio == "diretorio invalido")
                        ? null
                        : () {
                            processarGanhoSinal(diretorio);
                            Navigator.pop(context);
                          },
                    child: Text("gerar imagem com o arquivo escolhido"))
              ],
            ),
          ),
        ));
  }

  Widget escolherAlgoritmoDropDownButton() {
    return DropdownButton(
      value: algoritmoInicial,
      style: TextStyle(color: Colors.red, fontSize: 30),
      onChanged: (String newValue) {
        setState(() {
          algoritmoInicial = newValue;
          global.requisicaoSinal.algorithm = newValue;
        });
      },
      items: algoritmo.map((String e) {
        return DropdownMenuItem(
          value: e,
          child: Text(e),
        );
      }).toList(),
    );
  }

  void escolherArquivos() async {
    FilePickerCross filepicker;
    filepicker = await FilePickerCross.importFromStorage(
        type: FileTypeCross.custom, fileExtension: 'txt');

    setState(() {
      diretorio = filepicker.path;
    });
  }
}
