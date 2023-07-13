from typing import Callable, NewType
import networkx

Grafos = NewType("Grafos", networkx.Graph)


def primeiros_50(f: Callable, grafo: Grafos):  # -> list[tuple[str, str]]:
    lista: list[tuple[str, str]] = []
    centralidades = f(grafo)
    centralidades = dict(sorted(centralidades.items(),
                                key=lambda item: item[1], reverse=True)[:50])

    for i in centralidades:
        tmp = grafo.nodes[i]
        lista.append((tmp["name"], tmp["categories"]))
    return lista


def mostrar_lista(lista: list):
    
    for i in lista:
        print(i)
    print("_"*79)



def main():
    grafo: Grafos = networkx.read_gml("./GraphMissingEdges.gml")
    mostrar_lista(primeiros_50(networkx.degree_centrality, grafo))
    mostrar_lista(primeiros_50(
        networkx.eigenvector_centrality, grafo))
    mostrar_lista(primeiros_50(
        networkx.closeness_centrality, grafo))
    mostrar_lista(primeiros_50(
        networkx.betweenness_centrality, grafo))

    # print((centralidade_grau))


if __name__ == "__main__":
    main()
