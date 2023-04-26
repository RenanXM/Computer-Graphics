#pragma once
#include "alglin.h"
#include "iluminacao.h"

//classe mãe dos objetos
class Objeto
{
public:
  //cada objeto tem suas propriedades luminosas.
  Intensidade* Ke;
  Intensidade* Kd;
  Intensidade* Ka;
  float m; // Shininess

  // Retorna o t do ponto mais próximo do objeto em relação a P0 considerando dr
  virtual float intersecObj(Ponto* P0, Vetor* dr);
  // Retorna um vetor unitário.
  virtual Vetor* calcN(Ponto* Pi);
  // Pra objeto retorna false(anyway)
  virtual bool sombraPropria(Ponto* Pi, LuzPontual* Lp, Vetor* L, float t);
  // CALCULA VETOR L (padrão para todos objetos)
  Vetor* calcL(Ponto* Pi, Ponto* Pf);
  // CALCULA VETOR R (padrão para todos objetos)
  Vetor* calcR(Vetor* n, Vetor* l);
  // CALCULA VETOR V (padrão para todos objetos)
  Vetor* calcV(Vetor* dr);
};


//entendido.
//esfera é filha de objeto.
class Esfera : public Objeto
{
public:
  //raio
  float r;
  //ponto central
  Ponto* c;
  Esfera();
  //construtor de uma esfera
  Esfera(float r, Ponto* c, Intensidade* Ke, Intensidade* Kd, Intensidade* Ka, float m);
  //
  float intersecObj(Ponto* P0, Vetor* dr);
  //Calcular o vetot "N" do objeto esfera.
  Vetor* calcN(Ponto* Pi);
  //??? serve de nada
  bool sombraPropria(Ponto* Pi, LuzPontual* Lp, Vetor* L, float t);
};


class Plano : public Objeto
{
//Como o plano é filho de Objeto, ele também recebe os atributos
//da classe Objeto. Exemplo Ke, Kd, Ka
public:
  //Ponto P pi que certamente está no plano
  Ponto* Ppi;
  //Vetor normal ao plano
  Vetor* npi;
  Plano();
  //Construtor de um plano
  Plano(Ponto* Ppi, Vetor* npi, Intensidade* Ke, Intensidade* Kd, Intensidade* Ka, float m);
  //retornamos o valor necessário para verificar a intersecção
  float intersecObj(Ponto* P0, Vetor* dr);
  //Calculo do vetor Normal ao plano 
  Vetor* calcN(Ponto* Pi);
  //inutil
  bool sombraPropria(Ponto* Pi, LuzPontual* Lp, Vetor* L, float t);
};