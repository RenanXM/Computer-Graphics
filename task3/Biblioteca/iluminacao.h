#pragma once
#include "alglin.h"

//entendido
class Cor
{
public:
  float r, g, b;
  Cor();
  Cor(float r, float g, float b);
};

//entendido
class Intensidade
{
public:
  float r, g, b;
  Intensidade();
  Intensidade(float r, float g, float b);
};

//entendido
class LuzPontual
{
public:
  Ponto* Pf;
  Intensidade* If;
  LuzPontual();
  LuzPontual(Ponto* Pf, Intensidade* If);
};

//entendido
class LuzAmbiente
{
public:
  Intensidade* Ia;
  LuzAmbiente();
  LuzAmbiente(Intensidade* Ia);
};

//entendido
Intensidade* arroba(Intensidade* i1, Intensidade* i2);

//entendido
Intensidade* escalarI(Intensidade* I, float k);

//entendido
Intensidade* somaI(Intensidade* I1, Intensidade* I2);