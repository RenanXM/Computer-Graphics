#pragma once
#include "math.h"

class Vetor
{
public:
  // Consideramos vetor como "coluna", a menos que esteja explicito o tipo do vetor no nome da variável
  double x, y, z;
  Vetor();
  Vetor(double x, double y, double z);
};

class Ponto
{
public:
  double x, y, z;
  Ponto();
  Ponto(double x, double y, double z);
};

class Matriz
{
public:
  // Consideramos vetor como "coluna", a menos que esteja explicito o tipo do vetor no nome da variável
  Vetor v1, v2, v3;
  Matriz();
  Matriz(Vetor v1, Vetor v2, Vetor v3);
};


double prodEsc(Vetor v1, Vetor v2);
double Modulo(Vetor v);
Vetor subV(Vetor v1, Vetor v2);
Vetor subP(Ponto P1, Ponto P2);
Vetor addV(Vetor v1, Vetor v2);
Vetor multEscV(Vetor v1, double k);
Vetor divEscV(Vetor v, double k);
Ponto addPV(Ponto p, Vetor v);

Matriz subM(Matriz A, Matriz B);
Matriz prodV(Vetor vcoluna, Vetor vlinha);
Vetor prodMV(Matriz A, Vetor vcoluna);
Vetor prodVM(Vetor vlinha, Matriz m);
Vetor prodVetorial(Vetor v, Vetor u);
Matriz identidade();