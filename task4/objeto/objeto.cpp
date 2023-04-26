#include "objeto.h"

Vetor Objeto::calcN(Ponto Pi, Vetor dr)
{
  return Vetor(1, 1, 1);
}

double Objeto::intersecObj(Ponto P0, Vetor dr)
{
  return -4000;
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