#pragma once
#include "../alglin/alglin.h"

class Face
{
public:
  int id, idAresta1, idAresta2, idAresta3;
  Vetor n, r1, r2, r1xr2;
  Ponto P1;

  Face();
  Face(int id, int idAresta1, int idAresta2, int idAresta3);
  void setVetores(Vetor n, Vetor r1, Vetor r2, Vetor r1xr2);
  void setP1(Ponto P1);
};
