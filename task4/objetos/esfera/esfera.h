#pragma once

#include "../../objeto/objeto.h"

class Esfera : public Objeto
{
public:
  double r;
  Ponto c;
  Esfera();
  Esfera(double r, Ponto c, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);
  double intersecObj(Ponto P0, Vetor dr);
  Vetor calcN(Ponto Pi, Vetor dr);
};