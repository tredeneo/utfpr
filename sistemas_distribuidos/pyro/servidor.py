import Pyro4


# configura uma instância única do servidor para ser consumida por diversos clientes
# @Pyro4.behavior(instance_mode="single")
@Pyro4.expose
class servidor(object):
    cliente = None

    def ola(self, name: str, daemon):
        cliente = daemon
        return f"ola {name}"


def main():
    # registra a aplicação do servidor no serviço de nomes
    daemon = Pyro4.Daemon()
    ns = Pyro4.locateNS()
    uri = daemon.register(servidor)
    ns.register("ola.mundo", uri)
    print("A aplicação está ativa")
    daemon.requestLoop()


main()
