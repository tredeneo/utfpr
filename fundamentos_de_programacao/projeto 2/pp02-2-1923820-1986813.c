/*nome:daniel de viveiros inácio
  ra:1923820
  nome:kelvin james de souza martins 
  ra:1986813*/
#include <stdio.h>
#include <string.h>
#define TAM 100
main()
{
	char string[TAM],//sequencia completa como entrada
		conteudo[TAM],//string que possui os codigos que tem dentro da sequencia dada
		entrada[TAM],//codigo de entrada para ser verificado
		*teste;//foi usado a função "strstr" que tem como saindo um ponteiro
 	int i,k,j,l;
	printf("escreva a sequencia genetica:");
	fgets(string,TAM,stdin);
	printf("escreva a estrutura da proteina:");
	fgets(entrada,TAM,stdin);
	entrada[strlen(entrada)-1]='\0';
	for(i=2,k=1,j=0,l=0;i<strlen(string);i+=3,k+=3,j+=3,l++)//i,k,j varia de 3 em 3pois as cadeias são de 3 letras,e l varia de 1 pois é um string para armazenar os codigos
	{
		if((string[j]=='t'&&string[k]=='t'&&string[i]=='t')||(string[j]=='t'&&string[k]=='t'&&string[i]=='c'))
		{
			conteudo[l]='A';
		}
		else if((string[j]=='t'&&string[k]=='t'&&string[i]=='a')||(string[j]=='t'&&string[k]=='t'&&string[i]=='g')||(string[j]=='c'&&string[k]=='t'&&string[i]=='t')||(string[j]=='c'&&string[k]=='t'&&string[i]=='c')||
				(string[j]=='c'&&string[k]=='t'&&string[i]=='a')||(string[j]=='c'&&string[k]=='t'&&string[i]=='g'))
		{
			conteudo[l]='B';
		}
		else if((string[j]=='a'&&string[k]=='t'&&string[i]=='t')||(string[j]=='a'&&string[k]=='t'&&string[i]=='c')||(string[j]=='a'&&string[k]=='t'&&string[i]=='a'))
		{
			conteudo[l]='C';
		}
		else if(string[j]=='a'&&string[k]=='t'&&string[i]=='g')
		{
			conteudo[l]='D';
		}
		else if((string[j]=='g'&&string[k]=='t'&&string[i]=='t')||(string[j]=='g'&&string[k]=='t'&&string[i]=='c')||(string[j]=='g'&&string[k]=='t'&&string[i]=='a')||(string[j]=='g'&&string[k]=='t'&&string[i]=='g'))
		{
			conteudo[l]='E';
		}
		else if((string[j]=='t'&&string[k]=='c'&&string[i]=='t')||(string[j]=='t'&&string[k]=='c'&&string[i]=='c')||(string[j]=='t'&&string[k]=='c'&&string[i]=='a')||(string[j]=='t'&&string[k]=='c'&&string[i]=='g')||
				(string[j]=='a'&&string[k]=='g'&&string[i]=='t')||(string[j]=='a'&&string[k]=='g'&&string[i]=='c'))
		{
			conteudo[l]='F';
		}
		else if((string[j]=='c'&&string[k]=='c'&&string[i]=='t')||(string[j]=='c'&&string[k]=='c'&&string[i]=='c')||(string[j]=='c'&&string[k]=='c'&&string[i]=='a')||(string[j]=='c'&&string[k]=='c'&&string[i]=='g'))
		{
			conteudo[l]='G';
		}
		else if((string[j]=='a'&&string[k]=='c'&&string[i]=='t')||(string[j]=='a'&&string[k]=='c'&&string[i]=='c')||(string[j]=='a'&&string[k]=='c'&&string[i]=='a')||(string[j]=='a'&&string[k]=='c'&&string[i]=='g'))
		{
			conteudo[l]='H';
		}
		else if((string[j]=='g'&&string[k]=='c'&&string[i]=='t')||(string[j]=='g'&&string[k]=='c'&&string[i]=='c')||(string[j]=='g'&&string[k]=='c'&&string[i]=='a')||(string[j]=='g'&&string[k]=='c'&&string[i]=='g'))
		{
			conteudo[l]='I';
		}
		else if((string[j]=='t'&&string[k]=='a'&&string[i]=='t')||(string[j]=='t'&&string[k]=='a'&&string[i]=='c'))
		{
			conteudo[l]='J';
		}
		else if((string[j]=='t'&&string[k]=='a'&&string[i]=='a')||(string[j]=='t'&&string[k]=='a'&&string[i]=='g')||(string[j]=='t'&&string[k]=='g'&&string[i]=='a'))
		{
			conteudo[l]='K';
		}
		else if((string[j]=='c'&&string[k]=='a'&&string[i]=='t')||(string[j]=='c'&&string[k]=='a'&&string[i]=='c'))
		{
			conteudo[l]='L';
		}
		else if((string[j]=='c'&&string[k]=='a'&&string[i]=='a')||(string[j]=='c'&&string[k]=='a'&&string[i]=='g'))
		{
			conteudo[l]='M';
		}
		else if((string[j]=='a'&&string[k]=='a'&&string[i]=='t')||(string[j]=='a'&&string[k]=='a'&&string[i]=='c'))
		{
			conteudo[l]='N';
		}
		else if((string[j]=='a'&&string[k]=='a'&&string[i]=='a')||(string[j]=='a'&&string[k]=='a'&&string[i]=='g'))
		{
			conteudo[l]='O';
		}
		else if((string[j]=='g'&&string[k]=='a'&&string[i]=='t')||(string[j]=='g'&&string[k]=='a'&&string[i]=='c'))
		{
			conteudo[l]='P';
		}
		else if((string[j]=='t'&&string[k]=='g'&&string[i]=='t')||(string[j]=='t'&&string[k]=='g'&&string[i]=='c'))
		{
			conteudo[l]='Q';
		}
		else if(string[j]=='t'&&string[k]=='g'&&string[i]=='g')
		{
			conteudo[l]='R';
		}
		else if((string[j]=='c'&&string[k]=='g'&&string[i]=='t')||(string[j]=='c'&&string[k]=='g'&&string[i]=='c')||(string[j]=='c'&&string[k]=='g'&&string[i]=='a')||(string[j]=='c'&&string[k]=='g'&&string[i]=='g')||
				(string[j]=='a'&&string[k]=='g'&&string[i]=='a')||(string[j]=='a'&&string[k]=='g'&&string[i]=='g'))
		{
			conteudo[l]='S';
		}
		else if((string[j]=='g'&&string[k]=='g'&&string[i]=='t')||(string[j]=='g'&&string[k]=='g'&&string[i]=='c')||(string[j]=='g'&&string[k]=='g'&&string[i]=='a')||(string[j]=='g'&&string[k]=='g'&&string[i]=='g'))
		{
			conteudo[l]='T';
		}
		else if((string[j]=='g'&&string[k]=='a'&&string[i]=='a')||(string[j]=='g'&&string[k]=='a'&&string[i]=='g'))
		{
			conteudo[l]='U';
		}
	}
	teste=strstr(conteudo,entrada);//verifica se os codigo dentro da sequencia "conteudo" contem os codigos de entrada"entrada",caso n existir volta NULL
	if(teste==NULL)//"teste" é um ponteiro ,entao é mais pratico usar o NULL como condição 
		printf("nao,a estrutura primaria esta ausente nesta sequencia genetica");
	else
	 	printf("sim,a estrutura primaria esta presente nesta sequencia genetica");
}
