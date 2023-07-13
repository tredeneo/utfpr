import pickle
from typing import List
import spacy
import numpy 
from sklearn.decomposition import LatentDirichletAllocation

lda_model = LatentDirichletAllocation(              # Number of topics
                                        learning_method='online', 
                                        #max_ter=500,
                                        random_state=0,
                                        n_jobs = -1,# Use all available CPUs
                                         )

def recuperar_topicos_lda(model, feature_names, no_top_words):
    lista = []
    for _, topic in enumerate(model.components_):
        
        tmp = (" ".join([feature_names[i]
                          for i in topic.argsort()[:-no_top_words - 1:-1]]))
        lista.append(tmp)
    return lista

  
nlp = spacy.load('en_core_web_md')
  
  
def calcular_similaridade_palavras(primeira:str,segunda:str):

    words = [primeira,segunda]
    tokens = nlp(" ".join(words))
      
    token1, token2 = tokens[0], tokens[1]
    return token1.similarity(token2)

def calcular_similaridade_topicos(primeiro:List[str],segundo:List[str]):
    valor = 0
    for i in primeiro:
        for j in segundo:
            valor += calcular_similaridade_palavras(i,j)
    return valor

def separar_topicos(lista_topicos:List[List]):
    import itertools
    for (primeiro,segundo) in itertools.combinations(lista_topicos,r=2):
        print(primeiro)
        print(segundo)
        tmp = calcular_similaridade_topicos(primeiro,segundo)
        print(tmp)
        print("_"*80)


# NOME = "ARK: Survival Evolved"
NOME = "PLAYERUNKNOWN'S BATTLEGROUNDS"
# NOME = "Grand Theft Auto V"
def temporaria_nao_sei():
    with open(f"../Dados/topicos/modelos/lda_modelo_{NOME}.sav","rb") as file:
        modelo = pickle.load(file)
        palavras = numpy.load(f"../Dados/topicos/palavras/lda_words_{NOME}.npy",allow_pickle=True)
        
    lista_topicos = recuperar_topicos_lda(modelo,palavras,10)
    lista_topicos = list(map(lambda x: list(x.split(" ")),lista_topicos))
    separar_topicos(lista_topicos[0:2])

def main():
    temporaria_nao_sei()
    
if __name__ == "__main__":
    main()
