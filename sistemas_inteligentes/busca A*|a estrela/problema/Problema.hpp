#ifndef PROBLEMA_HPP
#define PROBLEMA_HPP

#include "../comuns/Labirinto.hpp"
#include "Estado.hpp"
#include "../comuns/PontosCardeais.hpp"

class Problema : public PontosCardeais {
  private:
  Estado *estIni;
  int maxLin;
  int maxCol;
  float **custo;

  public:
  Labirinto *crencaLabir;
  Estado *estObj;

  public:
  Problema();
  void criarLabirinto(int maxLinha, int maxColuna);
  void defEstIni(int lin, int col);
  void defEstObj(int lin, int col);
  Estado *suc(Estado *est, int acao);
  int *acoesPossiveis(Estado *est);
  int *acoesPossiveisSemColaterais(Estado *est);
  float obterCustoAcao(Estado *est1, int acao, Estado *est2);
  float obterCustoAcao(Estado *est1, int acao);
  bool testeObjetivo(Estado *estAtu);
};

#endif // PROBLEMA_HPP
