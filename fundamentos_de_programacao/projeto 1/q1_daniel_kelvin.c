/*nome:daniel de viveiros inácio
  ra:1923820
  nome:kelvin james de souza martins 
  ra:1986813*/
#include<stdio.h>
#include <locale.h>
void calendario(int primeirodia,int totalmes,int ano,int mes)
{
	int i,
		v=9-primeirodia,
		w=10,
		x=16-primeirodia,
		y=23-primeirodia,
		z=30-primeirodia;
		if(primeirodia==0)//os laços executam apartir do numero 1,mas se o mes começar no sabado ele tem que partir do 1 \n
			printf("\n");
		if(ano==1582&&mes==10)//foi tirado alguns dias nesse mes e ano por causa da transição de calendario
			printf("");//apenas um comando para na fazer nada para que no nesse mes/ano va direto pro laço do dia 17
		else
		{
			for(i=2;i<v;i++)//com números de 2 algarismos,o espaçamento muda.
				if(primeirodia==0)
					if(i==2)//para o segundo dia do mês não ficar desalocado. 
						printf(" %d", i);
					else
						printf("%4d",i);
            	else
					printf("%4d",i);
        	printf("\n");
        	for(i=v;i<w;i++)//preenchendo as semanas do calendário.
            	printf(" %d  ",i);
			for(i=w;i<x;i++)
            	printf(" %d ",i);
    		printf("\n");
			for(i=x;i<y;i++)
        	    printf(" %d ",i);
    	}
        printf("\n");
        for(i=y;i<z;i++)
            printf(" %d ",i);
        printf("\n");
        for(i=z;i<=totalmes;i++)//acaba o calendário.
        {
        	if(primeirodia==6 && i==31 && totalmes==31)
        		printf("\n");
            printf(" %d ",i);
        }
}
int primeiromes(int mes, int ano) //congruência de Zeller.          
  {
    if (mes <= 2)
    {
      mes = mes + 10;
      ano = ano - 1;
    }
    else
    	mes = mes - 2;
    int a = ano % 100;
    int b = ano / 100;
	int resultado = (700+((26*mes-2)/10)+2+a+a/4+b/4-2*b) % 7;
    return resultado;
  }
int bissexto(int ano)
{
    if ((ano%400 == 0)||(ano%4==0 && ano%100!=0))
          return 1;
    else
          return 0;
}
main()
{
	setlocale(LC_ALL,"");//setar o C para a lingua do pc,estamos considerando q sera roda em um pc estando em portugues para o ç de março aparecer corretamente
    int ano,mes,primeirodia,ehbissexto,i,totalmes;
    char espaco=' ';
    printf("digite o mes e o ano:");
    scanf("%d %d",&mes,&ano);
    primeirodia=primeiromes(mes,ano);//descobre em qual dia da semana cai o primeiro dia do mes.
    ehbissexto=bissexto(ano);//verifica se o ano eh bissexto
    if(ehbissexto==1&&mes==2)
        totalmes=29;
    else if(ehbissexto==0&&mes==2)
        totalmes=28;
    else if(mes==4||mes==6||mes==9||mes==11)
        totalmes=30;
    else if(mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12)
        totalmes=31;
    if(mes==1)
    	printf("%6cJaneiro de ",espaco);
    else if(mes==2)
    	printf("%1cFevereiro de ",espaco);
    else if(mes==3)
    	printf("%8cMarço de ",espaco);
    else if(mes==4)
    	printf("%8cAbril de ",espaco);
    else if(mes==5)
    	printf("%8cMaio de ",espaco);
    else if(mes==6)
    	printf("%8cJunho de ",espaco);
    else if(mes==7)
    	printf("%8cJulho de ",espaco);
    else if(mes==8)
    	printf("%7cAgosto de ",espaco);
    else if(mes==9)
    	printf("%7cSetembro de ",espaco);
    else if(mes==10)
    	printf("%7cOutubro de ",espaco);
    else if(mes==11)
    	printf("%7cNovembro de ",espaco);
    else if(mes==12)
    	printf("%6cDezembro de ",espaco);
    printf("%d\n", ano );
    printf("DOM SEG TER QUA QUI SEX SAB\n");
    if(ano==1582&& mes==10)//foi tirado alguns dias nesse mes e ano por causa da transição de calendario
    	printf("                     15  16");
    else
    {
    	if(primeirodia==1)
        	printf("%c1",espaco);
    	else if(primeirodia==2)
        	printf("%5c1",espaco);
    	else if(primeirodia==3)
        	printf("%7c1",espaco);
    	else if(primeirodia==4)
        	printf("%11c1",espaco);
    	else if(primeirodia==5)
        	printf("%16c1",espaco);
    	else if(primeirodia==6)
        	printf("%21c1",espaco);
    	else if(primeirodia==0)
        	printf("%25c1",espaco);
   	}
	calendario(primeirodia,totalmes,ano,mes);//imprime o calendario
}
