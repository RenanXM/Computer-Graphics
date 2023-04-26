#pragma once
#include "../complexos/complexos.h"

class Portico : public Complexo
{
public:
  Objeto* ColunaEsquerda;
  Objeto* ColunaDireita;
  Objeto* VigaDireita;
  Objeto* VigaEsquerda;
  Portico();

  Portico(Intensidade iColEsq, double mColEsq, Intensidade iColDir, double mColDir, Intensidade iVigaDir, double mVigaDir, Intensidade iVigaEsq, double mVigaEsq);

  Portico(string TextColEsq, double mColEsq, string TextColDir, double mColDir, string TextVigaDir, double mVigaDir, string TextVigaEsq, double mVigaEsq);

  Portico(string Text, double m);
  Portico(Intensidade i, double m);

  void inicializar();
};