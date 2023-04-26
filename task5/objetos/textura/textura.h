#pragma once
#include "../plano/plano.h"
#include "../../texturaImagem/texturapixel.h"

class Textura: public Objeto
{
public:
  Objeto* obj;
  Image* image;
  int larguraImage;
  int alturaImage;
  Textura();
  Textura(Objeto* obj, string path);

  double intersecObj(Ponto P0, Vetor dr);
  Vetor calcN(Ponto Pi, Vetor dr);
  void intersecTextura(Ponto Pi);
};