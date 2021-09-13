import 'package:flutter/material.dart';
import './cliente.dart';
import './servidor.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      darkTheme: ThemeData.dark(),
      themeMode: ThemeMode.system,
      routes: {
        "/": (context) => MyHomePage(title: 'Flutter Demo Home Page'),
        "/cliente": (context) => Cliente(),
        "/servidor": (context) => Servidor(),
      },
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            BotaoCliente(context),
            SizedBox(
              width: 50.0,
            ),
            BotaoServidor(context),
          ],
        ),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }

  ElevatedButton BotaoCliente(BuildContext context) {
    return ElevatedButton(
      style: ButtonStyle(
        minimumSize: MaterialStateProperty.all<Size>(Size(100, 50)),
      ),
      onPressed: () => {Navigator.pushNamed(context, "/cliente")},
      child: Text("Client"),
    );
  }

  ElevatedButton BotaoServidor(BuildContext context) {
    return ElevatedButton(
      style: ButtonStyle(
        minimumSize: MaterialStateProperty.all<Size>(Size(100, 50)),
      ),
      onPressed: () => {Navigator.pushNamed(context, "/servidor")},
      child: Text("Server"),
    );
  }
}
