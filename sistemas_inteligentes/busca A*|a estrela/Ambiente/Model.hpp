//
// Created by ander on 4/17/2019.
//

#ifndef C___MODEL_HPP
#define C___MODEL_HPP

#include "../comuns/Labirinto.hpp"
#include "../comuns/PontosCardeais.hpp"
#include "View.hpp"

class Model : public PontosCardeais {
  protected:
  int pos[2];
  int posObj[2];
  View *view;

  friend class View;

  public:
  Labirinto *labir;

  public:
  Model(int linhas, int colunas);
  void desenhar();
  int setPos(int lin, int col);
  int setObj(int lin, int col);
  void porParedeHorizontal(int ini, int fim, int linha);
  void porParedeVertical(int ini, int fim, int coluna);
  int *lerPos();
  void ir(int coord);
};

#endif // C___MODEL_HPP
