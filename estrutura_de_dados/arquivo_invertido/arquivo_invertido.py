# -*- coding: utf-8 -*-
from typing import List


def verifica_palavra_repetida(lista, palavra):
    for i in range(len(lista)):
        if lista[i] == palavra:
            return i
    return -1


def mostra_arquivo_invertido(lista, matriz):
    for i in range(len(matriz)-1):
        print (lista[i])
        print (matriz[i])
    return None


def selection_sort(lista, matriz):
    for i in range(len(lista)):
        for k in range(i, len(lista), 1):
            if lista[k] < lista[i]:
                lista[i], lista[k], matriz[i], matriz[k] = lista[k], lista[i], matriz[k], matriz[i]
    return lista, matriz


def adiciona_no_arquivo_invertido(lista, matriz):
    arq = open('Historia.txt', 'r')
    texto = arq.read()
    linha = [None]
    palavra = ''
    k = 0
    for i in range(len(texto)):
        caracter = texto[i]
        if (caracter == '-') or (caracter == ':') or (caracter == '.') or (caracter == ',') or (caracter == '?'):
            continue
        if (caracter == ' ') or (caracter == '\n'):
            posicao = i-len(palavra)
            repetido = verifica_palavra_repetida(lista, palavra)
            if repetido != -1:
                matriz[repetido].append(posicao)
            else:
                lista.append(palavra)
                linha.append(posicao)
                matriz.append(linha)
                linha = []
            palavra = ''
            k = k+1
        elif caracter != '\0':
            palavra = palavra+caracter
    lista, matriz = selection_sort(lista, matriz)
    return lista, matriz, texto


def mostra_palavra_da_lista(lista, matriz, texto):
    posicao = None
    palavra = input(" escreva uma palavra:")
    aux = 0
    for i in range(len(lista)):
        if palavra == lista[i]:
            posicao = i
            aux = 1
            break
    if aux == 0:
        print (" a palavra não esta na lista")
        return None
    distancia = 10
    tamanho = len(matriz[posicao])
    print ("a palavra aparece no texto em %d posição" % tamanho)
    aux = 0
    for i in matriz[posicao]:
        if aux == 1:
            palavra = input("deseja ver a proxima aparição da palavra? \n (S / N):")
            if palavra == "N" or palavra == "n":
                break
        if i-distancia < 0 and i+distancia > len(texto):
            print ("trecho do texto - " + texto[distancia-distancia:len(texto)-1])
        elif i-distancia < 0:
            print ("trecho do texto - " + texto[distancia-distancia:i+distancia])
        elif i+distancia > len(texto):
            print ("trecho do texto - " + texto[i-10:len(texto)-1])
        else:
            print ("trecho do texto - " + texto[i-10:i+10])
        aux = 1
    return None


def main():
    lista= []
    matriz = []
    texto = None
    while 1 == 1:
        print ("\n MENU:")
        print (" 1 - para criar o arquivo invertido")
        print (" 2 - para mostrar o arquivo invertido")
        print (" 3 - para procurar por uma palavra no arquivo invertido")
        print (" 4 - para sair do programa")
        opcao = int(input(" digite uma numero do menu:"))
        if opcao == 1:
            lista, matriz, texto = adiciona_no_arquivo_invertido(lista, matriz)
        elif opcao == 2:
            mostra_arquivo_invertido(lista, matriz)
        elif opcao == 3:
            mostra_palavra_da_lista(lista, matriz, texto)
        else:
            break
    return None


main()
