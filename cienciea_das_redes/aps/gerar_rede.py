import networkx
import pandas
import itertools

ASTROS_CAMPOS = ["Star1", "Star2", "Star3", "Star4"]

ATORES_MESMA_ARESTA = True

# flag pra rodar com menos dados pra testar mais rapido
DEBUG = False

CSV = pandas.read_csv("./imdb_top_1000.csv")
CSV = CSV[
    [
        "Series_Title",
        "Genre",
        "Director",
        "Star1",
        "Star2",
        "Star3",
        "Star4",
        "Gross",
    ]
]


def criar_grafo_do_csv():
    if ATORES_MESMA_ARESTA:
        grafo = networkx.Graph()
    else:
        grafo = networkx.MultiGraph()

    for _, row in CSV.iterrows():
        atores = row[["Star1", "Star2", "Star3", "Star4"]].values
        grafo.add_node(
            row["Series_Title"],
            gross=row["Gross"],
            genre=row["Genre"],
            director=row["Director"],
            stars=",".join(atores)
        )
    return grafo


def lista_de_arestas_com_atores(arestas):
    lista = []
    for par in arestas:
        primeiro_no = CSV.loc[CSV["Series_Title"] == par[0]]
        astros_primeiro = primeiro_no[ASTROS_CAMPOS].values.flatten()

        segundo_no = CSV.loc[CSV["Series_Title"] == par[1]]
        astros_segundo = segundo_no[ASTROS_CAMPOS].values.flatten()
        atores_comum = []
        for ator in astros_primeiro:
            if ator in astros_segundo:
                if ATORES_MESMA_ARESTA:
                    atores_comum.append(ator)
                else:
                    lista.append((par[0], par[1], {"star": ator}))
        if ATORES_MESMA_ARESTA and len(atores_comum) > 0:
            lista.append((par[0], par[1], {"stars": str(atores_comum)}))

    return lista


def main():
    import multiprocessing
    import numpy

    # pegar quantidade de nucleos e criar processos com essa quantidade
    ncores = multiprocessing.cpu_count()
    pool = multiprocessing.Pool()
    grafo = criar_grafo_do_csv()

    # produto cartesiano , de todos os nos
    titulos = CSV["Series_Title"].values.flatten()
    par_nos = [x for x in itertools.product(
        titulos, titulos) if x[0] != x[1]]

    if DEBUG:
        tamanho = len(par_nos)
        par_nos = par_nos[:int(tamanho * 0.02)]

    # dividir a lista de  pares de no pela quantidade de nucleos
    split = numpy.array_split(par_nos, ncores)
    # aplicar função em cada parte da divisão do nos
    print("calculandos arestas")
    tmp = pool.map(lista_de_arestas_com_atores, split)
    # flatten, juntar tudo em uma lista
    arestas = list(itertools.chain.from_iterable(tmp))

    print("adicionando arestas")
    grafo.add_edges_from(arestas)
    networkx.write_gml(grafo, "grafo_imdb_1000.gml")
    print("terminou")


if __name__ == "__main__":
    main()
