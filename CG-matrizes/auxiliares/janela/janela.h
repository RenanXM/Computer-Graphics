#pragma once
#include "../../alglin/alglin.h"

class Janela{
public:
  // Centro da janela
  Ponto cj;
  Janela();
  Janela(Ponto cj);
  
  void translacao(double tx, double ty, double tz);
  void rx(double alfa);
  void ry(double alfa);
  void rz(double alfa);
  void espxy();
  void espxz();
  void espyz();

  void transformacao(Matriz m);
};