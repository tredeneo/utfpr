//
// Created by ander on 4/17/2019.
//

#ifndef C___LABIRINTO_HPP
#define C___LABIRINTO_HPP

class Labirinto {
  protected:
  int maxCol;
  int maxLin;
  int **parede;

  friend class Model;

  friend class View;

  friend class Problema;

  public:
  Labirinto(int maxLinhas, int maxColunas);
  int getMaxLin();
  int getMaxCol();
  void porParedeHorizontal(int ini, int fim, int linha);
  void porParedeVertical(int ini, int fim, int coluna);
};

#endif // C___LABIRINTO_HPP
