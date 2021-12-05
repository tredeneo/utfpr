/**Desenha o ambiente (o que está representado no Model) em
 * formato texto.
 *
 * @author tacla
 */

#include "Model.hpp"
#include <cstdio>

View::View(Model *m) { model = m; }

/**Desenha o labirinto representado no modelo
*
*/
void View::desenhar() {
  printf("--- Estado do AMBIENTE ---\n");
  printf("%d,%d\n", model->pos[0], model->pos[1]);

  printf("   ");
  for (int col = 0; col < model->labir->getMaxCol(); col++) {
    printf(" %2d ", col);
  }
  printf("\n");

  for (int lin = 0; lin < model->labir->getMaxLin(); lin++) {
    printf("   ");
    for (int col = 0; col < model->labir->getMaxCol(); col++) {
      printf("+---");
    }
    printf("+\n");
    printf("%2d ", lin);
    for (int col = 0; col < model->labir->getMaxCol(); col++) {
      if (model->labir->parede[lin][col] == 1) {
        printf("|XXX"); // desenha parede
      } else if (model->pos[0] == lin && model->pos[1] == col) {
        printf("| A "); // desenha agente
      } else if (model->posObj[0] == lin && model->posObj[1] == col) {
        printf("| G ");
      } else {
        printf("|   "); // posicao vazia
      }
    }
    printf("|");
    if (lin == (model->labir->getMaxLin() - 1)) {
      printf("\n   ");
      for (int x = 0; x < model->labir->getMaxCol(); x++) {
        printf("+---");
      }
      printf("+\n");
    }
    printf("\n");
  }
}
