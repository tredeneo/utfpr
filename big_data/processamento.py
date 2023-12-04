from pyspark.sql import SparkSession
from pyspark.sql.functions import when, col,expr,substring

arquivos = "microdados_enem_2022/DADOS/MICRODADOS_ENEM_2022.csv"

colunas_inutilizaveis = [
        "NU_INSCRICAO",
        "NU_ANO",
        "TP_ANO_CONCLUIU",
        "TP_ENSINO",
        "TP_SIT_FUNC_ESC",
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
        "TX_GABARITO_CN",
        "TX_GABARITO_CH",
        "TX_GABARITO_LC",
        "TX_GABARITO_MT",
        "TP_PRESENCA_CN",
        "TP_PRESENCA_CH",
        "TP_PRESENCA_LC",
        "TP_ENSINO",
        "TP_PRESENCA_MT",
        "CO_MUNICIPIO",
        "NO_MUNICIPIO",
        "IN_TREINEIRO",
        "CO_MUNICIPIO_ESC",
        "NO_MUNICIPIO_ESC",
        "CO_UF_ESC",
        "SG_UF_ESC",
        "TP_DEPENDENCIA_ADM_ESC",
        "TP_LOCALIZACAO_ESC",
        "NO_MUNICIPIO_PROVA",
        "Q003", #uma coluna categorica cheia de itens dificil de analisar separadamente
        "Q004"#uma coluna categorica cheia de itens dificil de analisar separadamente  
]

colunas_para_transformar_em_binario = [
    "Q007",
    "Q008",
    "Q009",
    "Q010",
    "Q011",
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
    "Q025"
]

def ler_dados_enem():
    return spark.read.csv(arquivos,header=True, inferSchema=True,sep=";",encoding="iso-8859-15")
    
def filtrar_alunos_presentes_todos_dias(df):
    return df.filter(col("TP_PRESENCA_CN")==1).filter(col("TP_PRESENCA_CH")==1).filter(col("TP_PRESENCA_LC")==1).filter(col("TP_PRESENCA_MT")==1)

def transformar_categoricas_em_binario(df):
    transformar = {col_name: when(col(col_name) == "A", 0).otherwise(1) for col_name in colunas_para_transformar_em_binario}
    for col_name, expression in transformar.items():
        df = df.withColumn(col_name, expression.alias(col_name))
    df = df.withColumn("TP_ST_CONCLUSAO",when(col("TP_ST_CONCLUSAO") == 1, 1).otherwise(0))
    df = df.withColumn("Q001",when((col("Q001") == "E") | (col("Q001") == "F") | (col("Q001") == "G"), 1).otherwise(0))
    df = df.withColumn("Q002",when((col("Q002") == "E") | (col("Q002") == "F") | (col("Q002") == "G"), 1).otherwise(0))
    df = df.withColumn("CO_MUNICIPIO_PROVA", expr("substring(CO_MUNICIPIO_PROVA, 1, length(CO_MUNICIPIO_PROVA)-1)"))
    return df
    
def ler_csv_idh():
    df = spark.read.csv("IDH_2010.csv",header=True, inferSchema=True)
    df = df.select(["Código da Unidade da Federação","Nome da Unidade da Federação","Código do Município","IDHM","IDHM Educação","IDHM Longevidade","IDHM Renda"])
    return df

def juntar_bases_pelo_codigo_municio(enem,idh):
    df = enem.join(idh,enem["CO_MUNICIPIO_PROVA"]==idh["Código do Município"],how="inner")
    df = df.drop(*["Código da Unidade da Federação","Nome da Unidade da Federação","Código do Município"])
    df = df.withColumn("regiao", substring(col("CO_UF_PROVA"), 1, 1))
    return df
    
def main():
    enem = ler_dados_enem()
    enem = filtrar_alunos_presentes_todos_dias(enem)
    enem = enem.drop(*colunas_inutilizaveis)
    enem = transformar_categoricas_em_binario(enem)
    idh = ler_csv_idh()
    df = juntar_bases_pelo_codigo_municio(enem,idh)
    #df.coalesce(1).write.csv("processado_csv", header=True, mode="overwrite")
    #df = df.repartition(1)
    df.write.parquet("processados_parquet", mode="overwrite")

    

if __name__ == "__main__":
    main()