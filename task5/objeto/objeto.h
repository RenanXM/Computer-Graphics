#pragma once
#include "../auxiliares/iluminacao/iluminacao.h"

class Objeto
{
public:
  Intensidade Ke;
  Intensidade Kd;
  Intensidade Ka;
  double m; // Shininess
  Objeto();
  Objeto(Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);

  Vetor calcL(Ponto Pi, Ponto Pf);
  Vetor calcR(Vetor n, Vetor l);
  Vetor calcV(Vetor dr);

  // Métodos que vão ser sobrescritos
  virtual double intersecObj(Ponto P0, Vetor dr);
  virtual Vetor calcN(Ponto Pi, Vetor dr);
  virtual void intersecTextura(Ponto Pi);
};