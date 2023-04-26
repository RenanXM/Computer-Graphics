#pragma once
#include "../../objeto/objeto.h"

class Plano : public Objeto
{
public:
  Ponto Ppi;
  Vetor npi;
  Plano();
  Plano(Ponto Ppi, Vetor npi, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);
  double intersecObj(Ponto P0, Vetor dr);
  Vetor calcN(Ponto Pi, Vetor drLuz);
};