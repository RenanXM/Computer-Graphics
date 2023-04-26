#pragma once
#include "../../objeto/objeto.h"

class Cilindro: public Objeto{
public:
  Ponto Cb, Ct;
  double Rc, H;
  Vetor dc;
  bool tampaInf, tampaSup;
  int escolha;
  Cilindro();
  Cilindro(double Rc, double H, Ponto Cb, Vetor dc, bool Tinf, bool Tsup, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);

  Vetor calcN(Ponto Pi, Vetor dr);
  Vetor normalTampaSup();
  Vetor normalTampaInf();
  Vetor normalSup(Ponto Pi, Vetor dr);
  double intersecTampaSup(Ponto P0, Vetor dr);
  double intersecTampaInf(Ponto P0, Vetor dr);
  double intersecTampa(Vetor n, Ponto P0, Vetor dr);
  double intersecSup(Ponto P0, Vetor dr);
  double intersecObj(Ponto P0, Vetor dr);

  double escolhaObj(double tTampaInf, double tTampaSup, double tSuperficie);
};