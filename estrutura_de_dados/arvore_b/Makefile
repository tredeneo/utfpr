#Neste exemplo de Makefile, os arquivos objetos (.o) são gerados separadamente, assim, somente arquivos fonte (.c) alterados são recompilados para gerar um novo .o. Então o novo .o é linkado com os outros .o (dos arquivos não alterados) para gerar o executável. O make sabe o que deve ser recompilado com base nos timestamps dos arquivos fonte e seus respectivos arquivos objeto.


######### Sintaxe ###########
#regra: dependências
#<TAB>	comando	
#############################

#==============
#A regra all: é usada para construir o sistema de forma incremental 
all: out
	@echo " " 
	@echo "Copilação concluída!!"
	@echo " " 
	 

out: mainArvoreb.o printArvoreb.o removeArvoreb.o buscaArvoreb.o criaArvoreb.o insereArvoreb.o
	gcc -o out mainArvoreb.o printArvoreb.o removeArvoreb.o buscaArvoreb.o criaArvoreb.o insereArvoreb.o

mainArvoreb.o: mainArvoreb.c
	gcc -o mainArvoreb.o -c mainArvoreb.c 


printArvoreb.o: printArvoreb.c
	gcc -o printArvoreb.o -c printArvoreb.c

removeArvoreb.o: removeArvoreb.c
	gcc -o removeArvoreb.o -c removeArvoreb.c

criaArvoreb.o: criaArvoreb.c
	gcc -o criaArvoreb.o -c criaArvoreb.c

insereArvoreb.o: insereArvoreb.c
	gcc -o insereArvoreb.o -c insereArvoreb.c

buscaArvoreb.o: buscaArvoreb.c
	gcc -o buscaArvoreb.o -c buscaArvoreb.c  

clean: 
	rm -f *.o

execClean:
	rm -f out


