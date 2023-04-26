#pragma once
#include "../../malhas/cubo/cubo.h"
#include "../../objeto/textura.h"
#include "../../objetos/esfera/esfera.h"
#include "../../objetos/cone/cone.h"
#include "../../objetos/cilindro/cilindro.h"

#include <vector>
using std::vector;

class Complexo : public Objeto
{
public:
  vector<Objeto*> Objetos;
  Objeto* escolhido;
  Complexo();

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