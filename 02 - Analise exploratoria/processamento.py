import pandas


def pegar_interseccao(enem_2019: pandas.DataFrame, enem_2020: pandas.DataFrame):
    """
    usar colunas que estão presentes nas duas bases
    e remover colunas que só são aplicadas para quem teve presença

    """
    colunas_interseccao = []

    for i in enem_2019.columns:
        if i in enem_2020.columns:
            colunas_interseccao.append(i)

    colunas_inutilizaveis = [
        "NU_INSCRICAO",
        "TP_ANO_CONCLUIU",
        "CO_PROVA_CN",
        "CO_PROVA_CH",
        "CO_PROVA_LC",
        "CO_PROVA_MT",
        "NU_NOTA_CN",
        "NU_NOTA_CH",
        "NU_NOTA_LC",
        "NU_NOTA_MT",
        "TX_RESPOSTAS_CN",
        "TX_RESPOSTAS_CH",
        "TX_RESPOSTAS_LC",
        "TX_RESPOSTAS_MT",
        "TP_LINGUA",
        "TX_GABARITO_CN",
        "TX_GABARITO_CH",
        "TX_GABARITO_LC",
        "TX_GABARITO_MT",
        "TP_STATUS_REDACAO",
        "NU_NOTA_COMP1",
        "NU_NOTA_COMP2",
        "NU_NOTA_COMP3",
        "NU_NOTA_COMP4",
        "NU_NOTA_COMP5",
        "NU_NOTA_REDACAO",
    ]
    for i in colunas_inutilizaveis:
        colunas_interseccao.remove(i)
    enem_2019 = enem_2019[colunas_interseccao]
    enem_2020 = enem_2020[colunas_interseccao]
    return enem_2019, enem_2020


def juntar_faltas(csv: pandas.DataFrame):
    tipos_presenca = [
        "TP_PRESENCA_CN",
        "TP_PRESENCA_CH",
        "TP_PRESENCA_LC",
        "TP_PRESENCA_MT",
    ]
    lista_faltas = []
    for indice, linha in csv.iterrows():
        if min(linha[20], linha[21], linha[22], linha[23]) == 0:
            lista_faltas.append(1)
        else:
            lista_faltas.append(0)
    csv = csv.drop(csv[tipos_presenca], axis=1)
    csv = pandas.concat([csv, pandas.DataFrame({"falta": lista_faltas})], axis=1)
    return csv


def transformar_categorica(csv: pandas.DataFrame):
    """
    transformar os campos categoricos que estão em alfanumerico
    para numerico
    """
    colunas = csv.columns
    for i, nome in enumerate(colunas):
        csv[csv.columns[i]] = pandas.factorize(csv.iloc[:, i])[0]
    return csv


def separar_ordinais(csv: pandas.DataFrame):
    """
    separar os campos que são ordinais
    """
    nao_ordinais = [
        "TP_SEXO",
        "TP_ESTADO_CIVIL",
        "TP_COR_RACA",
        "TP_NACIONALIDADE",
        "CO_MUNICIPIO_ESC",
        "NO_MUNICIPIO_ESC",
        "CO_UF_ESC",
        "SG_UF_ESC",
        "TP_DEPENDENCIA_ADM_ESC",
        "TP_LOCALIZACAO_ESC",
        "TP_SIT_FUNC_ESC",
        "CO_MUNICIPIO_PROVA",
        "NO_MUNICIPIO_PROVA",
        "CO_UF_PROVA",
        "SG_UF_PROVA",
        "Q003",
        "Q004",
    ]
    ordinais = [i for i in csv.columns if i not in nao_ordinais]
    csv_ordinal = csv[ordinais]
    csv_nao_ordinal = csv[nao_ordinais]
    return csv_ordinal, csv_nao_ordinal


def filtrar_formandos(csv: pandas.DataFrame):
    csv = csv[csv["TP_ST_CONCLUSAO"] == 2]
    csv = csv.drop(csv[["IN_TREINEIRO", "TP_ST_CONCLUSAO"]], axis=1)
    return csv


def limpeza(enem_2019: pandas.DataFrame, enem_2020: pandas.DataFrame):

    enem_2019, enem_2020 = pegar_interseccao(enem_2019, enem_2020)

    enem_2019 = juntar_faltas(enem_2019)
    enem_2020 = juntar_faltas(enem_2020)

    return enem_2019, enem_2020


def main():
    quantidade_lida = 10000
    enem_2019 = pandas.read_csv(
        "./microdados_enem_2019/DADOS/MICRODADOS_ENEM_2019.csv",
        delimiter=";",
        encoding="iso-8859-15",
        nrows=quantidade_lida,
    )
    enem_2020 = pandas.read_csv(
        "./microdados_enem_2020/DADOS/MICRODADOS_ENEM_2020.csv",
        delimiter=";",
        encoding="iso-8859-15",
        nrows=quantidade_lida,
    )
    enem_2019, enem_2020 = limpeza(enem_2019, enem_2020)
    enem_2019 = transformar_categorica(enem_2019)
    enem_2020 = transformar_categorica(enem_2020)

    enem_2019_ordinal, enem_2019_nao_ordinal = separar_ordinais(enem_2019)
    enem_2020_ordinal, enem_2020_nao_ordinal = separar_ordinais(enem_2020)


if __name__ == "__main__":
    main()
