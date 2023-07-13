# Faça a criptanálise da mensagem cifrada com o cifrador de César e mostre a chave usada. Qual é o texto criptografado?
|letra | frequencia %|
|-|-|
|r |14.49|
|v |12.56|
|9 |11.59|
|5 |8.21|
|z |5.79|
|4 |5.79|
|3 |5.79|
|B |5.31|
|t |5.31|
|8 |3.86|
|A |3.86|
|y |3.38|
|x |1.93|
|u |1.93|
|7 |1.93|
|6 |1.93|
|2 |0.96|
|s |0.96|
|G |0.48|
|d |0.48|
|E |0.48|
|m |0.48|
|U |0.48|
|V |0.48|
|g |0.48|
|w |0.48|
|c |0.48|

como a letra "a" é a mais usada no portugues, e na analise de frequencia a letra que mais aparace é a letra "r",é possivel pegar a diferença do valor ascii entre as duas letras para achar a chave, nesse caso a chave é "17"

# O algoritmo de Vernam é vulnerável à análise de frequências? Justifique.
não, pois cada letra sera convertida usando uma chave diferente, fazendo que mesma letras tenha frequencias diferentes por serem convertidas a letras diferentes

## Como será feita a geração da chave?
para cada execução sera gerando uma chave aleatoria do tamanho do texto de entrada

## É possivel usar o algoritmo de Vernam para cifrar uma base de dados? Justifique.
é possivel, porem a chave teria o mesmo tamanho da base, e fica algo inviavel para armazenar a chave


# O algoritmo RC4 é vulnerável à análise de frequências? Justifique.
não, apesar de usar uma chave pequena, tem muitas operações XOR e que usa passos anteriores para cada letra, que no final a mesma letra de origem vai estar mapeada para letras de destinos diferentes

