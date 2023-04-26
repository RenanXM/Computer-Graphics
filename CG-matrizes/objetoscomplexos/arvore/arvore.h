#pragma once
#include "../complexos/complexos.h"


class Arvore : public Complexo
{
public:

  Objeto* esfera;
  Objeto* cone;
  Objeto* tronco;
  Objeto* suporte;

  Arvore();

  Arvore(Intensidade KeEsfera, Intensidade KdEsfera, Intensidade KaEsfera, double mEsfera,
         Intensidade KeSuporte, Intensidade KdSuporte, Intensidade KaSuporte, double mSuporte,
         Intensidade KeCone, Intensidade KdCone, Intensidade KaCone, double mCone,
         Intensidade KeTronco, Intensidade KdTronco, Intensidade KaTronco, double mTronco);

  Arvore(string texturaEsfera, string texturaSuporte, string texturaCone, string texturaTronco, double mEsfera, double mSuporte, double mCone, double mTronco);

  void inicializar();
};