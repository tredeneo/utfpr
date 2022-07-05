import sys
import pandas

sys.path.append(".")
import processamento

def ler_csv(caminho):
    quantidade_lida = 10
    csv = pandas.read_csv(
        caminho,
        delimiter=";",
        encoding="iso-8859-15",
        nrows=quantidade_lida,
        na_filter=False,
        engine="c"
    )
    return csv

enem_2019 = ler_csv("../../microdados_enem_2019/DADOS/MICRODADOS_ENEM_2019.csv")
enem_2020 = ler_csv("../../microdados_enem_2020/DADOS/MICRODADOS_ENEM_2020.csv",)
enem_2019, enem_2020 = processamento.pegar_interseccao(enem_2019, enem_2020)
processamento.tratamento(enem_2019).to_csv("../dados/micro_dados_2019.csv",index=False)
processamento.tratamento(enem_2020).to_csv("../dados/micro_dados_2020.csv",index=False)
