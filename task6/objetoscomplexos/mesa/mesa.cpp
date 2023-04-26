#include "mesa.h"
Mesa::Mesa(){}

Mesa::Mesa(Intensidade KeTampo, Intensidade KdTampo, Intensidade KaTampo,   double mTampo,
           Intensidade KeSup1, Intensidade KdSup1, Intensidade KaSup1, double mSup1,
           Intensidade KeSup2, Intensidade KdSup2, Intensidade KaSup2, double mSup2)
{
  Cubo* tampo = new Cubo(KeTampo, KdTampo, KaTampo, mTampo);
  Cubo* suporte1 = new Cubo(KeSup1, KdSup1, KaSup1, mSup1);
  Cubo* suporte2 = new Cubo(KeSup2, KdSup2, KaSup2, mSup2);

  this->Objetos.push_back(tampo);
  this->Objetos.push_back(suporte1);
  this->Objetos.push_back(suporte2);

  this->tampo = tampo;
  this->suporte1 = suporte1;
  this->suporte2 = suporte2;

  this->inicializar();
}

Mesa::Mesa(string texturaTampo, string texturaSup1, string texturaSup2, double mTampo, double mSup1, double mSup2)
{
  Intensidade nula = Intensidade(0, 0, 0);
  Cubo *tampo = new Cubo(nula, nula, nula, mTampo);
  Textura* texturatampo = new Textura(tampo, texturaTampo);

  Cubo *suporte1 = new Cubo(nula, nula, nula, mSup1);
  Textura* texturasuporte1 = new Textura(suporte1, texturaSup1);

  Cubo *suporte2 = new Cubo(nula, nula, nula, mSup2);
  Textura* texturasuporte2 = new Textura(suporte2, texturaSup2);

  this->Objetos.push_back(texturatampo);
  this->Objetos.push_back(texturasuporte1);
  this->Objetos.push_back(texturasuporte2);

  this->tampo = texturatampo;
  this->suporte1 = texturasuporte1;
  this->suporte2 = texturasuporte2;

  this->inicializar();
}

void Mesa::inicializar()
{
  // Aplicar transformações

  //this->espXZ();

  this->tampo->escala(250, 5, 150);
  this->suporte1->escala(5, 95, 150);
  this->suporte2->escala(5, 95, 150);

  this->tampo->translacao(-125, -5, -300);
  this->suporte1->translacao(120, 0, -300);
  this->suporte2->translacao(-125, 0, -300);

  //this->espXZ();
}