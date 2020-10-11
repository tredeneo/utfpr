/* daniel de viveiros inacio
 * 1923820
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
long int tamanho=0;
long int comparacao_global=0;
long int atribuicao_global=0;
typedef struct
{
    int registro;
    char nome[15];
    struct pessoa *proximo;
}Pessoa;
Pessoa *ultimo_elemento;

void inicia_lista(Pessoa *identidade)
{
    identidade->proximo = NULL;
}
void remove_no_inicio(Pessoa *identidade)
{   clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;
    Pessoa *identidade_auxiliar;

    identidade_auxiliar=identidade->proximo;
    atribuicao++;
    printf(" %s,%d",identidade_auxiliar->nome,identidade_auxiliar->registro);
    identidade_auxiliar=identidade_auxiliar->proximo;
    atribuicao++;
    identidade->proximo=identidade_auxiliar;
    atribuicao++;
    tamanho--;
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(",C(%ld),M(%ld),tempo de execucao:%.2f,posicao:%ld \n",comparacao,atribuicao,tempo_gasto,1);
}
void remove_no_meio(Pessoa *identidade)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;

    long int i,posicao;
    printf(" que posicao deseja remover de[1 ate %d]:",tamanho);
    scanf("%d",&posicao);
    if(posicao<1 || posicao >tamanho)
    {
        printf("posicao invalida");
        comparacao++;
        return ;
    }
    Pessoa *identidade_atual=identidade,
        *identidade_anterior;
    for(i=0;i<posicao;i++)
    {
        identidade_anterior=identidade_atual;
        atribuicao++;
        identidade_atual=identidade_atual->proximo;
        atribuicao++;
    }
    printf(" %s,%d",identidade_atual->nome,identidade_atual->registro);
    identidade_anterior->proximo=identidade_atual->proximo;
    atribuicao++;
    free(identidade_atual);
    tamanho--;
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(",C(%ld),M(%ld),tempo de execucao:%.2f,posicao:%ld \n",comparacao,atribuicao,tempo_gasto,i);

}
void remove_no_fim(Pessoa *identidade)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;
    long int i=1;

    Pessoa *identidade_atual;
    Pessoa *identidade_final;

    identidade_atual=identidade->proximo;
    atribuicao++;
    if(identidade->proximo==NULL)
    {
        printf("Lista vazia!\n");
        comparacao++;
    }
    else
    {
        while(identidade_atual->proximo != NULL)
        {
            identidade_final=identidade_atual;
            atribuicao++;
            identidade_atual=identidade_atual->proximo;
            atribuicao++;
            i++;
        }
        identidade_final->proximo=NULL;
        atribuicao++;
        printf(" %s,%d",identidade_atual->nome,identidade_atual->registro);
        free(identidade_atual);
    }
    tamanho--;
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(",C(%ld),M(%ld),%.2f,%ld \n",comparacao,atribuicao,tempo_gasto,i);

}
void insere_no_comeco_sem_mostrar(Pessoa *identidade,char *nome,int registro)
{
    Pessoa *identidade_novo;
    identidade_novo=(Pessoa*)malloc(sizeof(Pessoa));

    strcpy(identidade_novo->nome,nome);
    identidade_novo->registro=registro;
    tamanho++;

    identidade_novo->proximo = identidade->proximo;
    identidade->proximo = identidade_novo;
}
void insere_no_comeco(Pessoa *identidade,char *nome,int registro,int condicao)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;

    Pessoa *identidade_novo;
    identidade_novo=(Pessoa*)malloc(sizeof(Pessoa));

    strcpy(identidade_novo->nome,nome);
    atribuicao++;
    identidade_novo->registro=registro;
    atribuicao++;

    Pessoa *identidade_antigo;
    identidade_antigo= identidade->proximo;
    atribuicao++;
    identidade->proximo = identidade_novo;
    atribuicao++;
    identidade_novo->proximo = identidade_antigo;
    atribuicao++;
    tamanho++;
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    system("clear");
    if(condicao == 1)
    {
        printf(" %s,%d,C(%ld),M(%ld),%.2f,%ld \n",identidade_novo->nome,identidade_novo->registro,comparacao,atribuicao,tempo_gasto,1);
    }
}
void insere_no_meio(Pessoa *identidade)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;

    char nome[15];
    int registro;
    long int i,posicao;
    printf("em que posicao, de [2 ate %d] voce deseja inserir:",tamanho);
    scanf("%d",&posicao);
    if(posicao<1 || posicao >tamanho)
    {
        printf("posicao invalida");
        return ;
    }
    printf("escreva o nome");
    scanf("%s",&nome);
    printf("escreva o rg");
    scanf("%d",&registro);

    Pessoa *identidade_atual=identidade,
        *identidade_anterior,
        *identidade_novo;

    identidade_novo=(Pessoa*)malloc(sizeof(Pessoa));
    strcpy(identidade_novo->nome,nome);
    atribuicao++;
    identidade_novo->registro=registro;
    atribuicao++;

    for(i=0;i<posicao;i++)
    {
        identidade_anterior=identidade_atual;
        atribuicao++;
        identidade_atual=identidade_atual->proximo;
        atribuicao++;
    }
    identidade_anterior->proximo=identidade_novo;
    atribuicao++;
    identidade_novo->proximo=identidade_atual;
    atribuicao++;
    tamanho++;
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    printf(" %s,%d,C(%ld),M(%ld),tempo de execucao:%.2f,posicao:%ld \n",identidade->nome,identidade_novo->registro,comparacao,atribuicao,tempo_gasto,i+1);
}
void insere_no_final(Pessoa *identidade,char *nome,int registro,int condicao)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    double tempo_gasto;
    long int i=1;

    Pessoa *identidade_novo;
    Pessoa *identidade_atual;

    identidade_novo=(Pessoa*)malloc(sizeof(Pessoa));

    identidade_atual=identidade;

    strcpy (identidade_novo->nome,nome);
    atribuicao++;
    identidade_novo->registro=registro;
    atribuicao++;

    if(identidade_atual == NULL)
    {
        identidade_atual=identidade_atual->proximo;
        comparacao++;
        atribuicao++;
    }
    else
    {
        while(identidade_atual->proximo!= NULL)
        {
            identidade_atual=identidade_atual->proximo;
            atribuicao++;
            i++;

        }
    }
    identidade_atual->proximo=identidade_novo;
    atribuicao++;
    identidade_novo->proximo=NULL;
    atribuicao++;
    tamanho++;
    tempo_final = clock();
    tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
    system("clear");
    if(condicao== 1)
    {
        printf(" %s,%d,C(%ld),M(%ld),%.2f,%ld \n",identidade_novo->nome,identidade_novo->registro,comparacao,atribuicao,tempo_gasto,i);
    }
}
void insero_no_fim_sem_mostrar(char *nome,int registro)
{
    Pessoa *identidade_novo;
    Pessoa *identidade_atual;
    identidade_novo=(Pessoa*)malloc(sizeof(Pessoa));
    identidade_novo=(Pessoa*)malloc(sizeof(Pessoa));

    strcpy(identidade_novo->nome,nome);
    identidade_novo->registro=registro;
    tamanho++;

    identidade_atual=ultimo_elemento->proximo;

    identidade_atual->proximo=identidade_novo;
    identidade_novo->proximo = NULL;
    ultimo_elemento->proximo = identidade_novo;

}
void ler_do_arquivo(Pessoa *identidade,char *nome_arquivo)
{
    FILE *arquivo;
    char atual[25],
        nome[15],
        string_rg[10],
        caracter;
    int i,j,indicador,registro;
    long int teste=0,
             tamanho_arquivo=0;
        arquivo=fopen(nome_arquivo,"r");
    if(arquivo == NULL)
        printf(" Erro,nao foi possivel abrir o arquivo\n");
    else
        while((caracter=fgetc(arquivo))!=EOF)
            if(caracter== ',')
                tamanho_arquivo++;
    fclose(arquivo);
    arquivo=fopen(nome_arquivo,"r");
    if(arquivo == NULL)
    {
        printf(" Erro,nao foi possivel abrir o arquivo\n");
    }
    else
    {
        while((fgets(atual, sizeof(atual),arquivo))!=NULL)
        {

            i=0;
            j=0;
            while(atual[i]!=',')
            {
                nome[i]=atual[i];
                i++;
            }
            nome[i]='\0';
            i++;
            indicador=0;
            while(atual[i]!='\0')
            {
                string_rg[j]=atual[i];
                i++;
                j++;
                indicador=1;
            }
            if(indicador==1)
            {
                string_rg[j]='\0';
                registro=atoi(string_rg);
            }
            else
            {
                printf("teste,entrei");
                registro=0;
            }
            teste++;
            if(identidade->proximo == NULL)
            {
                insere_no_comeco_sem_mostrar(identidade,nome,registro);
                ultimo_elemento->proximo=identidade->proximo;
            }
            else
            {
                insero_no_fim_sem_mostrar(nome,registro);
            }
            if(teste == tamanho_arquivo)
            {
                return;
            }
        }
    }
    system("clear");
    fclose(arquivo);
}
int verifica_lista(Pessoa *identidade)
{
    if(identidade->proximo=NULL)
        return 1;
    else
        return 0;
}
void imprime_lista(Pessoa *identidade)
{
    Pessoa *identidade_atual;
    identidade_atual=identidade->proximo;
    if(identidade->proximo == NULL)
    {
        printf("Lista vazia!");
        return ;
    }
    else
    {
        printf("%s,%d\n",identidade_atual->nome,identidade_atual->registro);
        while(identidade_atual->proximo != NULL)
        {

            identidade_atual=identidade_atual->proximo;
            printf("%s,%d\n",identidade_atual->nome,identidade_atual->registro);
        }
    }
}
void salva_lista(Pessoa *identidade)
{
    FILE *arquivo;
    Pessoa *identidade_atual;
    identidade_atual=identidade->proximo;
    arquivo=fopen("lista_salva.txt","w");
    if(identidade->proximo == NULL)
    {
        printf("Lista vazia!");
        return ;
    }
    else
    {
        while(identidade_atual->proximo != NULL)
        {
            fprintf(arquivo,"%s,%d\n",identidade_atual->nome,identidade_atual->registro);
            identidade_atual=identidade_atual->proximo;
        }
        fprintf(arquivo,"%s,%d\n",identidade_atual->nome,identidade_atual->registro);
    }
    fclose(arquivo);
}
void procurar_na_lista(Pessoa *identidade)
{
    clock_t tempo_inicial,tempo_final;
    tempo_inicial = clock();
    long int atribuicao=0;
    long int comparacao=0;
    long int i=1;
    double tempo_gasto;

    int registro;
    Pessoa *identidade_atual;
    identidade_atual=identidade->proximo;
    atribuicao++;
    printf("escreva o rg que deseja procurar:");
    scanf("%d",&registro);
    if(identidade->proximo == NULL)
    {
        printf("Lista vazia!");
    }
    else
    {
        while(identidade_atual->proximo != NULL)
        {
            identidade_atual=identidade_atual->proximo;
            atribuicao++;
            if(identidade_atual->registro==registro)
            {
                comparacao++;
                tempo_final = clock();
                tempo_gasto = ((tempo_final-tempo_inicial)/((CLOCKS_PER_SEC)/1000));
                printf("%s,%d,C(%ld),M(%ld),tempo de execucao:%.2f,posicao:%ld \n",identidade_atual->nome,identidade_atual->registro,comparacao,atribuicao,tempo_gasto,i);

                return;
            }
            i++;
        }
        printf("nao possui um elemento com esse rg na lista");
    }
}
main()
{
    char nome_arquivo[]="NomeRG10.txt";
    Pessoa *identidade;
    int menu,registro;
    char nome[15];

    identidade=(Pessoa*)malloc(sizeof(Pessoa));
    ultimo_elemento=(Pessoa*)malloc(sizeof(Pessoa));

    inicia_lista(identidade);
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
        printf(" 8 para ordenar\n");
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
                printf("escreva o nome:");
                scanf("%s",&nome);
                printf("escreva o rg:");
                scanf("%d",&registro);
                insere_no_comeco(identidade,nome,registro,1);
                break;
            case 2:
                printf("escreva o nome:");
                scanf("%s",&nome);
                printf("escreva o rg:");
                scanf("%d",&registro);
                insere_no_final(identidade,nome,registro,1);
                break;
            case 3:
                insere_no_meio(identidade);
                break;
            case 4:
                remove_no_inicio(identidade);
                break;
            case 5:
                remove_no_fim(identidade);
                break;
            case 6:
                remove_no_meio(identidade);
                break;
            case 7:
                procurar_na_lista(identidade);
                break;
            case 8:
                ordena(identidade);
                break;
            case 9:
                imprime_lista(identidade);
                break;
            case 10:
                salva_lista(identidade);
                break;
            case 11:
                ler_do_arquivo(identidade,nome_arquivo);
                break;
            case 12:

                break;
        }
    }while(menu!=12);
}
