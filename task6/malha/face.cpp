#include "face.h"

Face::Face()
{
}

Face::Face(int id, int idAresta1, int idAresta2, int idAresta3)
{
  this->id = id;
  this->idAresta1 = idAresta1;
  this->idAresta2 = idAresta2;
  this->idAresta3 = idAresta3;
}

void Face::setVetores(Vetor n, Vetor r1, Vetor r2, Vetor r1xr2)
{
  this->n = n;
  this->r1 = r1;
  this->r2 = r2;
  this->r1xr2 = r1xr2;
}

void Face::setP1(Ponto P1)
{
  this->P1 = P1;
}
