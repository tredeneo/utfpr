/**Labirinto representa um labirinto com paredes. A indexação das posições do
 * labirinto é dada por par ordenado (linha, coluna). A linha inicial é zero e
 * a linha máxima é (maxLin - 1). A coluna inicial é zero e a máxima é
 * (maxCol - 1).
 *
 * @author Tacla
 */
#include "Labirinto.hpp"

Labirinto::Labirinto(int maxLinhas, int maxColunas) {
  /*Número máximo de colunas do labirinto */
  this->maxCol = maxColunas;
  /*Número máximo de linhas do labirinto */
  this->maxLin = maxLinhas;

  /*Array que representa o labirinto sendo as posições = 1 aquelas que
      contêm paredes */
  parede = new int *[maxLin];
  for (int i = 0; i < maxLin; i++) {
    parede[i] = new int[maxCol];
  }
}

int Labirinto::getMaxLin() { return maxLin; }

int Labirinto::getMaxCol() { return maxCol; }

/** Constroi parede horizontal da coluna inicial até a final na linha indicada.
 * @param ini: coluna inicial entre 0 e número máximo de colunas - 1
 * @param fim: coluna final (deve ser maior que coluna inicial)
 * @param linha: em qual linha colocar a parede (entre 0 e máx. de linhas - 1)
 */
void Labirinto::porParedeHorizontal(int ini, int fim, int linha) {
  if (fim >= ini && ini >= 0 && fim < maxCol && linha >= 0 && linha < maxLin) {
    for (int c = ini; c <= fim; c++) {
      parede[linha][c] = 1;
    }
  }
}

/** Constroi parede vertical da linha inicial até a final na coluna indicada.
 * até a final
* @param ini: linha inicial entre 0 e  máximo de linhas - 1
* @param fim: linha final (deve ser maior do que linha inicial)
* @param coluna: em qual coluna colocar a parede (entre 0 e máx. de colunas - 1)
*/
void Labirinto::porParedeVertical(int ini, int fim, int coluna) {
  if (fim >= ini && ini >= 0 && fim < maxLin && coluna >= 0 && coluna < maxCol) {
    for (int l = ini; l <= fim; l++) {
      parede[l][coluna] = 1;
    }
  }
}
