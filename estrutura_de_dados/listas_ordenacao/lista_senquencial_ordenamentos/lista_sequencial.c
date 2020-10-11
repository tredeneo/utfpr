/* daniel de viveiros inacio
 * 1923820
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
long long int atribuicao_global=0;
long long int comparacao_global=0;
typedef struct
{
    char nome[15];
    int RG;
}Pessoa;
long int insere_na_lista(Pessoa *identidade,long int tamanho,long int posicao)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int comparacao=0;
    long int atribuicao=0;
    double tempo_gasto;
    long int i;
    int registro;
    char nome[15];
    printf(" escreva o nome:");
    scanf("%s",&nome);
    atribuicao++;
    printf(" escreva o RG:");
    scanf("%d",&registro);
    atribuicao++;
    for(i=tamanho;i>posicao;i--)
    {
        strcpy(identidade[i].nome,identidade[i-1].nome);
        identidade[i].RG = identidade[i-1].RG;
        atribuicao++;
    }
    if(i==posicao)
    {
        strcpy(identidade[i].nome,nome);
        identidade[i].RG=registro;
        atribuicao++;
        comparacao++;
    }
    tamanho++;
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    system("clear");
    printf(" %s,%d,C(%ld),M(%ld),%.2f,%ld \n",identidade[i].nome,identidade[i].RG,comparacao,atribuicao,tempo_gasto,i);
    return tamanho;
}
long int remove_da_lista(Pessoa *identidade,long int tamanho,long int posicao)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;
    long int i;
    if(tamanho==0)
    {
        printf(" lista vazia\n");
        return tamanho;
    }
    tamanho--;
    printf(" %s,%d",identidade[posicao].nome,identidade[posicao].RG);
    for(i=posicao;i<tamanho;i++)
    {
        strcpy(identidade[i].nome,identidade[i+1].nome);
        identidade[i].RG = identidade[i+1].RG;
        atribuicao++;
    }
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(",C(%ld),M(%ld),tempo de execucao:%.2f,posicao:%ld \n",comparacao,atribuicao,tempo_gasto,i);
    return tamanho;
}
void procura_na_lista(Pessoa *identidade,long int tamanho)
{
    if(tamanho==0)
    {
        printf("lista vazia");
        return ;
    }
    clock_t tempo_inicial,tempo_final;
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;
    int registro,opcao;
    long int i;
    long int meio,inicio_atual,tamanho_atual;
    printf(" escreva um rg:");
    scanf("%d",&registro);
    atribuicao++;
    printf(" 1 - busca sequencial\n");
    printf(" 2 - busca binaria:");
    scanf("%d",&opcao);
    tempo_inicial = clock();
    if(opcao==1)
    {
        comparacao++;
        for(i=0;i<tamanho;i++)
        {
            comparacao++;
            if(identidade[i].RG==registro)
            {
                comparacao++;
                break;
            }
        }
    }
    if(opcao==2)
    {
        tamanho_atual=tamanho-1;
        atribuicao++;
        inicio_atual=0;
        while(inicio_atual<=tamanho_atual)
        {
            comparacao++;
            meio=(inicio_atual+tamanho_atual)/2;
            atribuicao++;
            if(registro==identidade[meio].RG)
            {
                comparacao++;
                i=meio;
                atribuicao++;
                break;
            }
            else if(identidade[meio].RG>registro)
            {
                comparacao++;
                tamanho_atual=meio-1;
                atribuicao++;
            }
            else if(identidade[meio].RG<registro)
            {
                comparacao++;
                inicio_atual=meio+1;
                atribuicao++;
            }
        }
    }
    if((i==tamanho) || (i==-1))
    {
        printf("o elemento nao esta na lista.ou a lista nao esta ordenado");
        return ;
    }
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    system("clear");
    printf(" %s,%d,C(%ld),M(%ld),%.2f,%ld \n",identidade[i].nome,identidade[i].RG,comparacao,atribuicao,tempo_gasto,i);
}
void imprime_lista(Pessoa *identidade,long int tamanho)
{
    long int i;
    system("clear");
	if(tamanho==0)
	{
		printf("Lista vazia!");
		return ;
	}
    for(i=0;i<tamanho;i++)
        printf(" %s,%d\n",identidade[i].nome,identidade[i].RG);
}
void selection_sort(Pessoa *identidade,long int tamanho)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int comparacao=0;
    long int atribuicao=0;
    double tempo_gasto;
    long int i, j, minimo;
    Pessoa atual;
    for(i=0;i<tamanho;i++)
    {
        comparacao++;
        minimo=i;
        atribuicao++;
        for(j=i+1;j<tamanho;j++)
        {
            if((identidade[j].RG)<(identidade[minimo].RG))
            {
                comparacao++;
                minimo=j;

                atribuicao++;
            }
        }
        if((identidade[i].RG)!=(identidade[minimo].RG))
        {
            comparacao++;
            atual=identidade[i];
            atribuicao++;
            identidade[i]=identidade[minimo];
            atribuicao++;
            identidade[minimo]=atual;
            atribuicao++;
        }
    }
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(" C(%ld),M(%ld),%.2f \n",comparacao,atribuicao,tempo_gasto);
}
void insertion_sort(Pessoa *identidade,long int tamanho)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int comparacao=0;
    long int atribuicao=0;
    double tempo_gasto;
    long int i, j;
    Pessoa atual;
    for(i=1;i<tamanho;i++)
    {
        comparacao++;
        atual=identidade[i];
        atribuicao++;
        for (j=i-1;(j>=0)&&(atual.RG<identidade[j].RG);j--)
        {
            comparacao++;
            identidade[j+1]=identidade[j];
            atribuicao++;
        }
        identidade[j+1]=atual;
        atribuicao++;
    }
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(" C(%ld),M(%ld),%.2f \n",comparacao,atribuicao,tempo_gasto);
}
void bubble_sort(Pessoa *identidade,long int tamanho)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int comparacao=0;
    long int atribuicao=0;
    double tempo_gasto;
    long int i,condicional=0;
    Pessoa atual;
    while(condicional == 0)
    {
        comparacao++;
        condicional=1;
        atribuicao++;
        for(i=0;i<tamanho-1;i++)
        {
            comparacao++;
            if(identidade[i+1].RG<identidade[i].RG)
            {
                comparacao++;
                atual=identidade[i];
                atribuicao++;
                identidade[i]=identidade[i+1];
                atribuicao++;
                identidade[i+1]=atual;
                atribuicao++;
                condicional=0;
                atribuicao++;
            }
        }
    }
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(" C(%ld),M(%ld),%.2f \n",comparacao,atribuicao,tempo_gasto);
}
void shell_sort(Pessoa *identidade,long long tamanho)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int comparacao=0;
    long int atribuicao=0;
    double tempo_gasto;
    long int i, j,pivo;
    pivo=1;
    Pessoa atual;

    while(pivo<tamanho)
    {
        comparacao++;
        pivo=(pivo*3)+1;
    }

    while(pivo>1)
    {
        comparacao++;
        pivo=pivo/3;
        for(i=pivo;i<tamanho;i++)
        {
            comparacao++;
            atual=identidade[i];
            atribuicao++;
            for (j=i;(j>=pivo)&&(atual.RG<identidade[j-pivo].RG);)
            {
                comparacao++;
                identidade[j]=identidade[j-pivo];
                atribuicao++;
                j=j-pivo;
            }
            identidade[j]=atual;
            atribuicao++;
        }

    }
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(" C(%ld),M(%ld),%.2f \n",comparacao,atribuicao,tempo_gasto);

}
void merge_sort(Pessoa *identidade,long long tamanho)
{
    if(tamanho>1)
    {
        comparacao_global++;
        long long i,j,k;
        long long metade=(tamanho/2);
        atribuicao_global++;
        Pessoa *identidade_primeiro;
        Pessoa *identidade_segundo;
        identidade_primeiro=(Pessoa*)malloc(sizeof(Pessoa)*metade);
        identidade_segundo=(Pessoa*)malloc(sizeof(Pessoa)*tamanho-metade);
        for(i=0;i<metade;i++)
        {
            identidade_primeiro[i]=identidade[i];
            atribuicao_global++;
        }
        for(j=0;i<tamanho;i++,j++)
        {
            identidade_segundo[j]=identidade[i];
            atribuicao_global++;
        }
        merge_sort(identidade_primeiro,metade);
        merge_sort(identidade_segundo,tamanho-metade);
        i=0;
        j=0;
        k=0;
        while((i<metade)&&(j<tamanho-metade))
        {
            if(identidade_primeiro[i].RG<identidade_segundo[j].RG)
            {
                comparacao_global++;
                identidade[k]=identidade_primeiro[i];
                atribuicao_global++;
                i++;
            }
            else
            {
                comparacao_global++;
                identidade[k]=identidade_segundo[j];
                atribuicao_global++;
                j++;
            }
            k++;
        }
        while(i<metade)
        {
            identidade[k]=identidade_primeiro[i];
            atribuicao_global++;
            i++;
            k++;
        }
        while(j<(tamanho-metade))
        {
            identidade[k]=identidade_segundo[j];
            atribuicao_global++;
            j++;
            k++;
        }
        free(identidade_primeiro);
        free(identidade_segundo);
    }
}
void quick_sort(Pessoa *identidade,long int tamanho)
{
    long int *inicio,*fim,i,esquerda,direita,media;
    media=(identidade[0].RG+identidade[tamanho-1].RG)/2;
    inicio=(long int*)malloc(sizeof(long int)*tamanho);
    fim=(long int*)malloc(sizeof(long int)*tamanho);
    Pessoa pivo;
    i=0;
    atribuicao_global++;
    inicio[0]=0;
    atribuicao_global++;
    fim[0]=tamanho;
    atribuicao_global++;
    while(i>=0)
    {
        esquerda=inicio[i];
        atribuicao_global++;
        direita=fim[i]-1;
        atribuicao_global++;
        if(esquerda<direita)
        {
            comparacao_global++;
            pivo=identidade[esquerda];
            pivo=identidade[media];
            atribuicao_global++;
            if(i==tamanho-1)
            {
                comparacao_global++;
                return ;
            }
            while(esquerda<direita)
            {
                while(identidade[direita].RG>=pivo.RG && esquerda<direita)
                {
                    direita--;
                }
                if(esquerda<direita)
                {
                    comparacao_global++;
                    identidade[esquerda++]=identidade[direita];
                    atribuicao_global++;
                }
                while(identidade[esquerda].RG<=pivo.RG && esquerda<direita)
                {
                    esquerda++;
                }
                if(esquerda<direita)
                {
                    comparacao_global++;
                    identidade[direita--]=identidade[esquerda];
                    atribuicao_global++;
                }
            }
            identidade[esquerda]=pivo;
            atribuicao_global++;
            inicio[i+1]=esquerda+1;
            atribuicao_global++;
            fim[i+1]=fim[i];
            atribuicao_global++;
            fim[i++]=esquerda;
            atribuicao_global++;
        }
        else
        {
            comparacao_global++;
            i--;
        }
    }
}
void ordena(Pessoa *identidade,long long tamanho)
{
    clock_t tempo_inicial,tempo_final;
    double tempo_gasto;
    int menu_ordena;
    atribuicao_global=0;
    comparacao_global=0;
    printf("\n");
    printf(" 1 para Selection-Sort \n");
    printf(" 2 para Insertion-Sort \n");
    printf(" 3 para Bubble-Sort \n");
    printf(" 4 para Shell-Sort \n");
    printf(" 5 para Quick-Sort \n");
    printf(" 6 para Merge-Sort \n");
    printf(" escreva um numero do menu:");
    scanf("%d",&menu_ordena);
    switch (menu_ordena)
    {
        case 1:
            selection_sort(identidade,tamanho);
            break;
        case 2:
            insertion_sort(identidade,tamanho);
            break;
        case 3:
            bubble_sort(identidade,tamanho);
            break;
        case 4:
            shell_sort(identidade,tamanho);
            break;
        case 5:
            tempo_inicial = clock();
            comparacao_global=0;
            atribuicao_global=0;
            quick_sort(identidade,tamanho);
            tempo_final = clock();
            tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
            printf(" C(%ld),M(%ld),%.2f \n",comparacao_global,atribuicao_global,tempo_gasto);
            break;
        case 6:
            tempo_inicial = clock();
            comparacao_global=0;
            atribuicao_global=0;
            merge_sort(identidade,tamanho);
            tempo_final = clock();
            tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
            printf(" C(%ld),M(%ld),%.2f \n",comparacao_global,atribuicao_global,tempo_gasto);
            break;
    }
}
main()
{
    FILE *arquivo;
    char caracter,
        atual[25],
        string_rg[10],
        nome_arquivo[]="NomeRG100M.txt";
    long int tamanho=0,tamanho_arquivo=0,k=0,posicao;
    int i,j,indicador,menu;
    Pessoa *identidade;
    identidade=(Pessoa*)malloc(sizeof(Pessoa)*1);
    do
    {
        printf("\n");
        printf(" 1 para inserir no comeco da lista\n");
        printf(" 2 para inserir no final da lista\n");
        printf(" 3 para inserir em posicao qualquer da lista\n");
        printf(" 4 para remover do inicio da lista \n");
        printf(" 5 para remover do final da lista\n");
        printf(" 6 para remover da posicao qualquer da lista\n");
        printf(" 7 para procurar uma pessoa na lista pelo RG\n");
        printf(" 8 para ordenar \n");
        printf(" 9 para mostrar a lista\n");
        printf(" 10 para salvar a lista em um arquivo\n");
        printf(" 11 para ler o arquivo e armazenar em uma lista\n");
        printf(" 12 para sair do programa \n");
        printf(" escreva um numero do menu:");
        scanf("%d",&menu);
        printf("\n");
        switch (menu)
        {
            case 1:
                identidade=(Pessoa*)realloc(identidade,(tamanho+1)*sizeof(Pessoa));
                tamanho=insere_na_lista(identidade,tamanho,0);
                break;
            case 2:
                identidade=(Pessoa*)realloc(identidade,(tamanho+1)*sizeof(Pessoa));
                tamanho=insere_na_lista(identidade,tamanho,tamanho);
                break;
            case 3:
                do
                {
                    printf(" escreva a posicao que quer adicionar:");
                    scanf("%d",&posicao);
                    posicao--;
                    if(posicao<0)
                    {
                        posicao=tamanho+1;
                    }
                }while(posicao>tamanho);
                identidade=(Pessoa*)realloc(identidade,(tamanho+1)*sizeof(Pessoa));
                tamanho=insere_na_lista(identidade,tamanho,posicao);
                break;
            case 4:
                tamanho=remove_da_lista(identidade,tamanho,0);
                break;
            case 5:
                tamanho=remove_da_lista(identidade,tamanho,tamanho);
                break;
            case 6:
                do
                {
                    printf(" escreva a posicao que quer remover:");
                    scanf("%d",&posicao);
                    posicao--;
                    if(posicao<0)
                    {
                        posicao=tamanho+1;
                    }
                }while(posicao>tamanho);
                tamanho=remove_da_lista(identidade,tamanho,posicao);
                break;
            case 7:
                procura_na_lista(identidade,tamanho);
                break;
            case 8:
                ordena(identidade,tamanho);
                break;
            case 9:
                imprime_lista(identidade,tamanho);
                break;
            case 10:
                arquivo=fopen("lista_salva.txt","w");
                for(i=0;i<tamanho;i++)
                    fprintf(arquivo,"%s,%d\n",identidade[i].nome,identidade[i].RG);
                fclose(arquivo);
                break;
            case 11:
                arquivo=fopen(nome_arquivo,"r");
                if(arquivo == NULL)
                    printf(" Erro,nao foi possivel abrir o arquivo\n");
                else
                    while((caracter=fgetc(arquivo))!=EOF)
                        if(caracter== '\n')
                            tamanho_arquivo++;
                fclose(arquivo);
                identidade=(Pessoa*)realloc(identidade,(tamanho+tamanho_arquivo+1)*sizeof(Pessoa));
                arquivo=fopen(nome_arquivo,"r");
                k=tamanho;
                if(arquivo == NULL)
                    printf(" Erro, nao foi possivel abrir o arquivo\n");
                else
                    while( (fgets(atual, sizeof(atual), arquivo))!=NULL )
                    {
                        i=0;
                        j=0;
                        int p=0;
                        int condicao=0;
                        while(atual[p]!= '\n')
                        {
                            if(atual[p]== ',')
                                condicao=1;
                            p++;
                        }
                        if(condicao==0)
                            continue ;
                        while(atual[i]!= ',')
                        {
                            identidade[k].nome[i]=atual[i];
                            i++;
                        }
                        identidade[k].nome[i]='\0';
                        i++;
                        indicador=0;
                        while(atual[i]!= '\0')
                        {
                            string_rg[j]=atual[i];
                            i++;
                            j++;
                            indicador++;
                        }
                        if(indicador!=0)
                        {
                            string_rg[j]='\0';
                            identidade[k].RG=atoi(string_rg);
                        }
                        else
                        {
                            identidade[k].RG=0;
                        }
                        k++;
                    }
                fclose(arquivo);
                tamanho+=tamanho_arquivo;
                tamanho_arquivo=0;
                break;
            case 12:
                free(identidade);
                break;
        }
    }while(menu!=12);
}
