//
// Created by rul3r_t on 23/04/19.
//

#include "TreeNode.hpp"

TreeNode::TreeNode(TreeNode *pai) {
  this->parent = pai;
  this->depth = 0;
  st = NULL;
  gn = 0;
  hn = 0;
}

Estado *TreeNode::getState() {
  return st;
}

int TreeNode::getDepth() {
  return this->depth;
}

void TreeNode::setState(Estado *est) {
  this->st = est;
}

std::vector<TreeNode *> TreeNode::getChildren() {
  return children;
}

TreeNode *TreeNode::getParent() {
  return parent;
}

float TreeNode::getFn() {
  return gn + hn;
}

void TreeNode::setGn(float g) {
  this->gn = g;
}

float TreeNode::getGn() {
  return gn;
}

float TreeNode::getHn() {
  return hn;
}

void TreeNode::setHn(float hn) {
  this->hn = hn;
}

void TreeNode::setAction(int a) {
  this->action = a;
}

int TreeNode::getAction() {
  return this->action;
}

/*
 * Este método instancia um nó filho de <this> e cria uma associação entre
 * o pai (this) e o filho
*/
TreeNode *TreeNode::addChild() {
  TreeNode *child = new TreeNode(this);
  child->depth = this->depth + 1;
  children.push_back(child);
  return child;
}

std::string TreeNode::gerarStr() {
  std::stringstream ss;

  ss << st->getString() << " g:" << gn << " h:" << hn << " f=" << this->getFn();

  return ss.str();
}

/*
 * Atribui valores aos atributos gn, hn e fn. fn recebe gn+hn.
 * @param gn float que representa o custo acumulado da raiz até o nó n
 * @param hn float que representa o valor da heurística de n até o nó
 *           objetivo
 */
void TreeNode::setGnHn(float gn, float hn) {
  this->gn = gn;
  this->hn = hn;
}

void TreeNode::printSubTreeRec(TreeNode *node, int nivel) {
  std::stringstream spaces;

  spaces << "%" << nivel << "s" << "";
  std::cout << spaces.str() << node->gerarStr() << std::endl;
  nivel++;
  for (auto each: node->getChildren()) {
    printSubTreeRec(each, nivel);
  }
}

/**
 * Imprime a subárvore do nó em questão (this).
 */
void TreeNode::printSubTree() {
  std::cout << "\nA R V O R E" << std::endl;
  printSubTreeRec(this, 1);
}
