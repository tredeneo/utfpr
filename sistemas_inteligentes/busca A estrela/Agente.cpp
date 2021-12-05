//
// Created by rul3r_t on 4/19/19.
//

#include "Agente.hpp"
#include <deque>
#include <set>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>

int Agente::ct = -1;

Agente::Agente(Model *m) : PontosCardeais() {
  this->model = m;

  prob = new Problema();

  prob->criarLabirinto(9, 9);


  prob->crencaLabir->porParedeVertical(0, 1, 0);
  prob->crencaLabir->porParedeVertical(0, 0, 1);
  prob->crencaLabir->porParedeVertical(5, 8, 1);
  prob->crencaLabir->porParedeVertical(5, 5, 2);
  prob->crencaLabir->porParedeVertical(8, 8, 2);
  prob->crencaLabir->porParedeHorizontal(4, 7, 0);
  prob->crencaLabir->porParedeHorizontal(7, 7, 1);
  prob->crencaLabir->porParedeHorizontal(3, 5, 2);
  prob->crencaLabir->porParedeHorizontal(3, 5, 3);
  prob->crencaLabir->porParedeHorizontal(7, 7, 3);
  prob->crencaLabir->porParedeVertical(6, 7, 4);
  prob->crencaLabir->porParedeVertical(5, 6, 5);
  prob->crencaLabir->porParedeVertical(5, 7, 7);

  prob->defEstIni(8, 0);

  prob->defEstObj(2, 8);

  // Posiciona o agente fisicamente no ambiente na posicao inicial
  model->setPos(8, 0);

  estAtu = new Estado(8, 0);

  nos = 0;
  ct_ja_explorados = 0;
  ct_descartados_front = 0;
}

/**
* Agente escolhe qual acao será executada em um ciclo de raciocinio.
* Observar que o agente executa somente uma acao por ciclo.
*/
int Agente::deliberar() {
  //  contador de acoes
  ct++;
  if (ct == 0) {
    std::cout << "Digite o código do Algoritmo que voce deseja executar:"
                 "\n1 - A*. \n2 - Busca de Custo Uniforme.\nDigite: ";
    int option;
    std::cin >> option;
    if (option == 1) {
      aStar();
      std::cout << "Nós gerados: " << nos << std::endl;
      std::cout << "Espacial: " << nos + ct_ja_explorados + ct_descartados_front << std::endl;
    } else {
      uniform_cost_search();
      std::cout << "Nós gerados: " << nos << std::endl;
      std::cout << "Espacial: " << nos + ct_ja_explorados + ct_descartados_front << std::endl;
    }
    std::cout << "SOLUCAO: {";
    for (int i = plan.size() - 1; i >= 0; i--) {
      std::cout << acao[plan[i]] << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << "------INICIO DO ALGORITMO------\n" << std::endl;
  }
  //@todo T2: executar o plano de acoes: SOMENTE UMA ACAO POR CHAMADA DESTE METODO
  // Ao final do plano, verifique se o agente atingiu o estado objetivo verificando
  // com o teste de objetivo

  std::cout << "Estado Atual: " << estAtu->getString() << std::endl;
  std::cout << "Proxima acao: " << acao[plan.back()] << std::endl;
  executarIr(plan.back());
  estAtu = prob->suc(estAtu, plan.back());
  plan.pop_back();

  if (this->prob->testeObjetivo(estAtu)) {
    return -1;
  } else {
    return 1;
  }
  // Se retornar -1, encerra o agente
}

/**
    * Atuador: executa 'fisicamente' a acao Ir
    * @param direcao um dos pontos cardeais
    */
int Agente::executarIr(int direcao) {
  //@todo T1 - invocar metodo do Model - atuar no ambiente
  model->ir(direcao);
  return 1; // deu certo
}

/**
 * Simula um sensor que realiza a leitura da posição atual no ambiente e
 * traduz para um par de coordenadas armazenadas em uma instância da classe
 * Estado.
 * @return Estado contendo a posição atual do agente no labirinto
 */
Estado *Agente::sensorPosicao() {
  //@todo T1 - sensor deve ler a posicao do agente no labirinto (environment)
  int *pos;
  pos = model->lerPos();
  return new Estado(pos[0], pos[1]);
}

void Agente::uniform_cost_search() {
  auto *node = new TreeNode(nullptr);
  nos++;
  node->setState(estAtu);

  std::deque<TreeNode *> frontier;
  std::set<TreeNode *> explored;

  frontier.push_front(node);

  do {
    node = frontier.front();
    frontier.pop_front();
    if (prob->testeObjetivo(node->getState())) {
      while (node->getParent() != nullptr) {
        plan.push_back(node->getAction());
        node = node->getParent();
      }
      return;
    }
    explored.insert(node);
    int *actions = prob->acoesPossiveis(node->getState());
    for (int i = 0; i < acao.size(); i++) {
      if (actions[i] == 1) {
        TreeNode *child = node->addChild();
        nos++;
        Estado *childState = prob->suc(node->getState(), i);
        custo = node->getGn() + prob->obterCustoAcao(node->getState(), i, childState);
        child->setState(childState);
        child->setGn(custo);
        child->setAction(i);

        auto isIn = [](auto conTainer, TreeNode *b) {
          for (auto itr: conTainer)
            if (b->getState()->igualAo(itr->getState()))
              return itr;
          return (TreeNode *) nullptr;
        }; // Usar iterador aqui.

        auto inFrontier = isIn(frontier, child);
        if (!isIn(explored, child) && !(isIn(frontier, child))) {
          frontier.push_front(child);
        } else if (inFrontier && (inFrontier->getFn() > child->getFn())) {
          inFrontier = child;
          ct_descartados_front++;
        }
        std::sort(frontier.begin(), frontier.end(),
                  [](TreeNode *a, TreeNode *b) {
                    return a->getFn() < b->getFn();
                  }
        );
      }
    }
  } while (!frontier.empty());
}

void Agente::aStar() {
  std::deque<TreeNode *> openSet;
  std::deque<TreeNode *> closedSet;

  auto *node = new TreeNode(nullptr);
  nos++;
  node->setState(estAtu);

  openSet.push_back(node);
  do {
    node = openSet.front();
    openSet.pop_front();
    closedSet.push_back(node);

    if (prob->testeObjetivo(node->getState())) {
      while (node->getParent() != nullptr) {
        plan.push_back(node->getAction());
        node = node->getParent();
      }
      return;
    }
    int *actions = prob->acoesPossiveis(node->getState());
    for (int i = 0; i < acao.size(); i++) {
      if (actions[i] == 1) {
        TreeNode *child = node->addChild();
        nos++;
        Estado *childState = prob->suc(node->getState(), i);
        custo = node->getGn() + prob->obterCustoAcao(node->getState(), i, childState);
        child->setState(childState);
        child->setAction(i);
        child->setGnHn(custo, h2(childState, prob->estObj));
      }
    }

    auto isIn = [](auto conTainer, TreeNode *b) {
      for (auto itr: conTainer)
        if (b->getState()->igualAo(itr->getState()))
          return itr;
      return (TreeNode *) nullptr;
    }; // Lamba expression para comparação.
    for (auto itr: node->getChildren()) {
      auto inOpenSet = isIn(openSet, itr);
      auto inClosedSet = isIn(closedSet, itr);

      if (inClosedSet) {
        ct_ja_explorados++;
        if (inClosedSet->getFn() < itr->getFn())
          continue;
      }
      if (inOpenSet) {
        if (inOpenSet->getFn() < itr->getFn()) {
          ct_descartados_front++;
          continue;
        }
      }
      openSet.push_back(itr);
    }
    std::sort(openSet.begin(), openSet.end(),
              [](TreeNode *a, TreeNode *b) {
                return a->getFn() < b->getFn();
              }
    );
  } while (!openSet.empty());
}

float Agente::h1(Estado *node, Estado *obj) {
  return (abs(node->getCol() - obj->getCol()) + abs(node->getLin() - obj->getLin()));
}

//Diagnoal
float Agente::h2(Estado *node, Estado *obj) {
  return fmax(abs(node->getCol() - obj->getCol()), abs(node->getLin() - obj->getLin()));
}