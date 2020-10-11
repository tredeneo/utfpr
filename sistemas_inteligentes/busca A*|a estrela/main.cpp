#include <cstdio>
#include <iostream>
#include <vector>

#include "Agente.hpp"
#include "Ambiente/Model.hpp"
#include <cstdlib>
#include <unistd.h>
#include <deque>
#include <algorithm>
#include <iostream>

int main() {
  // Cria o ambiente (modelo) = labirinto com suas paredes
  auto *model = new Model(9, 9);
  model->labir->porParedeVertical(0, 1, 0);
  model->labir->porParedeVertical(0, 0, 1);
  model->labir->porParedeVertical(5, 8, 1);
  model->labir->porParedeVertical(5, 5, 2);
  model->labir->porParedeVertical(8, 8, 2);
  model->labir->porParedeHorizontal(4, 7, 0);
  model->labir->porParedeHorizontal(7, 7, 1);
  model->labir->porParedeHorizontal(3, 5, 2);
  model->labir->porParedeHorizontal(3, 5, 3);
  model->labir->porParedeHorizontal(7, 7, 3);
  model->labir->porParedeVertical(6, 7, 4);
  model->labir->porParedeVertical(5, 6, 5);
  model->labir->porParedeVertical(5, 1, 2);
  // seta a posição inicial do agente no ambiente - nao interfere no
  // raciocinio do agente, somente no amibente simulado
  model->setPos(8, 0);
  model->setObj(2, 8);

  // Cria um agente
  auto *ag = new Agente(model);

  // Ciclo de execucao do sistema
  // desenha labirinto
  model->desenhar();

  // agente escolhe proxima açao e a executa no ambiente (modificando
  // o estado do labirinto porque ocupa passa a ocupar nova posicao)

  printf("\n*** Inicio do ciclo de raciocinio do agente ***\n\n");
  while (ag->deliberar() != -1) {
    usleep(900000);
    model->desenhar();
  }


  return 0;
}
