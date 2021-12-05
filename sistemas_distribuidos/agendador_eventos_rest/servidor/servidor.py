import sys
import modelos
import time
import datetime
import json
import redis
import threading
from dataclasses import asdict
from typing import List, Type
from flask import Flask, request
from flask_sse import sse
from flask.wrappers import Response

# indicar pro redis sempre decodificar os dados e usar utf-8 pra isso
red = redis.StrictRedis(charset="utf-8", decode_responses=True)

app = Flask(__name__)
app.config["REDIS_URL"] = "redis://localhost"  # os.environ.get("REDIS_URL")
# url que notificara novos eventos
app.register_blueprint(sse, url_prefix="/notificao")

sys.path.append(".")

usuarios: List[Type[modelos.Usuario]] = []
enquetes: List[Type[modelos.Enquete]] = []

# bloquear thread para evitar condições de corrida(uma variavel ser acessado ao mesmo tempo em lugares diferentes)
lock = threading.Lock()

# roda em sera cadastrado novo ususario
@app.route("/cadastrar_usuario", methods=["POST"])
def cadastrar_usuario():
    usuario = modelos.Usuario(request.get_json())
    usuarios.append(usuario)
    print(f"novo usuario cadastrado, total de {len(usuarios)}")
    return asdict(usuario)


# roda em que sera cadastrado nova enquete
@app.route("/cadastrar_enquete", methods=["POST"])
def cadastrar_enquete():
    enquete = modelos.Enquete(request.get_json())
    enquetes.append(enquete)
    print(f"nova enquete cadastrada, total de {len(enquetes)}")
    # publicar a enquete na url de noticaoção padrão
    sse.publish(json.dumps(asdict(enquete), default=str))
    # iniciar uma thread que ficar procurando se algum evento expirou
    threading.Thread(target=consultando_validade).start()
    return Response(enquete.id)


# rota para votar em um evento dado seu nome e nome de usuario
@app.route("/votar", methods=["POST"])
def votar():
    json = request.get_json()
    for i in range(len(enquetes)):
        if enquetes[i].titulo == json["titulo"]:
            enquetes[i].participantes.append(json["usuario"])
            enquetes[i].votar(json)
            break
    # iniciar thread que verificara q todos os usuarios cadastrados votaram
    threading.Thread(target=consultar_votos, args=(i,)).start()
    return enquetes[i].id


def consultar_votos(i):
    """
    verificar se dado uma enquete(o de indice i) se ela foi votadas por todos os usuarios cadastrados
    tem um sleep aqui apenas parada dar um tempo da requisição de voto ser retornada e o cliente poder se cadastradar
    na url para receber notificação do evento
    """
    time.sleep(2)
    # bloquear as thread para garantir acesso a variavel(global) enquetes
    with lock:
        if len(enquetes[i].participantes) == len(usuarios):
            # publicar que o evento foi finalizado no canal referente ao id do evento
            red.publish(enquetes[i].id, json.dumps(asdict(enquetes[i]), default=str))


@app.route("/consultar", methods=["GET"])
def consulta_enquete():
    json_entrada = request.get_json()
    for i in enquetes:
        if json_entrada["titulo"] == i.titulo:
            return json.dumps(asdict(i), default=str)
    return "invalido"


# url usada pra noticar evento especifico, onde id é o id do evento
# então ocleinte se cadastra na url do evento especifico
@app.route("/notifica_evento/<id>", methods=["GET"])
def notifica_fim_evento(id):
    # comando do flask para evitar conflidos de url,http
    with app.app_context():
        # devolver um "text/event-stream" que é a especificação do SSE, então o cliente ficar esperando
        # o evendo na função "esperar_notiticao"
        return Response(esperar_notificao(id), mimetype="text/event-stream")


def esperar_notificao(id):
    """
    função para receber notificação sobre um evento,o cliente se cadastrado em um canal do redis
    especificamente no canal do id do evento
    """
    pubsub = red.pubsub()
    pubsub.subscribe(id)
    for mensagem in pubsub.listen():
        # puler o evento do tipo subscribe pois é padrão o redis mandar esse vento apos se cadastrar em um canal
        if mensagem["type"] == "subscribe":
            continue
        # como a notificação que o evento foi finalizado sera mandado só uma vez sera usado return em vez de yield
        return f"data: {{'{mensagem['data']}'}}\n event:message\n\n"


def validade():
    with lock:
        atual = datetime.datetime.now()
        andamento = False
        for i in range(len(enquetes)):
            if enquetes[i].limite < atual:
                if enquetes[i].estado == "andamento":
                    enquetes[i].estado = "encerrada"
                    enquete = enquetes[i]
                    red.publish(enquete.id, json.dumps(asdict(enquete), default=str))
            if enquetes[i].estado == "andamento":
                andamento = True
        return andamento


def consultando_validade():
    while True:
        if validade():
            time.sleep(5)
            continue
        return


def main():
    app.run()


if __name__ == "__main__":
    main()
