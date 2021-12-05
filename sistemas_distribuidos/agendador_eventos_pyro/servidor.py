import Pyro4
import threading
import serpent
from typing import List, Dict
from cryptography.hazmat.primitives.asymmetric.ed25519 import Ed25519PublicKey
from cryptography.exceptions import InvalidSignature
import datetime

usuarios: List[Dict] = []
enquetes: List[Dict] = []


@Pyro4.expose
class Servidor(object):
    def cadastrar_usuario(self, nome: str, objeto: object, assinatura: bytes):
        usuario = {
            "nome": nome,
            "usuario": objeto,
            "assinatura": serpent.tobytes(assinatura),
        }
        if usuario not in usuarios:
            usuarios.append(usuario)
            print(f"usuario {nome} cadastrado, total de usuarios:{len(usuarios)}")

    def cadastrar_enquete(self, nome, titulo, local, data, limite):
        """
        cadastra uma enquete nova, foi usado como limite segundos,que pegara
        data e horario atual e somara o limite recebido
        """
        participantes = []
        participantes.append(nome)
        enquete = {
            "nome": nome,
            "titulo": titulo,
            "local": local,
            "data": data,
            "limite": datetime.datetime.now() + datetime.timedelta(seconds=limite),
            "estado": "andamento",
            "participantes": participantes,
        }
        enquetes.append(enquete)

        print(f"enquete {titulo} cadastrado, total de enquetes:{len(enquetes)}")
        """
            notifica os usuarios cadastrados, por ser um busca para n travar o servidor
            sera realizado em uma thread separada
            o primeiro é uma uma funções que que sera executada para verificar os eventos
            que ainda não chegaram no limite para votação

            o segundo, é para notificar todos os usuarios cadastrado que um evento
            foi cadastrado

        """
        threading.Thread(target=consultando_validade).start()
        threading.Thread(
            target=notificar_enquete,
            args=(
                enquete,
                "um novo evento foi cadastrado",
            ),
        ).start()

    def votar(self, nome, titulo, voto):
        """
        contabiliza os voto apenas se o evento estiver em andamento
        """

        for i in range(len(enquetes)):
            if enquetes[i]["titulo"] == titulo:
                if enquetes[i]["estado"] == "andamento":
                    for j in range(len(enquetes[i]["data"])):
                        for k in voto:
                            if enquetes[i]["data"][j]["horario"] == k["horario"]:
                                enquetes[i]["data"][j]["votos"] += 1
                    enquetes[i]["participantes"].append(nome)

    def consulta_enquete(self, nome: str, titulo: str, titulo_assinado: Dict) -> Dict:
        """
        recebe nome, titulo, e titulo assinado, a biblioteca pyro converteu os bytes
        bytes que foi mandanda em um tipo especifico de dicionario de bytes, dai uso
        a mesma biblioteca usado pelo pyro "serpent" para converter de volta a bytes
        """
        titulo_assinado = serpent.tobytes(titulo_assinado)

        for i in usuarios:
            if i["nome"] == nome:
                assinatura = Ed25519PublicKey.from_public_bytes(i["assinatura"])
                try:
                    assinatura.verify(titulo_assinado, titulo.encode())
                    for j in enquetes:
                        if j["titulo"] == titulo:
                            return j
                    return "enquete não encontrada"
                except InvalidSignature:
                    return "assinatura invalida"


def validade():
    atual = datetime.datetime.now()
    for i in range(len(enquetes)):
        if (enquetes[i]["limite"] < atual) or (
            len(enquetes[i]["participantes"]) == len(usuarios)
        ):
            if enquetes[i]["estado"] == "andamento":
                print("entrei validade")
                enquetes[i]["estado"] = "encerrada"
                enquete = enquetes[i]
                mensagem = "uma enquete foi finalizada\n"

                notificar_enquete(enquete, mensagem, True, True)


def notificar_enquete(
    enquete: Dict, mensagem: str, notificar_criador=False, final=False
):
    """
    procura os usuarios cadastrado
    então chama o metodo de usuario para mandar notificação
    caso o boleano seja false, n notificara o criado da enquete(caso do
    momento em que a enquete foi criada)

    """
    for i in usuarios:
        if notificar_criador == False:
            if i["nome"] == enquete["nome"]:
                continue
        usuario = i["usuario"]
        usuario.notificar_enquete(enquete, mensagem, final=final)


def consultando_validade():
    import time

    while True:
        validade()
        time.sleep(5)


def main():
    Pyro4.Daemon.serveSimple({Servidor: "servidor"})


if __name__ == "__main__":
    main()
