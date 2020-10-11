//
// Created by rul3r_t on 23/04/19.
//

#ifndef C___TREENODE_HPP
#define C___TREENODE_HPP

#include <vector>
#include "../problema/Estado.hpp"
#include <string>
#include <iostream>

class TreeNode {
  private:
  TreeNode *parent;
  std::vector<TreeNode *> children;
  int depth; // armazena a profundidade do nó
  float gn; // g(n) custo acumulado até o nó n
  float hn; // h(n) heurística a partir do nó n
  Estado *st;  // estado par <linha, coluna>
  int action; // acao que levou ao estado

  public:
  TreeNode(TreeNode *pai);
  Estado *getState();
  int getDepth();
  void setState(Estado *est);
  std::vector<TreeNode *> getChildren();
  TreeNode *getParent();
  float getFn();
  void setGn(float g);
  float getGn();
  float getHn();
  void setHn(float hn);
  void setAction(int a);
  int getAction();
  TreeNode *addChild();
  std::string gerarStr();
  void setGnHn(float gn, float hn);
  void printSubTreeRec(TreeNode *node, int nivel);
  void printSubTree();
};


#endif //C___TREENODE_HPP
