import pandas

"""
 codigo usado para limpar os dados do pib,idh e densidade

"""

csv = pandas.read_csv("./pib.csv")
csv.drop(csv.columns[[0, 1]], axis=1, inplace=True)
csv["codigo"] = csv.codigo.apply(lambda x: str(x)[:-1])


csv.to_csv("cod_pib.csv", index=False)


csv = pandas.read_csv("./idh.csv")
csv.drop(csv.columns[[0, 2, 3, 4, 5]], axis=1, inplace=True)
csv.to_csv("cod_idh.csv", index=False)

csv = pandas.read_csv("./socio_stats_wide_cities.csv")
csv["densidade"] = csv["Densidade Demográfica (hab/km²)"]
csv["codigo"] = csv["CodMun"]
csv = csv[["codigo", "densidade"]]
csv.to_csv("cod_densidade.csv", index=False)
