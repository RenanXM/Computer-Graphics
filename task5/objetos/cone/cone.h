#pragma once
#include "../../objeto/objeto.h"

class Cone: public Objeto
{
public:
  Ponto Cb, V;
  double Rc, H;
  Vetor dc;
  bool tampa;
  int escolha;

  Cone();
  Cone(double Rc, Ponto Cb, double H, bool tampa, Vetor dc, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);

  Vetor calcN(Ponto Pi, Vetor drLuz);
  Vetor normalSup(Ponto Pi, Vetor drLuz);
  Vetor normalTampa();

  double intersecObj(Ponto P0, Vetor dr);
  double intersecSup(Ponto P0, Vetor dr);
  double intersecTampa(Ponto P0, Vetor dr);

  double escolhaObj(double tTampa, double tSuperficie);
};