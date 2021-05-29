import 'dart:convert';


Imagem imagemFromJson(String str) => Imagem.fromJson(json.decode(str));

String imagemToJson(Imagem data) => json.encode(data.toJson());

class Imagem {
    Imagem({
        this.token,
        this.bytes,
    });

    String token;
    List<int> bytes;

    factory Imagem.fromJson(Map<String, dynamic> json) => Imagem(
        token: json["token"],
        bytes: List<int>.from(json["bytes"].map((x) => x)),
    );

    Map<String, dynamic> toJson() => {
        "token": token,
        "bytes": List<dynamic>.from(bytes.map((x) => x)),
    };
}