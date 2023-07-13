import polars
from polars import LazyFrame
import time
from functools import wraps
from textblob import Blobber
from textblob.sentiments import NaiveBayesAnalyzer
pattern = Blobber()
bayes = Blobber(analyzer=NaiveBayesAnalyzer())

def timeit(func):
    @wraps(func)
    def timeit_wrapper(*args,**kwargs):
        start_time = time.perf_counter()
        result = func(*args,**kwargs)
        end_time = time.perf_counter()
        total_time = (end_time - start_time)/ 60
        print(f"{func.__name__} levou {total_time:.2f} minutos para executa")
        return result
    return timeit_wrapper

def filtrar_erros(df:LazyFrame):
    df = df.filter(polars.col("review").is_not_null())
    df = df.filter(polars.col("review").str.n_chars() > 2)
    df = df.with_columns(polars.col("review").str.replace("&gt",""))
    df = df.with_columns(polars.col("review").str.replace("&lt",""))

    return df


def calcular_idioma(df:LazyFrame):
    import fasttext

    fasttext.FastText.eprint = lambda x:None #remover avisos 
    modelo = fasttext.load_model("../Dados/lid.176.bin")

    def func(x):
        lang = modelo.predict(x)[0]
        return str(lang)[11:13]
    df = df.with_columns(polars.col("review").apply(func).alias("lang"))
    return df

def arrumar_contracao(df:LazyFrame):
    import contractions
    def func(x):
        words = []
        bom = 0
        ruim = 0
        for word in x.split():
            try:
                words.append(contractions.fix(word))
                bom +=1
            except:
                words.append(word)
                ruim +=1
        if ruim > 0:
            print(bom,ruim) 
        return words #str
    df = df.with_columns(polars.col("review").apply(func).alias("no_contract"))
    return df

def juntar_sem_contracao(df:LazyFrame):
    def func(x):
        return " ".join(map(str,x))
    df = df.with_columns(polars.col("no_contract").apply(func).alias("rating_description_str"))
    return df

def tokenizar(df:LazyFrame):
    import re
    from nltk.tokenize import word_tokenize
    #rxx = re.compile(r'([^\w\s]{1,})([^\n\w\n])')
    rxx = re.compile(r'[^a-zA-Z]')
    def remover_reticencias(x):
        tmp = rxx.sub(" ",x)
        return word_tokenize(tmp)

    df = df.with_columns(polars.col("rating_description_str").apply(remover_reticencias).alias("tokenized"))
    return df


def minuscula(df:LazyFrame):
    def func(x):
        lista = []
        for word in x:
            lista.append(word.lower())
        return lista
    df = df.with_columns(polars.col("tokenized").apply(func).alias("lower"))
    return df 

def remover_palavras_vazia(df:LazyFrame):
    from nltk.corpus import stopwords
    palavras = set(stopwords.words("english"))
    def func(x):
        lista = []
        for word in x:
            if word not in palavras:
                lista.append(word)
        return lista
    df = df.with_columns(polars.col("lower").apply(func).alias("stopwords_removed"))
    return df

def classe_gramatical(df:LazyFrame):
    import nltk
    return df.with_columns(polars.col("stopwords_removed").apply(nltk.tag.pos_tag).alias("pos_tag"))

def converter_wordnet(df:LazyFrame):
    from nltk.corpus import wordnet
    def get_wordnet_pos(tag:str):
        match tag[0]:
            case 'J': return wordnet.ADJ
            case 'V': return wordnet.VERB
            case 'N': return wordnet.NOUN
            case 'R': return wordnet.ADV
            case _ : return wordnet.NOUN
    
    def func(x):
        lista = []
        for (word,pos_tag) in x:
            lista.append((word,get_wordnet_pos(pos_tag)))
        return lista
    df = df.with_columns(polars.col("pos_tag").apply(func).alias("wordnet_pos"))
    return df
        


def lematizacao(df:LazyFrame):
    from nltk.stem import WordNetLemmatizer

    def func(x):
        lista = []
        for word,tag in x:
            tmp = WordNetLemmatizer().lemmatize(word,tag)
            lista.append(tmp)
        return lista

    df = df.with_columns(polars.col("wordnet_pos").apply(func).alias("lemmatized"))
    return df

def filtrar_quantidade(df:LazyFrame):
    # agrupado = df.groupby("title").count()
    return df.filter(polars.col("title").count().over("title") > 100)
     

def calcular_polatidade(df:LazyFrame):
    def calcular_padrao(text):
        return pattern(text).sentiment.polarity
    def calcular_bayes(text):
        sentimento = bayes(text)
        return sentimento.sentiment.p_pos - sentimento.sentiment.p_neg
    
    df = df.with_columns(polars.col("review").apply(calcular_padrao).alias("polaridade"))
    df = df.with_columns(polars.col("review").apply(calcular_bayes).alias("polaridade_bayes"))
    return df


@timeit
def main():
    df = polars.read_csv("../Dados/steam_reviews.csv").lazy()
    df = df.filter(polars.col("title").is_in(["Wallpaper Engine"]).is_not())
    # df = df.filter(polars.col("title").is_in(
        # [
            # "Dead by Daylight",
            # "RESIDENT EVIL 2 / BIOHAZARD RE:2", 
    #         "Stardew Valley",
    #         "Terraria",
    #         "Wallpaper Engine",
    #         "Kenshi",
            # "Foundation",
            # "Moonlighter"
        # ]))
    df = df.with_columns(polars.col("title").str.replace("RESIDENT EVIL 2 / BIOHAZARD RE:2","RESIDENT EVIL 2"))
    df = filtrar_erros(df)
    df = calcular_idioma(df)
    df = df.filter(polars.col("lang") == "en")
    df = arrumar_contracao(df)
    df = juntar_sem_contracao(df)
    df = tokenizar(df)
    df = minuscula(df)
    df = remover_palavras_vazia(df)
    df = classe_gramatical(df)
    df = converter_wordnet(df)
    df = lematizacao(df)
    df = filtrar_quantidade(df)
    df = calcular_polatidade(df)

    # print(df.collect())
    df.collect().write_parquet("../Dados/tratados.parquet")





if __name__ == "__main__":
    main()
