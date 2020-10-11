#include "arvoreb.h"

/*Se Arvore*a for uma folha, basta remover a chave de a. O procedimento copia
 * todas as chaves de i para i-1.*/
Arvore *remover_de_folha(Arvore *a, int index) {
  for (int i = index + 1; i < a->n; i++) {
    a->chaves[i - 1] = a->chaves[i];
  }
  a->n = (a->n) - 1;
  return a;
}

/*Casos 2A, 2B e 2C.
2A: Se o filho a esquerda do nó x tem no mínimo T chaves, encontramos o
predecessor de K(chave a ser removida K') e então substituimos por K por K' e
eliminamos K.

2B:Se o filho a direita do nó x tem no mínimo T chaves, encontramos o
sucessor de K(chave a ser removida K') e então substituimos por K por K' e
eliminamos K.

2C:Se os nós a direita e a esquerda tem T-1 chaves então juntamos os dois nós
que vai ter tamanho 2t-1 e eliminamos a chave K.,
*/
Arvore *remover_de_nao_folha(Arvore *a, int index) {
  TIPO k = a->chaves[index];
  TIPO predecessor, sucessor;

  if (a->filhos[index]->n >= T) {
    Arvore *aux = a->filhos[index];
    while (!(aux->folha)) {
      aux = aux->filhos[aux->n];
    }
    predecessor = aux->chaves[aux->n - 1];
    a->chaves[index] = predecessor;
    a->filhos[index] = remover(a->filhos[index], predecessor);
    printf("Caso 2A\n");
  } else if (a->filhos[index + 1]->n >= T) {
    Arvore *aux = a->filhos[index + 1];
    while (!(aux->folha)) {
      aux = aux->filhos[0];
    }
    sucessor = aux->chaves[0];
    a->chaves[index] = sucessor;
    a->filhos[index + 1] = remover(a->filhos[index + 1], sucessor);
    printf("Caso 2B\n");
  } else {
    a->filhos[index]->chaves[T - 1] = a->chaves[index];
    for (int i = 0; i < a->filhos[index + 1]->n; i++) {
      a->filhos[index]->chaves[i + T] = a->filhos[index + 1]->chaves[i];
    }

    if (a->filhos[index]->folha == 0)
      for (int i = 0; i <= a->filhos[index + 1]->n; i++) {
        a->filhos[index]->filhos[i + T] = a->filhos[index + 1]->filhos[i];
      }

    for (int i = index + 1; i < a->n; i++) {
      a->chaves[i - 1] = a->chaves[i];
    }

    for (int i = index + 2; i <= a->n; i++) {
      a->filhos[i - 1] = a->filhos[i];
    }

    a->filhos[index]->n = a->filhos[index + 1]->n + a->filhos[index]->n + 1;
    a->n = a->n - 1;
    a->filhos[index] = remover(a->filhos[index], k);
    printf("Caso 2C\n");
  }

  return a;
}

// Função para verificar se raiz ficou vazia
Arvore *verificar_raiz_vazia(Arvore *raiz) {
  /*Se após a remoção a raiz tiver 0 chaves, tornar o primeiro filho a nova raiz
   * se existir filho; caso contrário ajustar a raiz para NULL. Liberar a raiz
   * antiga*/
  if (raiz->n == 0) {
    Arvore *aux = raiz;
    if (raiz->filhos[0] != NULL) {
      raiz = raiz->filhos[0];
    } else {
      raiz = NULL;
      free(aux);
    }
    printf("OK");
  }

  return raiz;
}

/*Função que retorna o index da primeira chave maior ou igual à chave*/
int buscar_index_remocao(Arvore *a, TIPO chave) {
  int i = 0;

  /*Procurando a chave no vetor de chaves */
  while ((i < a->n) && (chave > a->chaves[i])) {
    i = i + 1;
  }

  return i;
}

/*Funcão que remove uma chave K da árvore de acordo com os casos 1, 2A, 2B, 2C e
 * 3A.*/
Arvore *remover(Arvore *a, TIPO k) {
  int index;

  /*Completar!!!!!!!!!!!!!!*/
  if (a == NULL) {
    printf("Arvore Vazia.\n");
  }

  index = buscar_index_remocao(a, k);
  // A chave a ser removida está presente neste nó
  if (index >= 0 && a->chaves[index] == k) {
    if (a->folha) {
      a = remover_de_folha(a, index);
    } else {
      a = remover_de_nao_folha(a, index);
    }
  } else {
    // Se este nó é um nó folha, então a chave não está na árvore
    int indexAux = buscar_index_remocao(a->filhos[index], k);
    if (a->folha) {
      printf("\nA chave %d não está na árvore.\n", k);
      // printf("\nA chave %d não está na árvore.\n",k);
      return a;
    } /*Caso 3A: Se a chave do filho a ser removido tem <=(T-1) chaves então
         executamos o passo 3A que "empresta" uma chave do nó pai então nó pai
         recebe uma chave do nó da esquerda ou direita e removemos do
         respectivo irmão, a chave que foi emprestado ao pai.

     */
    else if (a->filhos[index]->n <= (T - 1) &&
             a->filhos[index]->chaves[indexAux] == k) {
      printf("caso 3A \n");
      TIPO aux;
      /*
        AjusteIndex foi utilizado pois em casos onde vamos remover por exemplo o
        71, o vizinho a esquerda é a alternativa para "emprestar" a chave, porém
        da maneira como desenvolvemos o código, o irmão a esquerda do nó que
        contem a chave a ser removida trocaria o último elemento com o 80, o
        seria incorreto pois a chave 67 estaria fora de ordem. Então AjusteIndex
        serve para verificar se a chave a ser removida é maior ou menor que o a
        chave contida em [index] e então ajusta os indices.
      */
      int AjusteIndex;
      if (a->filhos[index]->chaves[index] >= a->chaves[index]) {
        AjusteIndex = 1;
      } else {
        AjusteIndex = -1;
      }
      /*
        Se o filho a esquerda tem >=T chaves então emprestamos a chave dele.
      */
      if (a->filhos[index + 1]->n >= T && (index + 1) < a->n) {
        printf("Caso 3A \n");
        aux = a->filhos[index + 1]->chaves[0];
        a->filhos[index] = inserir(a->filhos[index], a->chaves[index]);
        if (AjusteIndex == 1)
          a->chaves[index - 1] = aux;
        else
          a->chaves[index] = aux;
        a->filhos[index + 1] = remover(a->filhos[index + 1], aux);
        a->filhos[index] = remover(a->filhos[index], k);
      }
      /*
        Se o filho a esquerda tem >=T chaves então emprestamos a chave dele.
      */
      else if (a->filhos[index - 1]->n >= T && (index - 1) >= 0) {
        printf("Caso 3A \n");
        aux = a->filhos[index - 1]->chaves[a->filhos[index - 1]->n - 1];
        a->filhos[index] = inserir(a->filhos[index], a->chaves[index - 1]);
        if (AjusteIndex == 1)
          a->chaves[index] = aux;
        else
          a->chaves[index - 1] = aux;
        a->filhos[index - 1] = remover(a->filhos[index - 1], aux);
        a->filhos[index] = remover(a->filhos[index], k);
      } else {
        printf("CAso 3B:nao implementado\n");
      }
    } /* Recursão para procurar o elemento a ser removido*/
    else
      a->filhos[index] = remover(a->filhos[index], k);
  }
  a = verificar_raiz_vazia(a);

  return a;
}