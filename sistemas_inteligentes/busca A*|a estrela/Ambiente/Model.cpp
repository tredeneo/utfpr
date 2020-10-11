/**Model implementa um ambiente na forma de um labirinto com paredes e com um
 * agente. A indexação da posição do agente é feita sempre por um
 * par ordenado (lin, col). Ver classe Labirinto.
 *
 * @author Tacla
 */
#include "Model.hpp"

/** Construtora de modelo do ambiente físico (labirinto)
   * @param linhas número de linhas do labirinto
   * @param colunas número de colunas do labirinto
   */
Model::Model(int linhas, int colunas) {
  /**Posição do agente (linha, coluna) */
  pos[0] = pos[1] = 0;
  /**Posição do objetivo (linha, coluna) */
  posObj[0] = posObj[1] = 0;
  if (linhas <= 0) {
    linhas = 5;
  }
  if (colunas <= 0) {
    colunas = 5;
  }
  /**Representação do labirinto */
  // instancia o labirinto; paredes não devem ser colocadas aqui porque
  // a classe model é utilizada para configurar varios labirintos
  labir = new Labirinto(linhas, colunas);

  /** Associação com a classe View que faz o print do labirinto */
  // instancia a visualizacao do ambiente associando-a ao model
  view = new View(this);
}

/**Faz um print do labirinto */
void Model::desenhar() { view->desenhar(); }

/**Utilizada para colocar o agente na posição inicial.
    * @param lin a linha onde o agente está situado
    * @param col a coluna onde o agente está situado
    * @return int 1 se o posicionamento é possível (dentro do labirinto e fora
    *             das paredes) e -1 se o posicionamento não é possível
   */
int Model::setPos(int lin, int col) {
  // verifica se está fora do grid
  if (col < 0 || col >= labir->getMaxCol() || lin < 0 || lin >= labir->getMaxLin())
    return -1;

  // verifica se estah sobre uma parede
  if (labir->parede[lin][col] == 1)
    return -1;

  pos[0] = lin;
  pos[1] = col;

  return 1;
}

/**Utilizada para colocar uma marca onde se encontra o estado objetivo.
     * @param lin a linha onde o agente está situado
     * @param col a coluna onde o agente está situado
     * @return int 1 se o posicionamento é possível (dentro do labirinto e fora
     *             das paredes) e -1 se o posicionamento não é possível
    */
int Model::setObj(int lin, int col) {
  // verifica se está fora do grid
  if (col < 0 || col >= labir->getMaxCol() || lin < 0 || lin >= labir->getMaxLin())
    return -1;

  // verifica se estah sobre uma parede
  if (labir->parede[lin][col] == 1)
    return -1;

  posObj[0] = lin;
  posObj[1] = col;

  return 1;
}

/**Colocar parede horizontal no labirinto.
    * @param ini: coluna inicial entre 0 e número máximo de colunas - 1
    * @param fim: coluna final (deve ser maior que a coluna inicial)
    * @param linha: em qual linha por a parede (entre 0 e máx. de linhas - 1)
    */
void Model::porParedeHorizontal(int ini, int fim, int linha) {
  labir->porParedeHorizontal(ini, fim, linha);
}

/**Constroi parede vertical
   * @param ini: linha inicial entre 0 e  máximo de linhas - 1
   * @param fim: linha final (deve ser maior que linha inicial)
   * @param coluna: em qual coluna por a parede (entre 0 e máx. de colunas - 1)
   */
void Model::porParedeVertical(int ini, int fim, int coluna) {
  labir->porParedeVertical(ini, fim, coluna);
}

/**Retorna a posição do agente no labirinto
     * @return vetor de 2 inteiros = par ordenado = [linha, coluna]
     */
int *Model::lerPos() { return pos; }


/**Coloca o agente na posição solicitada pela ação ir, desde que seja
    * possível. Não pode ultrapassar os limites do labirinto nem estar em
    * uma posição ocupada por uma parede.
    * @param coord int de 0 a 7 iniciando por N no sentido horário
    */
void Model::ir(int coord) {
  int lin = pos[0];
  int col = pos[1];

  switch (coord) {
    case N:
      lin--;
      break;
    case NE:
      col++;
      lin--;
      break;
    case L:
      col++;
      break;
    case SE:
      col++;
      lin++;
      break;
    case S:
      lin++;
      break;
    case SO:
      col--;
      lin++;
      break;
    case O:
      col--;
      break;
    case NO:
      col--;
      lin--;
      break;
    default:
      break;
  }

  // verifica se está fora do grid
  if (col < 0 || col >= labir->getMaxCol() || lin < 0 || lin >= labir->getMaxLin()) {
    lin = pos[0];
    col = pos[1];  // fica na posicao atual

  }

  // verifica se bateu em algum obstaculo
  if (labir->parede[lin][col] == 1) {
    lin = pos[0];
    col = pos[1];  // fica na posicao atual
  }

  // atribui nova posicao
  pos[0] = lin;
  pos[1] = col;
}
