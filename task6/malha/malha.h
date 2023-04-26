#pragma once
#include "../objeto/objeto.h"
#include "./vertice.h"
#include "./aresta.h"
#include "./face.h"
#include <string>
#include <vector>
using std::vector;
using std::string;

class Malha: public Objeto
{
public:
  vector<Vertice*> vertices;
  vector<Aresta*> arestas;
  vector<Face*> faces;
  int escolha;
  Malha();
  Malha(Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);
  Malha(string path, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m);

  virtual void inicializar(string path);

  // Função para inicialiar os vetores n e r1xr2 da face f
  void calcN_e_R1xR2(Face* f);
  void calcFaces();

  // Métodos sobrescritos de Objeto
  double intersecObj(Ponto P0, Vetor dr, int i) override;
  Vetor calcN(Ponto Pi, Vetor dr)override;

  // Transformação
  void translacao(double tx, double ty, double tz);
  void escala(double ex, double ey, double ez);
  void escala(double e);
  void rx(double alfa);
  void ry(double alfa);  
  void rz(double alfa);
  void espXY();
  void espXZ();
  void espYZ();
  void cisalhamentoYX(double alfa);
  void cisalhamentoXY(double alfa);
  void cisalhamentoXZ(double alfa);
  void cisalhamentoZX(double alfa);
  void cisalhamentoYZ(double alfa);
  void cisalhamentoZY(double alfa);

  void transformacaoECorrecaoFaces(Matriz m);
};