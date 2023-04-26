#include "iluminacao.h"

Cor::Cor() {}
Intensidade::Intensidade() {}
LuzPontual::LuzPontual() {}
LuzAmbiente::LuzAmbiente() {}

Cor::Cor(double r, double g, double b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

Intensidade::Intensidade(double r, double g, double b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

LuzPontual::LuzPontual(Ponto Pf, Intensidade If)
{
  this->Pf = Pf;
  this->If = If;
}

LuzAmbiente::LuzAmbiente(Intensidade Ia)
{
  this->Ia = Ia;
}

Intensidade arroba(Intensidade i1, Intensidade i2)
{
  return Intensidade(i1.r * i2.r, i1.g * i2.g, i1.b * i2.b);
}

Intensidade escalarI(Intensidade I, double k)
{
  return Intensidade(I.r * k, I.g * k, I.b * k);
}

Intensidade somaI(Intensidade I1, Intensidade I2)
{
  return Intensidade(I1.r + I2.r, I1.g + I2.g, I1.b + I2.b);
}