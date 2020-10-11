#include "arvoreb.h"

/*Repartimos o nó cheio y que é filho de x em torno da sua chave mediana, que
 * sobre para o nó x. As chaves de y maiores que a mediana sao transferidas para
 * m novo nó z que se torna filho de x.*/
Arvore *dividir_no(Arvore *x, int i, Arvore *y) {
  Arvore *z = criar();
  z->folha = y->folha;
  z->n = T - 1;

  for (int j = 0; j < T - 1; j++) {
    z->chaves[j] = y->chaves[j + T];
  }

  if (y->folha == 0) {
    for (int j = 0; j < T; j++) {
      z->filhos[j] = y->filhos[j + T];
    }
  }

  y->n = T - 1;

  for (int j = x->n; j >= i + 1; j--) {
    x->filhos[j + 1] = x->filhos[j];
  }

  x->filhos[i + 1] = z;

  for (int j = x->n - 1; j >= i; j--) {
    x->chaves[j + 1] = x->chaves[j];
  }
  x->chaves[i] = y->chaves[T - 1];
  x->n = x->n + 1;

  return x;
}

/* Caso x seja um nó folha, inserimos a chave K em x, caso contrário inserimos k
 * no nó folha adequado da subárvore filho de x.*/
Arvore *inserir_arvore_nao_cheia(Arvore *x, TIPO k) {
  int i;
  i = (x->n) - 1;
  if (x->folha) {
    while ((i >= 0) && (k < x->chaves[i])) {
      x->chaves[i + 1] = x->chaves[i];
      i--;
    }
    x->chaves[i + 1] = k;
    x->n = x->n + 1;

  } else {
    while ((i >= 0) && (k < x->chaves[i])) {
      i--;
    }
    i++;
    if (x->filhos[i]->n == (2 * T) - 1) {
      dividir_no(x, i, x->filhos[i]);
      if (k > x->chaves[i]) {
        i++;
      }
    }
    x->filhos[i] = inserir_arvore_nao_cheia(x->filhos[i], k);
  }
  return x;
}

/*Função para inserir uma chave em uma árvore B:*/
Arvore *inserir(Arvore *raiz, TIPO chave) {
  Arvore *r = raiz;
  if (r->n == (2 * T - 1)) {
    Arvore *s = criar();
    s->folha = FALSE;
    s->filhos[0] = r;
    s = dividir_no(s, 0, r);
    s = inserir_arvore_nao_cheia(s, chave);
    return s;
  } else {
    return inserir_arvore_nao_cheia(r, chave);
  }
}
