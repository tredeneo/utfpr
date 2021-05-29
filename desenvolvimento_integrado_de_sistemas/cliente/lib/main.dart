import 'package:cliente/telas/PegarArquivo.dart';
import 'package:cliente/telas/inicial.dart';
import 'package:flutter/material.dart';
import 'telas/inicial.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      darkTheme:
          ThemeData(primarySwatch: Colors.blue, brightness: Brightness.dark),
      themeMode: ThemeMode.dark,
      routes: {
        "/": (context) => PaginaInicial(),
        "/PegarArquivo": (context) => PegarArquivo(),
      },
    );
  }
}
