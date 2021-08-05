import threading
import socket
import os
from pathlib import Path


def tratar(cliente, endereco):
    info = cliente.recv(1024).decode()
    tipo_arquivo = info.split()[1].split(".")[1]
    nome_arquivo = "." + info.split()[1]
    try:
        if tipo_arquivo == "jpg":
            arquivo = open(nome_arquivo, "rb")
            saida = arquivo.read()
            resposta = "HTTP/1.1 200 OK \n"
            resposta += "Content-type: image/jpeg\n"
            cliente.send(resposta.encode())
            cliente.send(saida)
            # cliente.sendfile(arquivo)
            # cliente.send(f"Content-Length:{len(saida)}".encode())
            # for i in range(len(saida)):
            #     cliente.send(saida[i])
            # while saida:
            #     print("ainda")
            #     cliente.send(saida)
            #     saida = arquivo.read(1024)
        else:
            mandar_html(cliente, nome_arquivo, "200")
    except FileNotFoundError:
        print("arquivo não encontrado")
        mandar_html(cliente, "./erro.html", "404")

    except Exception as ex:
        print(f"thread\n{ex}")
    cliente.close()


def mandar_html(cliente, nome, codigo):
    arquivo = open(nome, "r")
    saida = arquivo.read()
    resposta = f"HTTP/1.1 {codigo} OK \n"
    resposta += "Content-type: text/html\n"
    cliente.send(resposta.encode())
    cliente.sendall(saida.encode())
    cliente.close()


if __name__ == "__main__":
    porta = 8094
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
        print(f"main\n{ex}")
    except KeyboardInterrupt:
        print("cabo")
    socket_servidor.close()
