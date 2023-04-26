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

  double intersecObj(Ponto P0, Vetor dr, int i);
  double intersecSup(Ponto P0, Vetor dr);
  double intersecTampa(Ponto P0, Vetor dr);

  double escolhaObj(double tTampa, double tSuperficie, int i);

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