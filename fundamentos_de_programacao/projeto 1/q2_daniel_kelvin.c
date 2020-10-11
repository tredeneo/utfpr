/* nome:daniel de viveiros inácio
   ra:1923820
   nome:kelvin james de souza martins 
   ra:1986813*/
#include <stdio.h>
#include <math.h>
long long int pot(int n)
{
	int i;
	long long int soma=1;
	for(i=0;i<5;i++)
	{
		soma=soma*n;
	}
	return soma;
}
int resposta(int max)
{
    int num1,num2,num3,num4,condicao;
    long long int auxiliar,pot1,pot2,pot3,pot4;
    	for(num1=1; num1<max; num1++)
		{
			pot1=pot(num1);
        	for(num2=1; num2<num1; num2++)
			{
				pot2=pot(num2);
            	for(num3=1; num3<num2; num3++)
				{
					pot3=pot(num3);
        			for(num4=1; num4<num3; num4++)
        			{
        				pot4=pot(num4);
						auxiliar=pot1+pot2+pot3+pot4;
						condicao=pow(auxiliar,0.2);
                    	if(auxiliar==pot(condicao))
						{
                        	printf("%d^5+%d^5+%d^5+%d^5=%d^5\n", num1, num2, num3,num4, condicao);
							return 0;//serve para a função parar quando encontrar um solução
                    	}
                	}

            	}          	
        	}
    	}
}
main()
{
    int max=1000;//indiferente do valor escolhido a partir do resultado(134)a função sera finalizada ao encontrar o primeiro resultado
    resposta(max);
}
