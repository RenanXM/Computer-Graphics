#pragma once
#include "../portico/portico.h"

class Galpao : public Complexo
{
public:
  Objeto* PorticoFrontal;
  Objeto* PorticoTraseiro;
  Objeto* TelhadoEsq;
  Objeto* TelhadoDir;
  Objeto* ParedeEsq;
  Objeto* ParedeDir;
  Objeto* ParedeFundo;
  Objeto* Chao;

  Galpao();
  Galpao(string tFrontal, string tTraseiro, string tTelEsq, string tTelDir, string tParEsq, string tParDir, string tParFundo, string tChao, double m);
  void inicializar();
};