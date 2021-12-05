from cryptography.hazmat.primitives.asymmetric.ed25519 import Ed25519PrivateKey
import Pyro4
from cryptography.hazmat.primitives import serialization
from typing import Dict
import datetime
import sys

Pyro4.config.DETAILED_TRACEBACK = True
sys.excepthook = Pyro4.util.excepthook


@Pyro4.expose
@Pyro4.callback
class Usuario(object):
    def __init__(self):
        self.publica, self.privada = self.chaves()
        self.nome = None

    def chaves(self):
        """
        criação das chaves, para poder passar a chave publica
        para o servidor sera passada como bytes,
        então ja foi armezanado como bytes
        """
        privada = Ed25519PrivateKey.generate()
        publica = privada.public_key().public_bytes(
            encoding=serialization.Encoding.Raw,
            format=serialization.PublicFormat.Raw,
        )
        return publica, privada

    def cadastrar(self, servidor):
        """
        criação do usuario
        """
        nome = ""
        while True:
            nome = input("digite o nome de Usuario:")
            if len(nome) == 0:
                print("nome invalido")
            else:
                break

        self.nome = nome
        try:
            servidor.cadastrar_usuario(self.nome, self, self.publica)

        except Exception as ex:
            print(f"erro ao cadastrar:{ex}")

    def notificar_enquete(self, enquete: Dict, mensagem: str, final=False):
        """
        metodo chamado pelo servidor quando o servidor armazena uma nova enquete
        """
        if final:
            maior = 0
            data = None
            for i in enquete["data"]:
                if i["votos"] > maior:
                    data = i["horario"]
                    maior = i["votos"]
            if maior == 0:
                evento = (
                    f"\n{mensagem}"
                    f"titulo:{enquete['titulo']}\nlocal:{enquete['local']}\n"
                    "ninguem votou em algum horario"
                )
            else:
                evento = (
                    f"\n{mensagem}"
                    f"titulo:{enquete['titulo']}\nlocal:{enquete['local']}\n"
                    f"o horario mais votado foi:{data}"
                )
        else:
            evento = (
                f"\n{mensagem}\n"
                f'titulo:{enquete["titulo"]}\nlocal:{enquete["local"]}\n'
                f"datas:{enquete['data']}"
            )
        print(evento)

    def cadastrar_enquete(self, servidor):
        titulo = input("digite o titulo da enquete:")
        local = input("digite o local do evento:")
        quantidade = int(input("digite quantos horarios quer cadastrar:"))
        horarios = []
        for i in range(quantidade):
            data = input("digite a data do evento(dia/mes/ano)   ")
            dia, mes, ano = map(int, data.split("/"))
            horario = input("digite o horario do evento(hora:minutos)   ")
            hora, minuto = map(int, horario.split(":"))
            horarios.append(
                {"horario": datetime.datetime(ano, mes, dia, hora, minuto), "votos": 0}
            )

        limite = int(input("digite o tempo limite para votar na enquete:"))
        servidor.cadastrar_enquete(self.nome, titulo, local, horarios, limite)

    def consulta_enquete(self, servidor):
        """
        pegar a entrada o titulo que o usuario quer saber,
        e mandar o titulo e o titulo assinado ao servidor
        """
        titulo = input("digite o titulo para fazer uma busca:")
        assinatura = self.privada.sign(titulo.encode())
        try:
            resultado = servidor.consulta_enquete(self.nome, titulo, assinatura)
        except Exception as ex:
            print(f"ex:{ex}")
            resultado = "ouve um erro na busca"
        if type(resultado) is dict:
            horarios = resultado["data"]
            print(f"\n o estado atual é {resultado['estado']}")
            print("datas:")
            for i in range(len(horarios)):
                print(f"data:{horarios[i]['horario']},votos:{horarios[i]['votos']}")
        else:
            print(resultado)

    def votar(self, servidor):
        """
        votar se participara ou não de um evento
        """
        titulo = input("digite o titulo do evento:")
        quantidade = int(input("digite quanto horarios quer confirmar:"))
        horarios = []
        for i in range(quantidade):
            data = input("digite a data do evento(dia/mes/ano)   ")
            dia, mes, ano = map(int, data.split("/"))
            horario = input("digite o horario do evento(hora:minutos)   ")
            hora, minuto = map(int, horario.split(":"))
            horarios.append({"horario": datetime.datetime(ano, mes, dia, hora, minuto)})

        servidor.votar(self.nome, titulo, horarios)
