#pragma once
#include "../../alglin/alglin.h"

class Observador
{
public:
  Ponto P0;
  Observador();
  Observador(Ponto P0);
  void translacao(double tx, double ty, double tz);
  void rx(double alfa);
  void ry(double alfa);
  void rz(double alfa);
  void espxy();
  void espxz();
  void espyz();

  void transformacao(Matriz m);
};