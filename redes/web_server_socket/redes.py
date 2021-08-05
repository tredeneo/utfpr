import threading
import socket
from pathlib import Path


def tratar(cliente, endereco):
    try:
        info = cliente.recv(1024).decode()
        print(info)
        nome = "." + info.split()[1]
        arquivo = open(nome, "r")
        saida = arquivo.read()
        print(arquivo)
        arquivo.close()
        resposta = "HTTP/1.1 200 OK \n"
        resposta += "Content-type: text/html\n"
        cliente.send(resposta.encode())
        cliente.sendall(saida.encode())
        # for i in range(len(saida)):
        #     cliente.send(saida[i].encode())
    except IsADirectoryError:
        print(f"{IsADirectoryError}")
    except FileNotFoundError:
        print("arquivo não encontrado")
        resposta = "HTTP/1.1 404 OK \n"
        resposta += "Content-type: text/html\n"
    cliente.close()


if __name__ == "__main__":
    socket_servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket_servidor.bind(("0.0.0.0", 8089))
    socket_servidor.listen(5)
    try:
        while True:
            (cliente, endereco) = socket_servidor.accept()
            thread = threading.Thread(target=tratar(cliente, endereco))
            thread.start()
    except KeyboardInterrupt:
        socket_servidor.close()
