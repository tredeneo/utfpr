import 'package:ml_linalg/linalg.dart';
import 'package:ml_linalg/matrix.dart';
import 'package:versao_dart/ler_csv.dart' as ler;

void main()   {
  // var tmp =  Matrix.fromList(ler.pegar_arquivo("../../arquivos/H-1.txt"));
  // var ultima = tmp * tmp.transpose() ;
    final m = Matrix.fromList(ler.pegar_arquivo('../csv/M.csv'));
    var n = Matrix.fromList(ler.pegar_arquivo('../csv/N.csv'));
    var a = Matrix.fromList(ler.pegar_arquivo('../csv/a.csv'));
    print(a * m);
    // print(m * a);
    print(m * n);


}
