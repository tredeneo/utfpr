import 'dart:convert';

Status statusFromJson(String str) => Status.fromJson(json.decode(str));

String statusToJson(Status data) => json.encode(data.toJson());

class Status {
    Status({
        this.token,
        this.status,
    });

    String token;
    String status;

    factory Status.fromJson(Map<String, dynamic> json) => Status(
        token: json["token"],
        status: json["status"],
    );

    Map<String, dynamic> toJson() => {
        "token": token,
        "status": status,
    };
}