#ifndef ESTADO_HPP
#define ESTADO_HPP

#include <sstream>
#include <string>

class Estado {
  private:
  int lin;
  int col;

  public:
  Estado(int lin, int col);
  void setLinCol(int lin, int col);
  bool igualAo(Estado *a);
  int getLin();
  int getCol();
  std::string getString();
};

#endif // ESTADO_HPP
