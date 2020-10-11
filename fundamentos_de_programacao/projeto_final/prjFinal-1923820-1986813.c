#include "trabalho3.h"
/*nome:daniel de viveiros in�cio
  ra:1923820
  nome:kelvin james de souza martins 
  ra:1986813*/
/**
 * função: conta a quantidade de veiculos totais e a quantidade por categoria
 *
 * Parâmetros: Imagem* img :imagem de entrada
 *             Imagem* bg :imagem do fundo
 *             int contagem :vetor que sera preenchido com a quantidade de veiculos
 *
 * Valor de Retorno: vetor com a quantidade de veiculos totais encontrado.
 **/
int contaVeiculos (Imagem* img, Imagem* bg, int contagem [N_TIPOS_DE_VEICULOS])
{
    int limiar=15,
        winSize=3;
    Imagem *imagem1,
           *imagem2;

    imagem1=criaImagem(img->largura,img->altura,1);
    imagem2=criaImagem(img->largura,img->altura,1);

    diferenca(img, bg, imagem1);

    filtroMedia(imagem1,imagem2,winSize);

    binariza(imagem2,imagem1,limiar);

    winSize=5;								//foi usado 5 pois foi o numero que deu melhor resultado
    filtroMinima(imagem1,imagem2,winSize);
    filtroRuido(imagem2,imagem1,winSize);	//
    filtroRuido(imagem1,imagem2,winSize);	//foi usado 2 vezes para diminuir mais o ruido dentro dos veiculos

    rotulo(imagem2,contagem);

    return contagem[0]+contagem[1]+contagem[2]+contagem[3];
}
/**
 * função: verifica o monor vizinho com forward scan
 *         percorre a matriz de cima para baixo,da esquerda para a direita
 *
 * Parâmetros: Imagem* img: imagem de entrada
 *             int matriz[][LAR]: matriz que representa
 *
 * Valor de Retorno: o menor valor entre os vizinhos.
 **/
void verificaVeiculo(Imagem *img,int **matriz, int r[], int aux,int contagem[])
{
    int i, j,k,cont=1,v[500];
    for(i=0; i<4; i++)
        contagem[i]=0;
    for(k=0; k<(aux); k++)
    {
        cont=0;

        for(i=75; i<666; i++)//75-666 � onde esta localizado a pista,com esses numeros ele ignora das faixas para fora
        {
            for(j=0; j<img->largura; j++)
            {
                if(matriz[i][j]==r[k])
                {
                    cont++;
                }
            }
        }
        if(cont>=21900)
        {
            contagem[3]++;
        }
        else if(cont>=6000)
        {
            contagem[2]++;
        }
        else if(cont>=4000)
        {
            contagem[1]++;
        }
        else if(cont>=1300)
        {
            contagem[0]++;
        }
    }
}
/**
 * função: verifica o monor vizinho com forward scan
 *         percorre a matriz de cima para baixo,da esquerda para a direita
 *
 * Parâmetros: int matriz[][LAR] :matriz usada para representar os objetos da imagem
 *             int i :indice da linha requerida para achar o menor vizinho
               int k :indice da coluna requrida para achar o menor vizinho
 *
 * Valor de Retorno: o menor valor entre os vizinhos.
 **/
int achaMenorcima(int **matriz,int i,int k)
{
    int menor=1000;
    if(matriz[i-1][k-1]<menor&&matriz[i-1][k-1]!=0)
    {
        menor=matriz[i-1][k-1];
    }
    if(matriz[i-1][k]<menor&&matriz[i-1][k]!=0)
    {
        menor=matriz[i-1][k];
    }
    if(matriz[i-1][k+1]<menor&&matriz[i-1][k+1]!=0)
    {
        menor=matriz[i-1][k+1];
    }
    if(matriz[i][k-1]<menor&&matriz[i][k-1]!=0)
    {
        menor=matriz[i][k-1];
    }
    return menor;
}
/**
 * função: verifica o monor vizinho com backward scan
 *         percorre a matriz de baixo para cima,da direita para a esquerda
 *
 * Parâmetros: int matriz[][LAR] :matriz usada para representar os objetos da imagem
 *             int i :indice da linha requerida para achar o menor vizinho
               int k :indice da coluna requrida para achar o menor vizinho
 *
 * Valor de Retorno: o menor valor entre os vizinhos.
 **/
int achaMenorbaixo(int **matriz,int i,int k)
{
    int menor=1000;
    if(matriz[i][k+1]<menor&&matriz[i][k+1]!=0)
        menor=matriz[i][k+1];
    if(matriz[i+1][k+1]<menor&&matriz[i+1][k+1]!=0)
        menor=matriz[i+1][k+1];
    if(matriz[i+1][k]<menor&&matriz[i+1][k]!=0)
    {
        menor=matriz[i+1][k];
    }
    if(matriz[i-1][k+1]<menor&&matriz[i-1][k+1]!=0)
    {
        menor=matriz[i-1][k+1];
    }
    return menor;
}
/**
 * função: rotula os objetos da imagem,usando o algoritmo de multi-pass
 *
 * Parâmetros: Imagem* img :imagem de entrada
 *             int contagem[] :vetor usados para armazenar a quantidade de veiculos
 *
 * Valor de Retorno: nenhum.
 **/
void rotulo(Imagem* img,int contagem[])
{
    int i,k,l,ind,
        soma,
        r=0,
        rotulos[1000]= {0},
                       aux=0,
                       **matriz;
    matriz=(int**)malloc(sizeof(int*)*img->altura);
    for(i=0;i<img->altura;i++)
        matriz[i]= (int*)malloc(sizeof(int)*img->largura);

    for(i=1; i<img->altura; i++)//
        for(k=1; k<img->largura; k++)//
            matriz[i][k]=img->dados[0][i][k];//
    for(i=0; i<img->altura; i++)
    {
        for(k=1; k<img->largura; k++)
        {
            if(matriz[i][k]!=0)
            {
                soma=matriz[i-1][k-1]+matriz[i-1][k]+matriz[i-1][k+1]+matriz[i][k-1];//verificar os vizinhos da parte de cima
                if(soma==0)
                {
                    r++;
                    matriz[i][k]=r;
                }
                else
                {
                    matriz[i][k]=achaMenorcima(matriz,i,k);//
                }
            }
        }
    }
    for(i=img->altura-2; i>=0; i--)
    {
        for(k=img->largura-2; k>=0; k--)
        {
            if(matriz[i][k]!=0)
            {
                soma=matriz[i][k+1]+matriz[i+1][k+1]+matriz[i+1][k]+matriz[i-1][k+1];//
                if(soma!=0)
                {
                    matriz[i][k]=achaMenorbaixo(matriz,i,k);//verificar os vizinhos da parte de baixo
                }
            }
        }
    }
    r=0;//
    for(i=0; i<img->altura; i++)
    {
        for(k=0; k<img->largura; k++)
        {
            if(matriz[i][k]>r)
            {
                for(l=0; l<aux; l++)
                {
                    if(rotulos[l]==matriz[i][k])
                        ind=1;
                }
                if(ind==0)
                {
                    rotulos[aux]=matriz[i][k];
                    aux++;
                    r++;
                }
                ind=0;
            }
        }
    }
    verificaVeiculo(img,matriz,rotulos,aux,contagem);
}
/**
 * função:  subtrai a imagem pelo fundo,para deixar em tons de cinza
 *
 * Parâmetros: Imagem* img :imagem de entrada
 *             Imagem* bg :imagem de fundo
 *             Imagem* out :imagem de saida
 *
 * Valor de Retorno: nenhum.
 **/
void diferenca(Imagem* img, Imagem* bg,Imagem* out)
{
    int i,k;

    for(i=0; i<img->altura; i++)
    {
        for(k=0; k<img->largura; k++)
        {
            out->dados[0][i][k]=(abs(img->dados[0][i][k]-bg->dados[0][i][k])+
                                 abs(img->dados[1][i][k]-bg->dados[1][i][k])+
                                 abs(img->dados[2][i][k]-bg->dados[2][i][k]))/3;
        }
    }
}
/**
 * função: deixa a imagem em 2 cores binarizada(255 ou 0)
 *
 * Parâmetros: Imagem* img :imagem de entrada
 *             Imagem* out :imagem de saida
 *             int limiar :valor que sera usado para binarizar,se um pixel for maior
 *              que limiar sera de uma cor,se for menor sera a outra
 *
 * Valor de Retorno: nenhum.
 **/
void binariza(Imagem* img, Imagem* out, int limiar)
{
    int i,k;
    for(i=0; i<img->altura; i++)
    {
        for(k=0; k<img->largura; k++)
        {
            if(img->dados[0][i][k]>=limiar)
            {
                out->dados[0][i][k]=255;
            }
            else
                out->dados[0][i][k]=0;
        }
    }
}
/**
 * função:  tira ruido da imagem, usando a media dos vizinhos
 *
 * Parâmetros: Imagem* img :imagem de entrada
 *             Imagem* out :imagem de saida
 *             int winSize :tamanho que sera usado para montar uma matriz para percorrer
 *
 * Valor de Retorno: nenhum.
 **/
void filtroMedia(Imagem* img, Imagem* out,int winSize)
{
    int i,k,j,h,
        soma=0,
        media;
    for(i=0; i<img->altura; i++)
    {
        for(k=0; k<img->largura; k++)
        {
            if(i<img->altura-winSize)
            {
                for(j=i; j<(winSize+i); j++)
                {
                    for(h=k; h<(winSize+k); h++)
                    {
                        soma=img->dados[0][j][h]+soma;
                    }
                }
            }
            media=soma/(winSize*winSize);
            out->dados[0][i][k]=media;
            soma=0;
        }
    }
}
/**
 * função:  tira ruido da imagem, especfico para ruido dentro dos veiculos
 *          usando o valor maximo dos vizinhos
 *
 * Parâmetros: Imagem* img :imagem de entrada
 *             Imagem* out :imagem de saida
 *             int winSize :tamanho que sera usado para montar uma matriz para percorrer
 *
 * Valor de Retorno: nenhum.
 **/
void filtroRuido(Imagem* img, Imagem* out,int winSize)
{
    int i,k,j,h,
        maxima=0;
    for(i=0; i<img->altura; i++)
    {
        for(k=0; k<img->largura; k++)
        {
            if(i<img->altura-winSize)
            {
                for(j=i; j<(winSize+i); j++)
                {
                    for(h=k; h<(winSize+k); h++)
                    {
                        if(img->dados[0][j][h]>maxima)
                            maxima=img->dados[0][j][h];
                    }
                }
            }
            out->dados[0][i][k]=maxima;
            maxima=0;
        }
    }
}/**
 * função:  tira ruido da imagem, especfico para ruido fora dos veiculos
 *          usando o valor minimo dos vizinhos
 *
 * Parâmetros: Imagem* img :imagem de entrada
 *             Imagem* out :imagem de saida
 *             int winSize :tamanho que sera usado para montar uma matriz para percorrer
 *
 * Valor de Retorno: nenhum.
 **/
void filtroMinima(Imagem* img, Imagem* out,int winSize)
{
    int i,k,j,h,
        minima=255;
    for(i=0; i<img->altura; i++)
    {
        for(k=0; k<img->largura; k++)
        {
            if(i<img->altura-winSize)
            {
                for(j=i; j<(winSize+i); j++)
                {
                    for(h=k; h<(winSize+k); h++)
                    {
                        if(img->dados[0][j][h]<minima)
                            minima=img->dados[0][j][h];
                    }
                }
            }
            out->dados[0][i][k]=minima;
            minima=255;
        }
    }
}
