#include "alglin.h"
#include "iluminacao.h"

Cor::Cor() {}
Intensidade::Intensidade() {}
LuzPontual::LuzPontual() {}
LuzAmbiente::LuzAmbiente() {}

//entendido
Cor::Cor(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

//entendido
Intensidade::Intensidade(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

//entendido
LuzPontual::LuzPontual(Ponto* Pf, Intensidade* If)
{
  this->Pf = Pf;
  this->If = If;
}

//entendido
LuzAmbiente::LuzAmbiente(Intensidade* Ia)
{
  this->Ia = Ia;
}

//entendido
Intensidade* arroba(Intensidade* i1, Intensidade* i2)
{
  return new Intensidade(i1->r * i2->r, i1->g * i2->g, i1->b * i2->b);
}

//entendido 
Intensidade* escalarI(Intensidade* I, float k)
{
  return new Intensidade(I->r * k, I->g * k, I->b * k);
}

//entendido
Intensidade* somaI(Intensidade* I1, Intensidade* I2)
{
  return new Intensidade(I1->r + I2->r, I2->g + I2->g, I1->b + I2->b);
}