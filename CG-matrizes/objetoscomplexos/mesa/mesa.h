#pragma once
#include "../complexos/complexos.h"

class Mesa : public Complexo
{
public:

  Objeto* tampo;
  Objeto* suporte1;
  Objeto* suporte2;
  Mesa();

  Mesa(Intensidade KeTampo, Intensidade KdTampo, Intensidade KaTampo, double mTampo,
       Intensidade KeSup1, Intensidade KdSup1, Intensidade KaSup1, double mSup1,
       Intensidade KeSup2, Intensidade KdSup2, Intensidade KaSup2, double mSup2);

  Mesa(string texturaTampo, string texturaSup1, string texturaSup2, double mTampo, double mSup1, double mSup2);
  void inicializar();
};