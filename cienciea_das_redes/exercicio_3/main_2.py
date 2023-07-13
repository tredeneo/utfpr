import networkx
import numpy

if __name__ == "__main__":
    grafo: networkx.DiGraph = networkx.DiGraph()
    grafo.add_nodes_from(["a", "b", "c"])
    grafo.add_edges_from([("a", "a"), ("a", "b"), ("b", "a"),
                         ("a", "c"), ("b", "b"), ("b", "c"), ("c", "c")])
    lista: list[dict] = []
    for i in numpy.arange(0, 1, 0.05):
        lista.append(networkx.pagerank(grafo, alpha=i))

    for i in lista:
        print(i)
