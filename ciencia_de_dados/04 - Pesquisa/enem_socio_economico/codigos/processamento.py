import pandas

"""
esse é o pacote principal que é usado no processamento, e limpeza dos dados,
"""


def tratamento(csv):
    """
    fazer a limpeza e tratamento dos dados
    """
    print("arquivo lido")

    # filtrar alunos com formação presvista para o ano do enem
    csv = csv[csv["TP_ST_CONCLUSAO"] == 2]
    csv = juntar_faltas(csv)
    csv = remover_sem_questionario(csv)
    csv = remover_sem_raca(csv)
    csv = possui_automovel(csv)
    csv = converter_salario_minimo(csv)
    # remove digito verificardor do codigo do municipio, pois algumas base não tem ele
    csv["CO_MUNICIPIO_PROVA"] = csv["CO_MUNICIPIO_PROVA"].astype(
        str).str[:-1].astype(int)

    municipio_idh = pandas.read_csv("./cod_idh.csv")
    municipio_pib = pandas.read_csv("./cod_pib.csv")
    municipio_densidade = pandas.read_csv("./cod_densidade.csv")
    # juntando idh,pib,densidade com base no codigo do municipio
    csv = pandas.merge(csv, municipio_idh[["codigo", "IDHM"]], how="left",
                       left_on="CO_MUNICIPIO_PROVA", right_on="codigo").drop(columns=["codigo"])
    print("adicionando idh")
    csv = pandas.merge(csv, municipio_pib[["codigo", "PIB"]], how="left",
                       left_on="CO_MUNICIPIO_PROVA", right_on="codigo").drop(columns=["codigo"])
    print("adicionando pib")
    csv = pandas.merge(csv, municipio_densidade[["codigo", "densidade"]], how="left",
                       left_on="CO_MUNICIPIO_PROVA", right_on="codigo").drop(columns=["codigo"])
    print("adicionando densidade")
    csv = csv.drop(columns=["CO_MUNICIPIO_PROVA", "index"])
    # converter o idh para facilitar a interpretação, 0.1 vira 100
    csv["IDHM"] = csv["IDHM"]*100
    # converter o idh para facilitar a interpretação, para cada 1000
    csv["PIB"] = csv["PIB"]/1000
    return csv


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
        "NU_ANO",
        "TP_ESCOLA",
        "SG_UF_ESC",
        "SG_UF_PROVA",
        "TP_ENSINO",
        "TP_NACIONALIDADE",
        "TP_DEPENDENCIA_ADM_ESC",
        "TP_LOCALIZACAO_ESC",
        "NO_MUNICIPIO_ESC",
        "NO_MUNICIPIO_PROVA",
        "CO_MUNICIPIO_ESC",
        "TP_SIT_FUNC_ESC",
        "CO_UF_ESC",
        "CO_UF_PROVA",
        "Q001",
        "Q002",
        "Q003",
        "Q004",
        "Q005",
        "Q007",
        "Q008",
        "Q009",
        "Q012",
        "Q013",
        "Q014",
        "Q015",
        "Q016",
        "Q017",
        "Q018",
        "Q019",
        "Q020",
        "Q021",
        "Q022",
        "Q023",
        "Q024",
        "Q025",
    ]
    for i in colunas_inutilizaveis:
        colunas_interseccao.remove(i)
    enem_2019 = enem_2019[colunas_interseccao]
    enem_2020 = enem_2020[colunas_interseccao]
    return enem_2019, enem_2020


def juntar_faltas(csv: pandas.DataFrame):
    """
        juntar as faltas em uma unica variavel binaria
    """
    print("juntar faltas")
    tipos_presenca = [
        "TP_PRESENCA_CN",
        "TP_PRESENCA_CH",
        "TP_PRESENCA_LC",
        "TP_PRESENCA_MT",
    ]
    lista_faltas = []
    for indice, linha in csv.iterrows():
        if (
            min(
                linha.get(tipos_presenca[0]),
                linha.get(tipos_presenca[1]),
                linha.get(tipos_presenca[2]),
                linha.get(tipos_presenca[3]),
            )
            == 0
        ):
            # 0 é que faltou em algumas das provas, se tiver algum zero sera considerado falta na prova
            lista_faltas.append(1)
        else:
            lista_faltas.append(0)
    csv = csv.drop(csv[tipos_presenca], axis=1)
    csv = pandas.concat(
        [csv, pandas.DataFrame({"falta": lista_faltas})], axis=1)
    return csv


def possui_automovel(csv: pandas.DataFrame):
    """
        coluna de carro e moto convertida para uma unica,
        são algumas categorias e foram convertidas para possue ou não
    """
    print("possui_automovel")

    possue = ["B", "C", "D", "E"]
    lista_automovel = []
    for indice, linha in csv.iterrows():
        if (linha.get("Q010") in possue) or (linha.get("Q011") in possue):
            lista_automovel.append("sim")
        elif linha.get("Q010") == "A":
            lista_automovel.append("não")
        elif linha.get("Q011") == "A":
            lista_automovel.append("não")
        else:
            lista_automovel.append("")
    csv = csv.drop(csv[["Q010", "Q011"]], axis=1)
    csv = pandas.concat([csv.reset_index(), pandas.DataFrame(
        {"automovel": lista_automovel})], axis=1)
    return csv


def converter_salario_minimo(csv: pandas.DataFrame):
    """
    converter o salario de categorica para numerica, a proporção 
    é a mesma para ambos os anos
    """
    print("converter_salario_minimo")
    renda_minimo = {
        "A": 0,
        "B": 1,
        "C": 1.5,
        "D": 2,
        "E": 2.5,
        "F": 3,
        "G": 4,
        "H": 5,
        "I": 6,
        "J": 7,
        "K": 8,
        "L": 9,
        "M": 10,
        "N": 12,
        "O": 15,
        "P": 20,
        "Q": 28,
    }
    csv["salario"] = csv.Q006.apply(
        lambda x: renda_minimo[x] if x in renda_minimo else "teste")
    return csv.drop(columns=["Q006"])


def remover_sem_questionario(csv: pandas.DataFrame):
    """ 
    remover alunos que não responderam os questionario
    socio-cultural
    """
    print("remover_sem_questionario")
    return csv[csv["Q006"] != ""]


def remover_sem_raca(csv: pandas.DataFrame):
    """
    remover alunos que não informram ra raça/cor
    """
    print("remover_sem_raca")
    return csv[csv["TP_COR_RACA"] != 0]


def main():
    pass


if __name__ == "__main__":
    main()
