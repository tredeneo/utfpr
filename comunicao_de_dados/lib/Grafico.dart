import 'package:flutter/material.dart';
import 'package:syncfusion_flutter_charts/charts.dart';
import 'dart:ui';

class Coordenadas {
  Coordenadas(this.x, this.y);
  final int x;
  final int y;
}

List<Coordenadas> ListIntToListSalesData(List<int> valores) {
  var codificadoData = <Coordenadas>[];
  for (int i = 0; i < valores.length; i++) {
    codificadoData.add(Coordenadas(i, valores[i]));
  }
  return codificadoData;
}

Container Grafico(List<Coordenadas> codificadoData) {
  return Container(
    width: window.physicalSize.width,
    child: SfCartesianChart(
      primaryYAxis:
          NumericAxis(visibleMaximum: 2, visibleMinimum: -2, interval: 1),
      primaryXAxis: NumericAxis(interval: 1),
      series: <ChartSeries>[
        StepLineSeries<Coordenadas, int>(
            width: 5,
            dataSource: codificadoData,
            xValueMapper: (Coordenadas coordenada, _) => coordenada.x,
            yValueMapper: (Coordenadas coordenada, _) => coordenada.y)
      ],
    ),
  );
}
