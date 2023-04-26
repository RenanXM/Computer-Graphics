#include "esfera.h"

Esfera::Esfera() {}

Esfera::Esfera(double r, Ponto c, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m):Objeto(Ke, Kd, Ka, m)
{
  this->r = r;
  this->c = c;
}

Vetor Esfera::calcN(Ponto Pi, Vetor drLuz)
{
  // Vetor n = multEscV(subP(Pi, this->c), 1 / this->r);
  // return multEscV(n, 1/Modulo(n));
  return divEscV(subP(Pi, this->c), this->r);
}

// Verifica se o raio, em teoria, bate na Esfera
double Esfera::intersecObj(Ponto P0, Vetor dr)
{
  Vetor w = subP(P0, this->c);
  double a = prodEsc(dr, dr);
  double b = 2 * prodEsc(w, dr);
  double c = prodEsc(w, w) - (this->r * this->r);

  double delta = (b * b) - (4 * a * c);
  if (delta < 0)
    return -1;

  double t1 = (-b - sqrt(delta)) / (2 * a);
  double t2 = (-b + sqrt(delta)) / (2 * a);
  if (t1 > 0)
    return t1;
  if (t2 > 0)
    return t2;
  return -1;
}