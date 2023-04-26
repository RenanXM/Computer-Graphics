#include "alglin.h"
#include "math.h"

Vetor::Vetor(){}
Ponto::Ponto(){}

//entendido
Vetor::Vetor(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

//entendido
Ponto::Ponto(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
};

//entendido
float prodEsc(Vetor* v1, Vetor* v2)
{
  return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

//entendido
float Modulo(Vetor* v)
{
  return sqrt(prodEsc(v, v));
}

//entendido
Vetor* subV(Vetor* v1, Vetor* v2)
{
  return new Vetor(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

//entendido
Vetor* subP(Ponto* P1, Ponto* P2){
  return new Vetor(P1->x - P2->x, P1->y - P2->y, P1->z - P2->z);
}

//entendido
Vetor* addV(Vetor* v1, Vetor* v2)
{
  return new Vetor(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

//entendido
Vetor* multEscV(Vetor* v1, float k)
{
  return new Vetor(v1->x * k, v1->y * k, v1->z * k);
}

//entendido
Ponto* addPV(Ponto* p, Vetor* v){
  return new Ponto(p->x + v->x, p->y + v->y, p->z + v->z);
}