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

  // Métodos que podem ser sobrescritos
  virtual double intersecObj(Ponto P0, Vetor dr, int i);
  virtual Vetor calcN(Ponto Pi, Vetor dr);
  virtual void intersecTextura(Ponto Pi);
  
  // Transformação
  virtual void translacao(double tx, double ty, double tz);
  virtual void escala(double ex, double ey, double ez);
  virtual void escala(double e);
  virtual void rx(double alfa);
  virtual void ry(double alfa);  
  virtual void rz(double alfa);
  virtual void espXY();
  virtual void espXZ();
  virtual void espYZ();
  virtual void cisalhamentoYX(double alfa);
  virtual void cisalhamentoXY(double alfa);
  virtual void cisalhamentoXZ(double alfa);
  virtual void cisalhamentoZX(double alfa);
  virtual void cisalhamentoYZ(double alfa);
  virtual void cisalhamentoZY(double alfa);
};