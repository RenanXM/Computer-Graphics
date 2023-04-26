#pragma once
#include "../objeto/objeto.h"
#include "./vertice.h"
#include "./aresta.h"
#include "./face.h"
#include <vector>
using std::vector;

class Malha: public Objeto
{
public:
  vector<Vertice> vertices;
  vector<Aresta> arestas;
  vector<Face> faces;
  int escolha;
  Malha();
  Malha(double aresta, Ponto Centro, Intensidade Kd, Intensidade Ke, Intensidade Ka, double m);

  // Função para inicialiar os vetores n e r1xr2 da face f
  void calcN_e_R1xR2(Face* f);

  // Métodos sobrescritos de Objeto
  double intersecObj(Ponto P0, Vetor dr) override;
  Vetor calcN(Ponto Pi, Vetor dr)override;
};