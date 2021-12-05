//
// Created by rul3r_t on 4/19/19.
//

#ifndef C___AGENTE_HPP
#define C___AGENTE_HPP

#include "comuns/PontosCardeais.hpp"
#include "Ambiente/Model.hpp"
#include "problema/Estado.hpp"
#include "problema/Problema.hpp"
#include "./arvore/TreeNode.hpp"
#include <iostream>
#include <vector>

class Agente : public PontosCardeais {
  protected:
  /* referência ao ambiente para poder atuar no mesmo*/
  Model *model;
  Estado *estAtu; // guarda o estado atual (posição atual do agente)  double custo;
  static int ct;
  Problema *prob;
  std::vector<int> plan; // Guarda plano de ações.
  float custo;
  int nos;
  int ct_ja_explorados;
  int ct_descartados_front;

  public:
  explicit Agente(Model *m);
  int deliberar();
  int executarIr(int direcao);
  Estado *sensorPosicao();
  void uniform_cost_search();
  void aStar();
  float h1(Estado *node, Estado *obj);
  float h2(Estado *node, Estado *obj);
};


#endif //C___AGENTE_HPP
