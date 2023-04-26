#pragma once
#include "../auxiliares/iluminacao/iluminacao.h"

class Objeto
{
public:
  Intensidade Ke;
  Intensidade Kd;
  Intensidade Ka;
  double m; // Shininess

  // Retorna o t do ponto mais próximo do objeto em relação a P0 considerando dr
  virtual double intersecObj(Ponto P0, Vetor dr);
  virtual Vetor calcN(Ponto Pi, Vetor dr);

  Vetor calcL(Ponto Pi, Ponto Pf);
  Vetor calcR(Vetor n, Vetor l);
  Vetor calcV(Vetor dr);
};