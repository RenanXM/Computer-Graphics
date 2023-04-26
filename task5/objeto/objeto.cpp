#include "objeto.h"
Objeto::Objeto(){}

Objeto::Objeto(Intensidade Ke, Intensidade Kd, Intensidade Ka, double m)
{
  this->Ke = Ke;
  this->Kd = Kd;
  this->Ka = Ka;
  this->m = m;
}
Vetor Objeto::calcN(Ponto Pi, Vetor dr)
{
  return Vetor(1, 1, 1);
}

double Objeto::intersecObj(Ponto P0, Vetor dr)
{
  return -1;
}


void Objeto::intersecTextura(Ponto Pi)
{
}

Vetor Objeto::calcL(Ponto Pi, Ponto Pf)
{
  return divEscV(subP(Pf, Pi), Modulo(subP(Pf, Pi)));
}

Vetor Objeto::calcR(Vetor n, Vetor l)
{
  // Vetor r = subV(multEscV(n, 2 * prodEsc(l, n)), l);
  // return multEscV(r, 1/Modulo(r));
  return subV(multEscV(n, 2 * prodEsc(l, n)), l);
}

Vetor Objeto::calcV(Vetor dr)
{
  return divEscV(dr, -Modulo(dr));
}