import networkx as nx
import pandas as pd
from networkx.algorithms.community import k_clique_communities

G = nx.read_gml("grafo_imdb_1000.gml")
#K-Clique

c = list(k_clique_communities(G, 4))
dataFrameAux = pd.DataFrame(columns=["nodeId", "Gross", "Genre", "Director", "Star1", "Star2", "Star3", "Star4", "partition"])
maiorPartitionTam = 0
maiorPartition = 0
partition = -1
for i in c:
    partition = partition + 1
    if(len(i) > maiorPartitionTam):
        maiorPartitionTam = len(i)
        maiorPartition = partition
    for no in sorted(list(i)):
        Gross = G.nodes[no]['gross']
        Genre = G.nodes[no]['genre']
        Director = G.nodes[no]['director']
        Star1 = G.nodes[no]['Star1']
        Star2 = G.nodes[no]['Star2']
        Star3 = G.nodes[no]['Star3']
        Star4 = G.nodes[no]['Star4']
        dataFrameAux = dataFrameAux.append({'nodeId':no,'partition':partition,"Gross":Gross,  "Genre":Genre, "Director":Director, "Star1":Star1, "Star2":Star2, "Star3":Star3, "Star4":Star4}, ignore_index=True)

dataFrameAux.to_csv('k-clique.csv', index=False) 
print(maiorPartition)