import requests


def requisicao_requests(payload, url):
    headers = {"Content-Type": "application/json"}

    response = requests.request(
        "POST", "http://127.0.0.1:5000" + url, json=payload, headers=headers
    )

    print(response.text)


payload = {"id": "1", "nome": "daniel"}
requisicao_requests(payload, "/cadastrar_usuario")
payload = {"id": "2", "nome": "bianca"}
requisicao_requests(payload, "/cadastrar_usuario")

payload = {
    "criador": "daniel",
    "titulo": "evento 1",
    "local": "evento 1",
    "datas": [{"data": "2020-02-25T14:44:28.534", "votos": 0}],
    "limite": "2022-02-25T14:44:28.534",
    "estado": "andamento",
}
requisicao_requests(payload, "/cadastrar_enquete")

payload = {
    "titulo": "evento 1",
    "usuario": "bianca",
    "datas": [{"data": "2020-02-25T14:44:28.534", "votos": 1}],
}
requisicao_requests(payload, "/votar")
