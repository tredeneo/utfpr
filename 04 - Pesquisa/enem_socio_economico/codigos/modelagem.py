import pandas
import statsmodels.formula.api as smf

quantidade_lida = 10000


def ler_arquivo(nome_arquivo):
    csv = pandas.read_csv(
        f"../dados/micro_dados_{nome_arquivo}.csv",
        # nrows=quantidade_lida,
        engine="c",
        na_filter=False,
    )
    return csv


def calcular_modelo(csv, nome_arquivo):
    resposta = "falta ~"
    resultados = []
    for i, campo in enumerate(campos):
        formula = resposta + " + ".join(campo)
        resultado_tmp = smf.logit(formula, csv).fit()
        with open(f"../modelos/{nome_arquivo}_{i+1}.txt", "w") as file:
            file.write(resultado_tmp.summary().as_text())
            file.close()
        resultados.append(resultado_tmp)
    return resultados


campos = [
    [
        "C(TP_SEXO)",
        "C(TP_COR_RACA)",
        "salario",
        "C(automovel)",
        "IDHM",
        "PIB",
        "densidade"
    ],
]
if __name__ == "__main__":
    arquivo = "2019"
    csv = ler_arquivo(arquivo)
    calcular_modelo(csv, arquivo)
