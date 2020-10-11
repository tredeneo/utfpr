/** Representa um estado do problema. Neste caso, é um par ordenado que representa
 * a linha e a coluna onde se encontra o agente no labirinto.
 * @author Tacla UTFPR
 * @version 2017-08
 */

#include "Estado.hpp"

Estado::Estado(int lin, int col) {
  /** linha onde se encontra o agente */
  this->lin = lin;
  /** coluna onde se encontra o agente */
  this->col = col;
}

void Estado::setLinCol(int lin, int col) {
  this->lin = lin;
  this->col = col;
}

bool Estado::igualAo(Estado *a) {
  return (this->lin == a->lin && this->col == a->col);
}

int Estado::getLin() { return this->lin; }

int Estado::getCol() { return this->col; }

std::string Estado::getString() {
  std::stringstream ss;

  ss << std::to_string(lin) << ", " << std::to_string(col);

  return ss.str();
}
//#TODO
