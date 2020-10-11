/*nome:daniel de viveiros inácio
  ra:1923820
  nome:kelvin james de souza martins 
  ra:1986813*/
#include <stdio.h>
int diaDoAno(int ano,int mes,int dia )//função para descobrir quanto dias do ano se passaram até a data indicada
{
  int meses[12]={31,28,31,30,31,30,31,31,30,31,30,31};
   for( ;mes>1;mes--) 
  {
    dia+= meses[mes-2];
    if(mes==3 && (ano%400==0 || (ano%4==0 && ano%100)))
      dia++;
  }
  return dia;
}
main()
{
    int dia,mes,ano,teste,diaDiscord,mesDiscord,semanaDiscord,anoDiscord;
    printf("digite a data a ser convertida(formato:dia/mes/ano):");
	scanf("%d %d %d", &dia, &mes, &ano);
	
	teste=diaDoAno(ano,mes,dia);
	anoDiscord=ano+1166;
    mesDiscord=(teste/73)+1;//o resultado disso da o mes discordiano(pois cada mes tem 73 dias se dividir pelos dias do mes),como so pode ser de 0 a 4 é somado +1
	if((ano%400==0||(ano%4==0 && ano%100))||mesDiscord==1)//como mabos os calendarios são equivalentes foi usado a ano gregoriano como base pra bissexto
	{
    	diaDiscord=(teste)%74;//como o dia bissexto repete ,foi considerado que o mes tem 74 ao inves de 73
    	if(diaDiscord==60)
    	{
    		printf("data:%d / %d / %d\n", diaDiscord-1,mesDiscord,anoDiscord);//-1 pois no ano bissexto esse dia se repete/é mais longo
    		printf("Dia de Sao Tiby\n");
    	}
    	else
    		printf("data:%d / %d / %d\n", diaDiscord,mesDiscord,anoDiscord);
    	
    }
    else
    {
    	diaDiscord=teste%73;
    	printf("data:%d / %d / %d\n", diaDiscord,mesDiscord,anoDiscord);
	}
    if(diaDiscord==5 || diaDiscord==50)
    	printf("é feriado");
    	
    printf("mes:");
    if(mesDiscord==1)
        printf("Caos");
    else if(mesDiscord==2)
        printf("Discordia");
    else if(mesDiscord==3)
        printf("Confusao");
    else if(mesDiscord==4)
        printf("Burocracia");
    else if(mesDiscord==5)
        printf("Consequencias");
    printf("\n");
    
    semanaDiscord=((4+teste)%5);//como existem cindo dias da semana o resto disso da que dia da semana vai cair de 0 a 4
    printf("dia de semama:");
    if(semanaDiscord==0)
        printf("Docemanha");
    else if(semanaDiscord==1)
        printf("Horadobum");
    else if(semanaDiscord==2)
        printf("Diapicante");
    else if(semanaDiscord==3)
        printf("Espinho-espinho");
    else if(semanaDiscord==4)
        printf("Laranja Poente");
    printf("\n");
}
