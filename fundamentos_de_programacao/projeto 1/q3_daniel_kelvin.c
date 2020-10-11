/*nome:daniel de viveiros inácio
  ra:1923820
  nome:kelvin james de souza martins 
  ra:1986813*/
#include <stdio.h>
main()
{
	char anterior, atual;
	int	milhar=0,
		centena=0,
		dezena=0,
		unidade=0,
		soma=0;
	printf("escreva o algarismo romano:\n" );
	do
	{
		scanf("%c", &atual);
		if(atual=='I')
			unidade=unidade+1;
		else if(atual=='V')
			if(anterior=='I')
				unidade=unidade+3;//como a caracter anterior ja foi somado,aqui tem que ser somado o caracter atual menos o anterior 2 vezes,5-1-1=3
			else
				unidade=unidade+5;
		else if(atual=='X')
			if(anterior=='I')
				dezena=dezena+8;//como a caracter anterior ja foi somado,aqui tem que ser somado o caracter atual menos o anterior 2 vezes,10-i-1=8
			else
				dezena=dezena+10;
		else if(atual=='L')
			if(anterior=='X')
				dezena=dezena+30;//como a caracter anterior ja foi somado,aqui tem que ser somado o caracter atual menos o anterior 2 vezes,50-10-10=30
			else
				dezena=dezena+50;
		else if(atual=='C')
			if(anterior=='X')
				dezena=dezena+80;//como a caracter anterior ja foi somado,aqui tem que ser somado o caracter atual menos o anterior 2 vezes,100-10-10=80
			else
				centena=centena+100;
		else if(atual=='D')
			if(anterior=='C')
				centena=centena+300;//como a caracter anterior ja foi somado,aqui tem que ser somado o caracter atual menos o anterior 2 vezes,500-100-100=300
			else
				centena=centena+500;
		else if(atual=='M')
			if(anterior=='C')
				milhar=milhar+800;//como a caracter anterior ja foi somado,aqui tem que ser somado o caracter atual menos o anterior 2 vezes,1000-100-100=800
			else
				milhar=milhar+1000;
		anterior=atual;
	}while(atual!='\n');
	soma=milhar+centena+dezena+unidade;
	printf("%d", soma);
}
