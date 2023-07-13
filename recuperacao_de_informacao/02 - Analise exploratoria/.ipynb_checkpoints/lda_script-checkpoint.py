import numpy as np
import pandas as pd
import re, nltk, spacy, gensim

# dataframe mais eficiente e com multithread
import polars
import pyarrow

# Sklearn
from sklearn.decomposition import LatentDirichletAllocation, TruncatedSVD,NMF
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer
from sklearn.model_selection import GridSearchCV


#https://stackoverflow.com/questions/40115043/no-space-left-on-device-error-while-fitting-sklearn-model
import os
os.environ['JOBLIB_TEMP_FOLDER'] = '/tmp'

def display_topics(model, feature_names, no_top_words):
    for topic_idx, topic in enumerate(model.components_):
        print(" ".join([feature_names[i]
                          for i in topic.argsort()[:-no_top_words - 1:-1]]))
def main():
    df = polars.read_csv('../Dados/steam_reviews_lemmatization.csv').lazy()
    #df = df.filter(polars.col("title").is_in(["Terraria","Stardew Valley"]))
    df = df.select(polars.col("lemmatized"))
    df = df.rename({"lemmatized": "review"})

    import ast
    #df.collect()
    df = df.select(
            polars.col("review").apply(lambda x: " ".join(ast.literal_eval(x)))
    )
    #df.collect().head(5)


    df = df.collect().to_pandas()

    vectorizer = CountVectorizer(analyzer='word',       
                                 #min_df=0.1,                        # minimum reqd occurences of a word 
                                 stop_words='english',             # remove stop words
                                 max_df=1.0,
                                 lowercase=True,                   # convert all words to lowercase
                                 token_pattern='[a-zA-Z0-9]{3,}',  # num chars > 3
                                 # max_features=50000,             # max number of uniq words
                                )

    data_vectorized = vectorizer.fit_transform(df["review"])


    no_top_words = 10






    # Build LDA Model
    lda_model = LatentDirichletAllocation(              # Number of topics
                                        learning_method='online', 
                                        #max_ter=500,
                                        random_state=0,
                                        n_jobs = -1,# Use all available CPUs
                                         )
    lda_output = lda_model.fit_transform(data_vectorized)
    names = vectorizer.get_feature_names_out()

    display_topics(lda_model,names,10)

    tfidf_vectorizer = TfidfVectorizer(max_df=0.90, min_df =25, max_features=5000, use_idf=True)
    tfidf = tfidf_vectorizer.fit_transform(df['review'])
    tfidf_feature_names = tfidf_vectorizer.get_feature_names_out()

    nmf = NMF(n_components=10, random_state=0, init='nndsvd').fit(tfidf)
    display_topics(nmf, tfidf_feature_names, no_top_words)
    

