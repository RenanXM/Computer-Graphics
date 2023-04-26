#pragma once
#include "objeto.h"
#include "../texturapixel/texturapixel.h"

class Textura: public Objeto
{
public:
  Objeto* obj;
  Image* image;
  int larguraImage;
  int alturaImage;
  Textura();
  Textura(Objeto* obj, string path);

  double intersecObj(Ponto P0, Vetor dr, int i);
  Vetor calcN(Ponto Pi, Vetor dr);
  void intersecTextura(Ponto Pi);

  // Transformação
  void translacao(double tx, double ty, double tz);
  void escala(double ex, double ey, double ez);
  void escala(double e);
  void rx(double alfa);
  void ry(double alfa);  
  void rz(double alfa);
  void espXY();
  void espXZ();
  void espYZ();
  void cisalhamentoYX(double alfa);
  void cisalhamentoXY(double alfa);
  void cisalhamentoXZ(double alfa);
  void cisalhamentoZX(double alfa);
  void cisalhamentoYZ(double alfa);
  void cisalhamentoZY(double alfa);
};