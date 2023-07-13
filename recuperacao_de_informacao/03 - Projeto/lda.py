import numpy as np
import pandas as pd


# Sklearn
from sklearn.decomposition import LatentDirichletAllocation
from sklearn.feature_extraction.text import CountVectorizer

import pickle

#https://stackoverflow.com/questions/40115043/no-space-left-on-device-error-while-fitting-sklearn-model
import os
os.environ['JOBLIB_TEMP_FOLDER'] = "/run/host/run/media/dnl/5fbc90ed-1aed-4ffb-a28c-39f71b69216d/tmp" #'/tmp'



def topicos_LDA(df:pd.DataFrame,coluna:str,jogo:str):
    vectorizer = CountVectorizer(analyzer='word',       
                                 #min_df=0.1,                        # minimum reqd occurences of a word 
                                 stop_words='english',             # remove stop words
                                 max_df=1.0,
                                 lowercase=False,
                                 token_pattern='[a-zA-Z0-9]{3,}',  # num chars > 3
                                 # max_features=50000,             # max number of uniq words
                                )

    data_vectorized = vectorizer.fit_transform(df[coluna])

    # Build LDA Model
    lda_model = LatentDirichletAllocation(              # Number of topics
                                        learning_method='online', 
                                        #max_ter=500,
                                        random_state=0,
                                        n_jobs = -1,# Use all available CPUs
                                         )
    lda_output = lda_model.fit_transform(data_vectorized)
    names = vectorizer.get_feature_names_out()
    
    with open(f"../Dados/topicos/modelos//lda_modelo_{jogo}.sav","wb") as f:
        pickle.dump(lda_model,f)

    with open(f"../Dados/topicos/palavras/lda_words_{jogo}.npy","wb") as f:
        np.save(f,names,allow_pickle=True)
        
    with open(f"../Dados/topicos/vetor/lda_vetor_{jogo}.npy","wb") as f:
        np.save(f,lda_output,allow_pickle=True)


   
def main():
    df = pd.read_parquet("../Dados/tratados.parquet",columns=["lemmatized","title"])
    df["lemmatized"] = df["lemmatized"].apply(str)
    tmp = df.groupby(["title"])["title"].first()

    for jogo in tmp:
        print(jogo)
        jogo_atual = df[df["title"] == jogo]
        topicos_LDA(jogo_atual,"lemmatized",jogo)

if __name__ == "__main__":
    main()
