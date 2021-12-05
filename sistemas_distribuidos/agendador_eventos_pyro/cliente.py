import Pyro4  # : ignore
import threading
import usuario


def configura_pyro(user: usuario.Usuario):
    '''
        instancia o servidor usando o servidor de nomes
        registra o cliente com o usuario passado pelo argumentos
        o cliente fica esperando chamadas rodando em uma thread separada
    '''
    global servidor
    servidor = Pyro4.core.Proxy("PYRONAME:servidor")
    daemon = Pyro4.Daemon()
    daemon.register(user)
    thread = threading.Thread(target=daemon.requestLoop, daemon=True)
    thread.start()


def main():
    # fmt: off
    user = usuario. Usuario()
    configura_pyro(user)
    menu = (
        "MENU\n"
        "1 - cadastrar usuario\n"
        "2 - cadastrar evento\n"
        "3 - consultar evento \n"
        "4 - votar\n"
        "0 - sair\n"
        "digite um numero:"
    )

    try:
        while True:
            try:
                entrada = int(input(menu))
            except ValueError:
                print("entrada invalida")
                continue
            match entrada:
                case 1:
                    user.cadastrar(servidor),
                case 2:
                    user.cadastrar_enquete(servidor),
                case 3:
                    user.consulta_enquete(servidor),
                case 4:
                    user.votar(servidor),
                case _:
                    print("saiu")
                    break
    except KeyboardInterrupt:
        print("programa foi está sendo encerrado")
    # fmt: on


if __name__ == "__main__":
    main()
