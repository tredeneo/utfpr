//
// Created by ander on 4/17/2019.
//

#ifndef C___VIEW_HPP
#define C___VIEW_HPP

class Model;

class View {
  private:
  Model *model;

  public:
  View(Model *m);
  void desenhar();
};

#endif // C___VIEW_HPP
