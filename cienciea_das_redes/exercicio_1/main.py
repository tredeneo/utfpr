import networkx
arestas = [
    ("Albuquerque", "Atlanta"),
    ("Chicago", "New York"),
    ("Chicago", "Pinhais"),
    ("Curitiba", "Atlanta"),
    ("Curitiba", "Chicago"),
    ("Curitiba", "Miami"),
    ("Curitiba", "New York"),
    ("Curitiba", "Sao Paulo"),
    ("Londrina", "Foz"),
    ("Maringa", "Albuquerque"),
    ("Maringa", "Cleveland"),
    ("Miami", "Denver"),
    ("Miami", "New York"),
    ("Miami", "Philadelphia"),
    ("Minneapolis", "Foz"),
    ("New York", "Cleveland"),
    ("New York", "Minneapolis"),
    ("Philadelphia", "Atlanta"),
    ("Phoenix", "Cleveland"),
    ("Phoenix", "Maringa"),
    ("Pinhais", "Londrina"),
    ("Ponta Grossa", "Cleveland"),
    ("Ponta Grossa", "Foz"),
    ("Ponta Grossa", "Londrina"),
    ("Sao Paulo", "Boston"),
    ("Sao Paulo", "Chicago"),
    ("Sao Paulo", "Foz"),
    ("Sao Paulo", "Londrina"),
    ("Sao Paulo", "Minneapolis"),
    ("Sao Paulo", "Ponta Grossa"),
    ("Tulsa", "Maringa"),
    ("Tulsa", "New York"),
]


def main():
    grafo: networkx.Graph = networkx.Graph()
    grafo.add_edges_from(arestas)
    print(networkx.diameter(grafo))


if __name__ == "__main__":
    main()
