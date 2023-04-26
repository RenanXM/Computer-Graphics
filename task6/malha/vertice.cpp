#include "vertice.h"

Vertice::Vertice()
{

}

Vertice::Vertice(int id, Ponto p)
{
  this->id = id;
  this->p = p;
}

void Vertice::setP(Ponto P)
{
  this->p = P;
}