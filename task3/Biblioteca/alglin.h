#pragma once

//entendido
class Vetor
{
public:
  float x, y, z;
  Vetor();
  Vetor(float x, float y, float z);
};

//entendido
class Ponto
{
public:
  float x, y, z;
  Ponto();
  Ponto(float x, float y, float z);
};


//entendido
float prodEsc(Vetor* v1, Vetor* v2);

//entendido
float Modulo(Vetor* v);

//entendido
Vetor* subV(Vetor* v1, Vetor* v2);

//entendido
Vetor* subP(Ponto* P1, Ponto* P2);

//entendido
Vetor* addV(Vetor* v1, Vetor* v2);

//entendido
Vetor* multEscV(Vetor* v1, float k);

//entendido
Ponto* addPV(Ponto* p, Vetor* v);