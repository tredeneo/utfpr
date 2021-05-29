import 'dart:convert';

Sinal sinalFromJson(String str) => Sinal.fromJson(json.decode(str));

String sinalToJson(Sinal data) => json.encode(data.toJson());

class Sinal {
  Sinal({
    this.token,
    this.signal,
    this.algorithm,
    this.datetime,
  });

  String token;
  List<dynamic> signal;
  String algorithm;
  String datetime;

  factory Sinal.fromJson(Map<String, dynamic> json) => Sinal(
        token: json["token"],
        signal: List<dynamic>.from(json["signal"].map((x) => x)),
        algorithm: json["algorithm"],
        datetime: json["datetime"],
      );

  Map<String, dynamic> toJson() => {
        "token": token,
        "signal": List<dynamic>.from(signal.map((x) => x)),
        "algorithm": algorithm,
        "datetime": datetime,
      };
}
