#pragma once

#include "../../objeto/objeto.h"

class Esfera : public Objeto
{
public:
  double r;
  Ponto c;
  Esfera();
  Esfera(double r, Ponto c, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);
  double intersecObj(Ponto P0, Vetor dr, int i);
  Vetor calcN(Ponto Pi, Vetor drLuz);

  // Transformação
  void translacao(double tx, double ty, double tz);
  void escala(double e);
  void rx(double alfa);
  void ry(double alfa);  
  void rz(double alfa);
  void espXY();
  void espXZ();
  void espYZ();

  void transformacao(Matriz m);
};