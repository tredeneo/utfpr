import threading
import socket
import os
from pathlib import Path


def tratar(cliente, endereco):
    print(f"thread no endereco: {endereco}")
    info = cliente.recv(1024).decode()
    tipo_arquivo = info.split()[1].split(".")[1]
    nome_arquivo = "." + info.split()[1]
    try:
        if tipo_arquivo == "jpg" or tipo_arquivo == "gif":
            mandar_imagem(cliente, nome_arquivo, tipo_arquivo)
        else:
            mandar_html(cliente, nome_arquivo, "200")
    except FileNotFoundError:
        print("arquivo não encontrado")
        mandar_html(cliente, "./erro.html", "404")

    except Exception as ex:
        print(f"erro na thread:\n{ex}")
    cliente.close()


def mandar_imagem(cliente, nome_arquivo, tipo_arquivo):
    arquivo = open(nome_arquivo, "rb").read()
    resposta = "HTTP/1.0 200 OK\n"
    resposta += f"Content-type: image/{tipo_arquivo}\n\n"
    cliente.send(resposta.encode())
    cliente.send(arquivo)


def mandar_html(cliente, nome, codigo):
    arquivo = open(nome, "r")
    saida = arquivo.read()
    resposta = f"HTTP/1.0 {codigo} OK \n"
    resposta += "Content-type: text/html\n"
    cliente.send(resposta.encode())
    cliente.sendall(saida.encode())


if __name__ == "__main__":
    porta = 8095
    print(f"porta: {porta}\n")
    socket_servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket_servidor.bind(("0.0.0.0", porta))
    socket_servidor.listen(5)
    try:
        while True:
            (cliente, endereco) = socket_servidor.accept()
            thread = threading.Thread(target=tratar(cliente, endereco))
            thread.start()
    except Exception as ex:
        print(f"erro na main:\n{ex}")
    except KeyboardInterrupt:
        print("cabo")
    socket_servidor.close()
