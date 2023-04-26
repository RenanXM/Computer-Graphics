#include "cubo.h"

Cubo::Cubo(){}

Cubo::Cubo(double aresta, Ponto Centro, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m) : Malha(Ke, Kd, Ka, m)
{
  this->inicializar(aresta, Centro);
}

Cubo::Cubo(Intensidade Kd, Intensidade Ke, Intensidade Ka, double m) : Malha(Ke, Kd, Ka, m)
{
  this->inicializar();
}

void Cubo::inicializar(double aresta, Ponto Centro)
{
  double x = Centro.x;
  double y = Centro.y;
  double z = Centro.z;
  double metA = aresta/2;

  this->vertices.push_back(new Vertice(0, Ponto(x - metA, y, z-metA)));
  this->vertices.push_back(new Vertice(1, Ponto(x - metA, y, z + metA)));
  this->vertices.push_back(new Vertice(2, Ponto(x + metA, y, z + metA)));
  this->vertices.push_back(new Vertice(3, Ponto(x + metA, y, z-metA)));
  this->vertices.push_back(new Vertice(4, Ponto(x - metA, y + aresta, z-metA)));
  this->vertices.push_back(new Vertice(5, Ponto(x - metA, y + aresta, z + metA)));
  this->vertices.push_back(new Vertice(6, Ponto(x + metA, y + aresta, z + metA)));
  this->vertices.push_back(new Vertice(7, Ponto(x + metA, y + aresta, z-metA)));

  this->arestas.push_back(new Aresta(0, 0, 1));
  this->arestas.push_back(new Aresta(1, 1, 2));
  this->arestas.push_back(new Aresta(2, 2, 3));
  this->arestas.push_back(new Aresta(3, 3, 0));
  this->arestas.push_back(new Aresta(4, 4, 5));
  this->arestas.push_back(new Aresta(5, 5, 6));
  this->arestas.push_back(new Aresta(6, 6, 7));
  this->arestas.push_back(new Aresta(7, 7, 4));
  this->arestas.push_back(new Aresta(8, 0, 4));
  this->arestas.push_back(new Aresta(9, 1, 5));
  this->arestas.push_back(new Aresta(10, 2, 6));
  this->arestas.push_back(new Aresta(11, 3, 7));
  this->arestas.push_back(new Aresta(12, 2, 7));
  this->arestas.push_back(new Aresta(13, 5, 7));
  this->arestas.push_back(new Aresta(14, 5, 2));
  this->arestas.push_back(new Aresta(15, 1, 4));
  this->arestas.push_back(new Aresta(16, 1, 3));
  this->arestas.push_back(new Aresta(17, 3, 4));

  this->faces.push_back(new Face(0, 6, 10, 12));
  this->faces.push_back(new Face(1, 12, 2, 11));
  this->faces.push_back(new Face(2, 7, 4, 13));
  this->faces.push_back(new Face(3, 13, 5, 6));
  this->faces.push_back(new Face(4, 5, 14, 10));
  this->faces.push_back(new Face(5, 9, 1, 14));
  this->faces.push_back(new Face(6, 4, 15, 9));
  this->faces.push_back(new Face(7, 8, 0, 15));
  this->faces.push_back(new Face(8, 1, 16, 2));
  this->faces.push_back(new Face(9, 3, 16, 10));
  this->faces.push_back(new Face(10, 11, 17, 7));
  this->faces.push_back(new Face(11, 3, 8, 17));

  this->calcFaces();
}

void Cubo::inicializar()
{
  this->vertices.push_back(new Vertice(0, Ponto(0, 0, 0)));
  this->vertices.push_back(new Vertice(1, Ponto(0, 0, 1)));
  this->vertices.push_back(new Vertice(2, Ponto(1, 0, 1)));
  this->vertices.push_back(new Vertice(3, Ponto(1, 0, 0)));
  this->vertices.push_back(new Vertice(4, Ponto(0, 1, 0)));
  this->vertices.push_back(new Vertice(5, Ponto(0, 1, 1)));
  this->vertices.push_back(new Vertice(6, Ponto(1, 1, 1)));
  this->vertices.push_back(new Vertice(7, Ponto(1, 1, 0)));

  this->arestas.push_back(new Aresta(0, 0, 1));
  this->arestas.push_back(new Aresta(1, 1, 2));
  this->arestas.push_back(new Aresta(2, 2, 3));
  this->arestas.push_back(new Aresta(3, 3, 0));
  this->arestas.push_back(new Aresta(4, 4, 5));
  this->arestas.push_back(new Aresta(5, 5, 6));
  this->arestas.push_back(new Aresta(6, 6, 7));
  this->arestas.push_back(new Aresta(7, 7, 4));
  this->arestas.push_back(new Aresta(8, 0, 4));
  this->arestas.push_back(new Aresta(9, 1, 5));
  this->arestas.push_back(new Aresta(10, 2, 6));
  this->arestas.push_back(new Aresta(11, 3, 7));
  this->arestas.push_back(new Aresta(12, 2, 7));
  this->arestas.push_back(new Aresta(13, 5, 7));
  this->arestas.push_back(new Aresta(14, 5, 2));
  this->arestas.push_back(new Aresta(15, 1, 4));
  this->arestas.push_back(new Aresta(16, 1, 3));
  this->arestas.push_back(new Aresta(17, 3, 4));

  this->faces.push_back(new Face(0, 6, 10, 12));
  this->faces.push_back(new Face(1, 12, 2, 11));
  this->faces.push_back(new Face(2, 7, 4, 13));
  this->faces.push_back(new Face(3, 13, 5, 6));
  this->faces.push_back(new Face(4, 5, 14, 10));
  this->faces.push_back(new Face(5, 9, 1, 14));
  this->faces.push_back(new Face(6, 4, 15, 9));
  this->faces.push_back(new Face(7, 8, 0, 15));
  this->faces.push_back(new Face(8, 1, 16, 2));
  this->faces.push_back(new Face(9, 3, 16, 10));
  this->faces.push_back(new Face(10, 11, 17, 7));
  this->faces.push_back(new Face(11, 3, 8, 17));

  this->calcFaces();
}