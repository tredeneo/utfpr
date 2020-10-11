#include "arvoreb.h"

/*Função principal:*/
int main() {
  int condicional = 1;  // 0 para int e 1 para char
  /*
  lembrar de mudar os parametros da constante T(arvore.h),
  TIPO(arvore.h),e escolher a função printf adequeda em
    (printArvoreb.c)linhas 14 e 15
  */
  Arvore *a = criar();
  /*Exercicio 18-2.1 Cormen*/
  if (condicional == 1) {
    a = inserir(a, 'F');
    a = inserir(a, 'S');
    a = inserir(a, 'Q');
    a = inserir(a, 'K');
    a = inserir(a, 'C');
    a = inserir(a, 'L');
    a = inserir(a, 'H');
    a = inserir(a, 'T');
    a = inserir(a, 'V');
    a = inserir(a, 'W');
    a = inserir(a, 'M');
    a = inserir(a, 'R');
    a = inserir(a, 'N');
    a = inserir(a, 'P');
    a = inserir(a, 'A');
    a = inserir(a, 'B');
    a = inserir(a, 'X');
    a = inserir(a, 'Y');
    a = inserir(a, 'D');
    a = inserir(a, 'Z');
    a = inserir(a, 'E');
    imprimir(a, 0);
    printf("\n arvore apos apenas da insercao \n \n");

    // Caso 1 : C
    // a = remover(a, 'C');

    // Caso 2A : Q
    // a = remover(a, 'Q');

    // Caso 2B : W
    // a = remover(a, 'W');

    // Caso 2C : B
    // a = remover(a, 'S');
    // a = remover(a, 'T');

    // Caso 3A : V
    // a = remover(a, 'V');

    // Caso 3B : não implementado

  } else if (condicional == 0) {
    a = inserir(a, 91);
    a = inserir(a, 90);
    a = inserir(a, 80);
    a = inserir(a, 71);
    a = inserir(a, 72);
    a = inserir(a, 50);
    a = inserir(a, 45);
    a = inserir(a, 47);
    a = inserir(a, 10);
    a = inserir(a, 8);
    a = inserir(a, 7);
    a = inserir(a, 5);
    a = inserir(a, 2);
    a = inserir(a, 3);
    a = inserir(a, 22);
    a = inserir(a, 44);
    a = inserir(a, 55);
    a = inserir(a, 66);
    a = inserir(a, 68);
    a = inserir(a, 17);
    a = inserir(a, 6);
    a = inserir(a, 21);
    a = inserir(a, 67);
    imprimir(a, 0);
    printf("\n arvore apos apenas da insercao \n");
    // Caso 1 : 22
    // a = remover(a, 22);

    // Caso 2A : 68
    // a = remover(a, 68);

    // Caso 2B : 50
    // a = remover(a, 50);

    // Caso 2C : 80
    // a = remover(a, 80);

    // Caso 3A : 45
    // a = remover(a, 45);

    // Caso 3B : não implementado
  }
  imprimir(a, 0);
  printf("\nArvore apos as operações de remocoes \n");

  return 0;
}
