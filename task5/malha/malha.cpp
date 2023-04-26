#include "malha.h"
#include <iostream>
Malha::Malha()
{
}

Malha::Malha(double aresta, Ponto Centro, Intensidade Kd, Intensidade Ke, Intensidade Ka, double m):Objeto(Ke, Kd, Ka, m)
{
}

void Malha::calcN_e_R1xR2(Face *f)
{
  int idVertice11 = this->arestas[f->idAresta1].idVI;
  int idVertice12 = this->arestas[f->idAresta1].idVF;

  int idVertice21 = this->arestas[f->idAresta2].idVI;
  int idVertice22 = this->arestas[f->idAresta2].idVF;

  int v1, v2, v3, n1, n;
  n1 = (idVertice11 + 1) * (idVertice12 + 1);
  n = n1 / (idVertice21 + 1);

  if (n == (idVertice11 + 1) || n == (idVertice12 + 1))
  {
    v1 = idVertice21;
    v2 = idVertice22;
    v3 = n - 1;
  }
  else
  {
    v1 = idVertice22;
    v2 = idVertice21;
    v3 = (n1 / (v1 + 1)) - 1;
  }

  Ponto P1 = this->vertices[v1].p;
  Ponto P2 = this->vertices[v2].p;
  Ponto P3 = this->vertices[v3].p;

  Vetor r1 = subP(P2, P1);
  Vetor r2 = subP(P3, P1);
  Vetor r1xr2 = prodVetorial(r1, r2);

  Vetor normal = divEscV(r1xr2, Modulo(r1xr2));
  f->setVetores(normal, r1, r2, r1xr2);
  f->setP1(P1);
}

double Malha::intersecObj(Ponto P0, Vetor dr)
{
  double ti, tmin, c1, c2;
  int idmin = 0;
  Face face;
  Vetor n, v;
  Ponto Pplano, Pi;

  tmin = -1;
  
  for (int i = 0; i < this->faces.size(); i++)
  {
    face = this->faces[i];
    n = face.n;
    if (prodEsc(dr, n) < 0)
    {
      Pplano = face.P1;
      ti = -((prodEsc(subP(P0, Pplano), n)) / prodEsc(dr, n));

      if (ti > 0)
      {
        Pi = addPV(P0, multEscV(dr, ti));
        v = subP(Pi, Pplano);
        if (prodEsc(face.r1xr2, n) != 0)
        {
          c1 = prodEsc(prodVetorial(v, face.r2), n) / prodEsc(face.r1xr2, n);
          c2 = prodEsc(prodVetorial(face.r1, v), n) / prodEsc(face.r1xr2, n);
          if ((c1 >= 0) && (c2 >= 0) && ((c1 + c2) <= 1) && ((tmin < 0) || ((tmin > 0) && (ti < tmin))))
          {
            // tplano é válido
            idmin = i;
            tmin = ti;
          }
        }
      }
    }
  }

  if (tmin > 0)
  {
    this->escolha = idmin;
    return tmin;
  }
  return -1;
}

Vetor Malha::calcN(Ponto Pi, Vetor dr)
{
  return this->faces[this->escolha].n;
}