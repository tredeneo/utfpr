import Pyro4  # : ignore
import threading


@Pyro4.expose
@Pyro4.callback
class cliente_callback(object):
    def notificacao(self):
        print("callback recebido do servidor!")


def loopThread(daemon):
    # thread para ficar escutando chamadas de método do servidor
    daemon.requestLoop()


def main():
    # obtém a referência da aplicação do servidor no serviço de nomes
    ns = Pyro4.locateNS()
    uri = ns.lookup("ola.mundo")
    servidor = Pyro4.Proxy(uri)
    # ... servidor.metodo() —> invoca método no servidor
    # Inicializa o Pyro daemon e registra o objeto Pyro callback nele.
    daemon_teste = Pyro4.core.Daemon()
    callback = cliente_callback()  # —> callback será enviado ao servidor no método de
    # cadastro da aplicação
    print(servidor.ola("teste", daemon_teste))
    daemon_teste.register(callback)
    # inicializa a thread para receber notificações do servidor
    thread = threading.Thread(target=loopThread, args=(daemon_teste,))
    thread.daemon = True
    thread.start()


main()
