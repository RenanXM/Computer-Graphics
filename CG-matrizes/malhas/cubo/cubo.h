#pragma once
#include "../../malha/malha.h"

class Cubo: public Malha
{
public:
  Cubo();
  Cubo(double aresta, Ponto Centro, Intensidade Kd, Intensidade Ke, Intensidade Ka, double m);
  Cubo(Intensidade Kd, Intensidade Ke, Intensidade Ka, double m);
  void inicializar();
  void inicializar(double aresta, Ponto Centro);
};