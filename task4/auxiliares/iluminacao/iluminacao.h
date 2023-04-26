#pragma once
#include "../../alglin/alglin.h"

class Cor
{
public:
  double r, g, b;
  Cor();
  Cor(double r, double g, double b);
};

class Intensidade
{
public:
  double r, g, b;
  Intensidade();
  Intensidade(double r, double g, double b);
};

class LuzPontual
{
public:
  Ponto Pf;
  Intensidade If;
  LuzPontual();
  LuzPontual(Ponto Pf, Intensidade If);
};

class LuzAmbiente
{
public:
  Intensidade Ia;
  LuzAmbiente();
  LuzAmbiente(Intensidade Ia);
};

Intensidade arroba(Intensidade i1, Intensidade i2);
Intensidade escalarI(Intensidade I, double k);
Intensidade somaI(Intensidade I1, Intensidade I2);