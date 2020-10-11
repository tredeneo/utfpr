/*============================================================================*/
/* GERADOR DE CASOS DE TESTE PARA O PROBLEMA DO CLASSIFICADOR DE VE�CULOS     */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu - nassu@dainf.ct.utfpr.edu.br                       */
/*============================================================================*/
/** Um gerador de casos de teste para o problema do classificador de ve�culos.
 * O gerador funciona abrindo uma imagem de refer�ncia e adicionando sobre ela
 * imagens de ve�culos, al�m de algum ru�do. A quantidade e os tipos de
 * ve�culos gerados � armazenada, para futura compara��o. O c�digo deste
 * m�dulo ficou um pouco "ing�nuo", porque decidi mant�-lo compacto e sem
 * precisar tratar de fatores como escala e rota��o. */
/*============================================================================*/

#include <stdlib.h>
#include <math.h>

#include "gerador_de_testes.h"

/*============================================================================*/

#define CHANCE_MOD 50 /* Quanto maior, maior a chance de gerar imagens com muitos ve�culos. */
#define PARAMETRO_SUAVIZACAO 50 /* Quanto menor, mais borradas as imagens tendem a ficar. */
#define SIGMA_RUIDO 10 /* Quanto maior, mais ru�do. */
#define DISTANCIA_ENTRE_VEICULOS 5

/* Estes par�metros se referem �s imagens usadas pelo gerador. Idealmente, este
 tipo de coisa n�o deveria ficar no fonte, mas aqui o ganho em generalidade que
 ter�amos usando um arquivo de configura��es simplesmente n�o compensaria a
 complexidade extra! */

#define BACKGROUND_FILE "gen/back1.bmp"
#define PATHS_FILE "gen/path1.bmp"

#define N_VEICULOS 7

char* VEICULOS [] =
{
	"gen/VEI1.BMP",
	"gen/VEI2.BMP",
	"gen/VEI3.BMP",
	"gen/VEI4.BMP",
	"gen/VEI5.BMP",
	"gen/VEI6.BMP",
	"gen/VEI7.BMP",
};

typedef enum
{
	MOTO,
	VEICULO_M,
	VEICULO_G,
	VEICULO_GG,
} TiposDeVeiculos;

int TIPOS_VEICULOS [] =
{
	VEICULO_G,
	VEICULO_M,
	VEICULO_M,
	MOTO,
	VEICULO_M,
	VEICULO_G,
	VEICULO_GG,
};

/*============================================================================*/

void povoaImagem (GeradorDeTestes* g, Imagem* img);
int insereVeiculo (GeradorDeTestes* g, Imagem* img, int row_v, int col_v);
Imagem* copiaImagem (Imagem* img);
void suavizaImagem (Imagem* img);
double rand_normal (double mean, double stddev);
void adicionaRuido (Imagem* img);

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)

/*============================================================================*/
/** Cria um gerador de testes.
 *
 * Par�metros: nenhum.
 *
 * Valor de retorno: ponteiro para o gerador de testes criado. */

GeradorDeTestes* criaGeradorDeTestes ()
{
	int i;
	GeradorDeTestes* g;
	g = (GeradorDeTestes*) malloc (sizeof (GeradorDeTestes));

	g->n_gerados = 0;
	for (i = 0; i < N_TIPOS_DE_VEICULOS; i++)
		g->contagem_de_veiculos [i] = 0;

	/* L� j� TODAS as imagens de ve�culos. � mais eficiente que ler tudo de novo para cada imagem gerada... */
	g->img_veiculos = (Imagem**) malloc (sizeof (Imagem*) * N_VEICULOS);
	for (i = 0; i < N_VEICULOS; i++)
	{
		g->img_veiculos [i] = abreImagem (VEICULOS [i]);
		if (!g->img_veiculos [i])
			return (NULL);
	}

	/* L� o fundo e a imagem dos caminhos. */
	g->background = abreImagem (BACKGROUND_FILE);
	g->path = abreImagem (PATHS_FILE);

	return (g);
}

/*----------------------------------------------------------------------------*/
/** Desaloca um gerador de testes.
 *
 * Par�metros: GeradorDeTestes* g: gerador de testes a destruir.
 *
 * Valor de retorno: nenhum. */

void destroiGeradorDeTestes (GeradorDeTestes* g)
{
	int i;

	free (g->background);
	free (g->path);

	/* Joga fora as imagens dos ve�culos. */
	for (i = 0; i < N_VEICULOS; i++)
		destroiImagem (g->img_veiculos [i]);
	free (g->img_veiculos);

	free (g);
}

/*----------------------------------------------------------------------------*/
/** Fun��o central do gerador, cria uma imagem de testes.
 *
 * Par�metros: GeradorDeTestes* g: o gerador a usar.
 *             int seed: a semente para o gerador de n�meros aleat�rios.
 *
 * Valor de retorno: a imagem criada. O chamador � respons�vel por desaloc�-la. */

Imagem* geraCasoDeTeste (GeradorDeTestes* g, int seed)
{
	Imagem* img;

	srand (seed);

	/* Copia a imagem do fundo. */
	img = copiaImagem (g->background);
	if (!img)
		return (NULL);

	/* Povoa a imagem com ve�culos. */
	povoaImagem (g, img);

	/* Suaviza um pouco a imagem. */
	suavizaImagem (img);

	/* Adiciona um pouco de ru�do. */
	adicionaRuido (img);

	return (img);
}

/*----------------------------------------------------------------------------*/
/** Apenas uma sub-parte da geraCasoDeTeste, esta fun��o povoa uma imagem com
 * ve�culos.
 *
 * Par�metros: GeradorDeTestes* g: o gerador usado.
 *             Imagem* img: imagem a povoar.
 *
 * Valor de retorno: nenhum. O gerador de testes passado tem v�rios campos atualizados, e a imagem � alterada. */

void povoaImagem (GeradorDeTestes* g, Imagem* img)
{
	int chance, i;
	unsigned long row, col;

	for (i = 0; i < N_TIPOS_DE_VEICULOS; i++)
		g->contagem_de_veiculos [i] = 0;
	g->n_gerados = 0;

	/* Define a chance de inserir um ve�culo em cada ponto do caminho... */
	chance = rand () % CHANCE_MOD;

	/* Percorre a imagem procurando por pixels de caminho. */
	for (row = 0; row < g->path->altura; row++)
		for (col = 0; col < g->path->largura; col++)
			if (g->path->dados [0][row][col] && rand () % 1000 < chance)
			{
				int offset = insereVeiculo (g, img, row, col);
				col += offset;
				if (offset != DISTANCIA_ENTRE_VEICULOS)
					g->n_gerados++;
			}
}

/*----------------------------------------------------------------------------*/
/** Sub-parte da povoaImagem, coloca UM ve�culo na imagem. O centro do ve�culo
 * � posicionado sobre a linha dada, com o canto esquerdo na coluna dada.
 *
 * Par�metros: GeradorDeTestes* g: o gerador usado.
 *             Imagem* img: imagem a povoar.
 *             int row_v: linha da imagem.
 *             int col_v: coluna da imagem.
 *
 * Valor de retorno: um modificador para a direita, que diz onde novos ve�culos podem aparecer. O gerador de testes passado tem alguns campos atualizados, e a imagem � alterada. */

int insereVeiculo (GeradorDeTestes* g, Imagem* img, int row_v, int col_v)
{
	unsigned long row, col;
	Imagem* img_veiculo;
	int pega_r, pega_g, pega_b;

	/* Escolhe um ve�culo para colocar na imagem... */
	int tipo_veiculo = rand () % N_VEICULOS;
	img_veiculo = g->img_veiculos [tipo_veiculo];

	/* Verifica se este ve�culo vai caber aqui... */
	if (col_v + img_veiculo->largura >= g->path->largura || !g->path->dados [0][row_v][col_v + img_veiculo->largura])
		return (DISTANCIA_ENTRE_VEICULOS);

	/* Verifica se este ve�culo vai caber aqui... */
	if (TIPOS_VEICULOS [tipo_veiculo] >= 0)
		g->contagem_de_veiculos [TIPOS_VEICULOS [tipo_veiculo]]++;

	/* Define uma varia��o de cor. Nos arquivos originais, o canal dominante �
	 o R, o G � o intermedi�rio, e o B � o canal mais fraco. Para gerar as
	 varia��es, selecionamos um canal aleat�rio da imagem original para cada
	 canal da imagem colada. */
	do
	{
		pega_r = rand () % 3;
		pega_g = rand () % 3;
		pega_b = rand () % 3;
	} while (pega_r == pega_g && pega_g == pega_b); /* Evita que os 3 canais sejam iguais. Meio irrealista, mas evitamos com isso alguns tons de cinza complicados, confundidos com o asfalto! */

	/* Cola. */
	for (row = 0; row < img_veiculo->altura; row++)
		for (col = 0; col < img_veiculo->largura; col++)
		{
			unsigned long x = col_v + col;
			unsigned long y = row_v - img_veiculo->altura/2 + row;

			if (x >= 0 && x < img->largura && y >= 0 && y < img->altura)
			{
				/* Magenta == transl�cido. */
				if (img_veiculo->dados [CANAL_R][row][col] == img_veiculo->dados [CANAL_B][row][col] &&
					img_veiculo->dados [CANAL_G][row][col] == 0)
				{
					float tone = img_veiculo->dados [CANAL_R][row][col] / 255.0f;
					img->dados [0][y][x] = (int) (img->dados [0][y][x] * tone);
					img->dados [1][y][x] = (int) (img->dados [1][y][x] * tone);
					img->dados [2][y][x] = (int) (img->dados [2][y][x] * tone);

				}
				else
				{
					img->dados [CANAL_R][y][x] = img_veiculo->dados [pega_r][row][col];
					img->dados [CANAL_G][y][x] = img_veiculo->dados [pega_g][row][col];
					img->dados [CANAL_B][y][x] = img_veiculo->dados [pega_b][row][col];
				}
			}
		}

	return (img_veiculo->largura + DISTANCIA_ENTRE_VEICULOS);
}

/*----------------------------------------------------------------------------*/
/** Cria uma c�pia da imagem dada.
 *
 * Par�metros: Imagem* img: imagem a copiar.
 *
 * Valor de retorno: uma c�pia da imagem dada, NULL se n�o puder criar. Precisa ser desalocada pelo chamador. */

Imagem* copiaImagem (Imagem* img)
{
	unsigned long i, j, k;
	Imagem* copia;

	copia = criaImagem (img->largura, img->altura, img->n_canais);

	if (!copia)
		return (NULL);

	for (i = 0; i < copia->n_canais; i++)
		for (j = 0; j < copia->altura; j++)
			for (k = 0; k < copia->largura; k++)
				copia->dados [i][j][k] = img->dados [i][j][k];

	return (copia);
}

/*----------------------------------------------------------------------------*/
/** Suaviza a imagem com um filtro 3x3. O peso do pixel central � escolhido
 * aleatoriamente, ou seja, a imagem pode ficar mais ou menos borrada.
 *
 * Par�metros: Imagem* img: imagem a suavizar.
 *
 * Valor de retorno: a imagem suavizada. */

void suavizaImagem (Imagem* img)
{
	unsigned long row, col;
	int canal, peso_centro;
	Imagem* copia; /* Precisamos guardar os dados originais. Seria bem mais eficiente guardar apenas uma janela, mas copiar tudo � bem mais simples... */
	copia = copiaImagem (img);

	peso_centro = rand () % PARAMETRO_SUAVIZACAO + 6;
	for (canal = 0; canal < img->n_canais; canal++)
		for (row = 1; row < img->altura-1; row++)
			for (col = 1; col < img->largura-1; col++)
				img->dados [canal][row][col] = (copia->dados [canal][row-1][col-1] +
				                                copia->dados [canal][row-1][col]*2 +
												copia->dados [canal][row-1][col+1] +
			                                    copia->dados [canal][row][col-1]*2 +
												copia->dados [canal][row][col]*peso_centro +
												copia->dados [canal][row][col+1]*2 +
												copia->dados [canal][row+1][col-1] +
												copia->dados [canal][row+1][col]*2 +
												copia->dados [canal][row+1][col+1])/(peso_centro + 12);
	destroiImagem (copia);
}

/*----------------------------------------------------------------------------*/
/** Adiciona ru�do a uma imagem.
 *
 * Par�metros: Imagem* img: imagem � qual adicionaremos ru�do.
 *
 * Valor de retorno: nenhum. */

void adicionaRuido (Imagem* img)
{
	unsigned long row, col, canal;

	for (canal = 0; canal < img->n_canais; canal++)
		for (row = 0; row < img->altura; row++)
			for (col = 0; col < img->largura; col++)
			{
				double ruido = rand_normal (0, SIGMA_RUIDO);
				img->dados [canal][row][col] = (unsigned char) (MIN (255, MAX (0, img->dados [canal][row][col] + ruido)));
			}
}

/*----------------------------------------------------------------------------*/
/** C�digo copiado de outro lugar para gerar n�meros aleat�rios seguindo uma
 * distribui��o normal. Original em:
 * en.literateprograms.org/Box-Muller_transform_%28C%29#chunk%20use:complete%20Box-Muller%20function */

double rand_normal (double mean, double stddev)
{
	static double n2 = 0.0;
	static int n2_cached = 0;
	if (!n2_cached) {
		double x, y, r;
		do {
			x = 2.0*rand()/RAND_MAX - 1;
			y = 2.0*rand()/RAND_MAX - 1;
			r = x*x + y*y;
		} while (r == 0.0 || r > 1.0);
		{
			double result;
			double d = sqrt(-2.0*log(r)/r);
			double n1 = x*d;
			n2 = y*d;
			result = n1*stddev + mean;
			n2_cached = 1;
			return result;
		}
	}
	else {
		n2_cached = 0;
		return n2*stddev + mean;
	}
}

/*----------------------------------------------------------------------------*/
/** Retorna uma c�pia do �ltimo background usado. A imagem deve ser desalocada
 * pelo chamador!
 *
 * Par�metros: GeradorDeTestes* g: gerador cujo background vamos copiar.
 *
 * Valor de retorno: uma c�pia do �ltimo background usado. Lembre-se de desaloc�-lo! */

Imagem* getBackground (GeradorDeTestes* g)
{
	return (copiaImagem (g->background));
}

/*----------------------------------------------------------------------------*/
/** Retorna o n�mero de ve�culos gerados na �ltima chamada ao gerador.
 *
 * Par�metros: GeradorDeTestes* g: gerador cujo n�mero de ve�culos queremos obter.
 *
 * Valor de retorno: o n�mero de ve�culos gerados. */

int pegaNVeiculosGerados (GeradorDeTestes* g)
{
	return (g->n_gerados);
}

int pegaNGerados (GeradorDeTestes* g, int tipo_veiculo)
{
	if (tipo_veiculo >= 0 && tipo_veiculo < N_TIPOS_DE_VEICULOS)
		return (g->contagem_de_veiculos [tipo_veiculo]);
	return (0);
}

/*============================================================================*/
