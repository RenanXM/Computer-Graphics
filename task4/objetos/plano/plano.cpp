#include "plano.h"

Plano::Plano() {}

Plano::Plano(Ponto Ppi, Vetor npi, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m)
{
  this->Ppi = Ppi;
  this->npi = npi;
  this->Ke = Ke;
  this->Kd = Kd;
  this->Ka = Ka;
  this->m = m;
}

// Verifica se o raio, em teoria, bate no Plano
double Plano::intersecObj(Ponto P0, Vetor dr)
{
  Vetor w = subP(P0, this->Ppi);
  return -(prodEsc(w, this->npi) / prodEsc(dr, this->npi));
}

Vetor Plano::calcN(Ponto Pi, Vetor dr)
{
  return this->npi;
}