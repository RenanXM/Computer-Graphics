#pragma once
#include "../../objeto/objeto.h"
#include <vector>
using std::vector;

class Luz
{
public:
  Ponto Pluz;
  Intensidade Iluz;
  Luz();
  Luz(Ponto Pluz, Intensidade Iluz);
  virtual Intensidade iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> Objetos);

};

class LuzAmbiente : public Luz
{
public:
  LuzAmbiente();
  LuzAmbiente(Intensidade Iluz);
  Intensidade iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos);
};

class LuzPontual : public Luz
{
public:
  LuzPontual();
  LuzPontual(Ponto Pluz, Intensidade Iluz);
  bool luzInterceptaObjeto(Objeto* obj, Ponto Pi, vector<Objeto*> objetos);
  Intensidade iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos);
};

class LuzDirecional : public Luz
{
public:
  bool lNegativo;
  Vetor D, lINV, l;
  LuzDirecional();
  LuzDirecional(Intensidade Iluz, bool lNegativo, Vetor D);
  bool luzInterceptaObjeto(Objeto* obj, Ponto Pi, vector<Objeto*> objetos, Vetor dr);
  Intensidade iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos);
};

class LuzSpot : public Luz
{
public:
  Vetor ds;
  double alfa;
  LuzSpot();
  LuzSpot(Ponto Pluz, Intensidade Iluz, Vetor ds, double alfa);
  bool luzInterceptaObjeto(Objeto* obj, Ponto Pi, vector<Objeto*> objetos);
  Intensidade iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos);
};