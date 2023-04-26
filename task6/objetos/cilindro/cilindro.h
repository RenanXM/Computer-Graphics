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

  Vetor calcN(Ponto Pi, Vetor drLuz);
  Vetor normalTampaSup();
  Vetor normalTampaInf();
  Vetor normalSup(Ponto Pi, Vetor drLuz);
  double intersecTampaSup(Ponto P0, Vetor dr);
  double intersecTampaInf(Ponto P0, Vetor dr);
  double intersecTampa(Vetor n, Ponto P0, Vetor dr);
  double intersecSup(Ponto P0, Vetor dr);
  double intersecObj(Ponto P0, Vetor dr, int i);

  double escolhaObj(double tTampaInf, double tTampaSup, double tSuperficie, int i);

  // Transformação
  void translacao(double tx, double ty, double tz);
  void escala(double e);
  void rx(double alfa);
  void ry(double alfa);  
  void rz(double alfa);
  void espXY();
  void espXZ();
  void espYZ();

  void transformacaoSemCorrecaoDc(Matriz m);
  void transformacaoECorrecaoDc(Matriz m);
};