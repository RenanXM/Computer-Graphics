#pragma once
#include "math.h"

class Vetor
{
public:
  // Consideramos vetor como "coluna", a menos que esteja explicito o tipo do vetor no nome da variável
  double x, y, z, d;
  Vetor();
  Vetor(double x, double y, double z);
  Vetor(double x, double y, double z, double d);
};

class Ponto
{
public:
  double x, y, z, d;
  Ponto();
  Ponto(double x, double y, double z);
};

class Matriz
{
public:
  // Consideramos vetor como "coluna", a menos que esteja explicito o tipo do vetor no nome da variável
  Vetor v1, v2, v3, v4;
  Matriz();
  Matriz(Vetor v1, Vetor v2, Vetor v3, Vetor v4);
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
Matriz somaM(Matriz A, Matriz B);
Matriz prodV(Vetor vcoluna, Vetor vlinha);
double prodLinhaColuna(Vetor vlinha, Vetor vcoluna);
Matriz prodMM(Matriz A, Matriz B);
Vetor prodMV(Matriz A, Vetor vcoluna);
Ponto prodMP(Matriz m, Ponto p);
Vetor prodVM(Vetor vlinha, Matriz m);
Vetor prodVetorial(Vetor v, Vetor u);
Matriz identidade();

Matriz Mtranslacao(double tx, double ty, double tz);
Matriz Mescala(double ex, double ey, double ez);
Matriz Mescala(double e);
Matriz Mrx(double alfa);
Matriz Mry(double alfa);
Matriz Mrz(double alfa);
Matriz Mespxy();
Matriz Mespxz();
Matriz Mespyz();
Matriz Mcisyx(double alfa);
Matriz Mcisxy(double alfa);
Matriz Mcisxz(double alfa);
Matriz Mciszx(double alfa);
Matriz Mcisyz(double alfa);
Matriz Mciszy(double alfa);

Matriz CorrecaoCisyx(double alfa);
Matriz CorrecaoCisxy(double alfa);
Matriz CorrecaoCisxz(double alfa);
Matriz CorrecaoCiszx(double alfa);
Matriz CorrecaoCisyz(double alfa);
Matriz CorrecaoCiszy(double alfa);
Matriz CorrecaoEscalaNaoUniforme(double ex, double ey, double ez);