#include "cubo.h"
Cubo::Cubo(){}

Cubo::Cubo(double aresta, Ponto Centro, Intensidade Kd, Intensidade Ke, Intensidade Ka, double m): Malha(aresta, Centro, Kd, Ke, Ka, m)
{
  this->inicializar(aresta, Centro);
}

void Cubo::inicializar(double aresta, Ponto Centro)
{
  double x = Centro.x;
  double y = Centro.y;
  double z = Centro.z;
  double metA = aresta/2;

  this->vertices.push_back(Vertice(0, Ponto(x - metA, y, z-metA)));
  this->vertices.push_back(Vertice(1, Ponto(x - metA, y, z + metA)));
  this->vertices.push_back(Vertice(2, Ponto(x + metA, y, z + metA)));
  this->vertices.push_back(Vertice(3, Ponto(x + metA, y, z-metA)));
  this->vertices.push_back(Vertice(4, Ponto(x - metA, y + aresta, z-metA)));
  this->vertices.push_back(Vertice(5, Ponto(x - metA, y + aresta, z + metA)));
  this->vertices.push_back(Vertice(6, Ponto(x + metA, y + aresta, z + metA)));
  this->vertices.push_back(Vertice(7, Ponto(x + metA, y + aresta, z-metA)));

  this->arestas.push_back(Aresta(0, 0, 1));
  this->arestas.push_back(Aresta(1, 1, 2));
  this->arestas.push_back(Aresta(2, 2, 3));
  this->arestas.push_back(Aresta(3, 3, 0));
  this->arestas.push_back(Aresta(4, 4, 5));
  this->arestas.push_back(Aresta(5, 5, 6));
  this->arestas.push_back(Aresta(6, 6, 7));
  this->arestas.push_back(Aresta(7, 7, 4));
  this->arestas.push_back(Aresta(8, 0, 4));
  this->arestas.push_back(Aresta(9, 1, 5));
  this->arestas.push_back(Aresta(10, 2, 6));
  this->arestas.push_back(Aresta(11, 3, 7));
  this->arestas.push_back(Aresta(12, 2, 7));
  this->arestas.push_back(Aresta(13, 5, 7));
  this->arestas.push_back(Aresta(14, 5, 2));
  this->arestas.push_back(Aresta(15, 1, 4));
  this->arestas.push_back(Aresta(16, 1, 3));
  this->arestas.push_back(Aresta(17, 3, 4));

  this->faces.push_back(Face(0, 6, 10, 12));
  this->faces.push_back(Face(1, 12, 2, 11));
  this->faces.push_back(Face(2, 7, 4, 13));
  this->faces.push_back(Face(3, 13, 5, 6));
  this->faces.push_back(Face(4, 5, 14, 10));
  this->faces.push_back(Face(5, 9, 1, 14));
  this->faces.push_back(Face(6, 4, 15, 9));
  this->faces.push_back(Face(7, 8, 0, 15));
  this->faces.push_back(Face(8, 1, 16, 2));
  this->faces.push_back(Face(9, 3, 16, 10));
  this->faces.push_back(Face(10, 11, 17, 7));
  this->faces.push_back(Face(11, 3, 8, 17));

  for (int i = 0; i < (this->faces).size(); i++)
    this->calcN_e_R1xR2(&(this->faces[i]));
}