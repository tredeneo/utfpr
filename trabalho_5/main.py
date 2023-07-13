import socket
import threading
import logging.handlers
import re
import hashlib


syslog_handler = logging.handlers.SysLogHandler(
    address=('10.181.28.70', 514))
logger = logging.getLogger()
logger.addHandler(syslog_handler)
logger.setLevel(logging.INFO)
tmp = True


def log(message):
    texto = f"Proxy - {message}"
    print(texto)
    logger.info(texto)


def mandar_requisicao(source, destination):
    try:
        while True:
            data = source.recv(4096)
            if not data:
                break
            destination.sendall(data)
    except :
        pass
    finally:
        for i in [source,destination]:
            try:
                i.close()
            except:
                pass
            
response_body = '''
    <html>
        <head>
            <meta charset="UTF-8">
            <title>Exemplo de resposta HTTP </title>
        </head>
        <body>
            <h1>erro 403</h1>
            <h2>Acesso não autorizado! </h2>
        </body>
    </html>
'''
response_body = response_body.encode('utf-8')
header = f'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: {len(response_body)}\r\n\r\n'.encode('utf-8')
RESPONSE = header + response_body


def process_client(client_socket, client_address):
    try:
        # Receber requisição HTTP do cliente
        request = client_socket.recv(4096)

        # Armazenar a requisição em um bloco de bytes
        request_lines = request.split(b'\n')
        http_request_line = request_lines[0].decode()

        # Verificar se a palavra "monitorando" está no objeto requisitado
        if b"monitorando" in request:
            client_socket.sendall(RESPONSE)

            # Log para o servidor SysLog
            log(f"requisição {client_address} bloqueada por conter")
        else:
            # Parse da requisição HTTP
            match = re.match(r'([A-Z]+) (\S+) HTTP/1.[01]', http_request_line)
            if match:
                method, url = match.groups()
                if method == 'CONNECT':
                    redirecionar_https(client_socket,client_address,url)
                elif method== "GET":
                    redirecionar_http(client_socket,client_address,url,request)
            else:
                client_socket.send(b'HTTP/1.1 400 Bad Request\r\n\r\n')
    except Exception as exp:
        log(f"exceção lançada: {exp}")
    finally:
        client_socket.close()



def encaminhar_requisicao_servidor(destination_host,dest_port,client_address):
    destination_socket = socket.socket(
        socket.AF_INET, socket.SOCK_STREAM)
    destination_socket.connect((destination_host, int(dest_port)))
    ip, port = destination_socket.getpeername()
    log(
    f"Nova requisição cliente:{client_address}  servidor ('{ip}', {port})'")
    return destination_socket


def redirecionar_http(client_socket, client_address,url,request):
    # Extrair o hostname do URL
    destination_host = url.split('/')[2]
    port = 80
    destination_socket = encaminhar_requisicao_servidor(destination_host,port,client_address)
    destination_socket.sendall(request)
    buffer = b""
    try:
        while True:
            data = destination_socket.recv(8196)
            if not data:
                break
            buffer += (data)
            client_socket.sendall(data)
    except :
        pass

    destination_socket.close()

    status_code = (buffer).decode().split()[1]
    print(status_code)
    log(
        f"resposta : Client: {client_address}, Server: {destination_host}, Status Code: {status_code}")



def redirecionar_https(client_socket, client_address,url):
    destination_host, port  = url.split(":")

    destination_socket = encaminhar_requisicao_servidor(destination_host,port,client_address)

    # Inform the client that a tunnel has been established
    client_socket.sendall(
        b'HTTP/1.1 200 Connection Established\r\n\r\n')

    # Forward bytes between client and destination
    client_to_destination = threading.Thread(
        target=mandar_requisicao, args=(client_socket, destination_socket))
    destination_to_client = threading.Thread(
        target=mandar_requisicao, args=(destination_socket, client_socket))
    client_to_destination.start()
    destination_to_client.start()
    client_to_destination.join()
    destination_to_client.join()

#gerar com :  
# sha256sum main_original.py | awk '{ print $1 }' > hash.tx
def teste_integridade():
    log("teste de integridade:")
    with open('hash.txt', 'r') as f:
        orig_hash = f.read().strip()
        with open('main_original.py', 'rb') as curr_f:
            curr_hash= hashlib.sha256(curr_f.read()).hexdigest()
        log(f"hash atual {curr_hash}")
        log(f"hash original {orig_hash}")
        if orig_hash == curr_hash:
            log("hash correto")
        else:
            log("hash_incorreto")
            exit()


def main():
    teste_integridade()
    server=socket.socket()
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    final = input("digite a numero final do ip 127.0.0.")
    #server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((f'127.0.0.{final}', 8081))
    server.listen(5)

    log(f"proxy iniciado 8081...")


    try:
        while True:
            # Aceitar conexão do browser
            client_socket, client_address = server.accept()

            # Criar uma thread para lidar com a conexão do browser
            client_handler = threading.Thread(
                target=process_client,
                args=(client_socket, client_address), 
                daemon=True)
            client_handler.start()
    except KeyboardInterrupt as e:
        server.close()

if __name__=="__main__":
    main()

