import mysql.connector

# import psycopg2
import csv


def main():
    tipo = "mysql"
    user = "root"
    host = "localhost"
    database = "universidade"
    password = "123"
    tabela = None
    if tipo == "mysql":
        conexao = mysql.connector.connect(
            user=user, host=host, password=password, database=database
        )
    elif tipo == "postgresql":
        conexao = psycopg2.connect(
            user=user, host=host, password=password, database=database
        )

    cursor = conexao.cursor()

    tabelas = []
    if tabela is None:

        cursor.execute(
            (
                "select table_name from information_schema.tables"
                f"where information_schema.tables.table_schema like '{database}'"
            )
        )
        tudo = cursor.fetchall()
        for i in tudo:
            tabelas.append(i[0])
    else:
        tabelas.append(tabela)

    for tabela_atual in tabelas:
        cursor.execute(
            (
                "select column_name,data_type from information_schema.columns "
                f"where table_name = '{tabela_atual}' and table_schema like '{database}'"
            )
        )
        colunas = cursor.fetchall()
        cursor.execute(f"select * from {tabela_atual}")
        with open(f"{database}-{tabela_atual}.csv", "w") as arquivo:
            write = csv.writer(arquivo)
            write.writerow([k[0] for k in colunas])
            write = csv.writer(arquivo, quating=csv.QUOTE_NONNUMERIC)
            write.writerows(cursor.fetchall())


def conectar(cursor):

    for i in cursor:
        pass
    print(type(cursor))


if __name__ == "__main__":
    main()
