#include "arvore.h"

Arvore::Arvore()
{}

Arvore::Arvore(Intensidade KeEsfera, Intensidade KdEsfera, Intensidade KaEsfera, double mEsfera,
         Intensidade KeSuporte, Intensidade KdSuporte, Intensidade KaSuporte, double mSuporte,
         Intensidade KeCone, Intensidade KdCone, Intensidade KaCone, double mCone,
         Intensidade KeTronco, Intensidade KdTronco, Intensidade KaTronco, double mTronco)
{
  Ponto c = Ponto(0, 0, 0);

  this->esfera = new Esfera(1, c, KeEsfera, KdEsfera, KaEsfera, mEsfera);
  this->cone = new Cone(1, c, 2.5, true, Vetor(0, 1, 0), KeCone, KdCone, KaCone, mCone);
  this->tronco = new Cilindro(3, 20, c, Vetor(0, 1, 0), false, false, KeTronco, KdTronco, KaTronco, mTronco);
  this->suporte = new Cubo(KeSuporte, KdSuporte, KaSuporte, mSuporte);

  this->Objetos.push_back(esfera);
  this->Objetos.push_back(cone);
  this->Objetos.push_back(tronco);
  this->Objetos.push_back(suporte);

  this->inicializar();
}

Arvore::Arvore(string texturaEsfera, string texturaSuporte, string texturaCone, string texturaTronco, double mEsfera, double mSuporte, double mCone, double mTronco)
{
  Intensidade nula = Intensidade(0, 0, 0);
  Ponto c = Ponto(0, 0, 0);

  Esfera* esfera = new Esfera(1, c, nula, nula, nula, mEsfera);
  Cone* cone = new Cone(1, c, 2.5, true, Vetor(0, 1, 0), nula, nula, nula, mCone);
  Cilindro* tronco = new Cilindro(3, 20, c, Vetor(0, 1, 0), false, false, nula, nula, nula, mTronco);
  Cubo* suporte = new Cubo(nula, nula, nula, mSuporte);

  Textura* texturaesfera = new Textura(esfera, texturaEsfera);
  Textura* texturacone = new Textura(cone, texturaCone);
  Textura* texturatronco = new Textura(tronco, texturaTronco);
  Textura* texturasuporte = new Textura(suporte, texturaSuporte);

  this->esfera = texturaesfera;
  this->cone = texturacone;
  this->tronco = texturatronco;
  this->suporte = texturasuporte;

  this->Objetos.push_back(texturaesfera);
  this->Objetos.push_back(texturacone);
  this->Objetos.push_back(texturatronco);
  this->Objetos.push_back(texturasuporte);

  this->inicializar();
}

void Arvore::inicializar()
{
  this->esfera->escala(4.5);
  this->cone->escala(60);
  this->tronco->escala(2);
  this->suporte->escala(40, 9, 40);
  
  this->esfera->translacao(0, 125, -200);
  //this->esfera->translacao(0, 160, -200);

  this->cone->translacao(0, -30, -200);

  this->tronco->translacao(0, -70, -200);
  //this->tronco->translacao(0, -150, -200);

  this->suporte->translacao(-20, -79, -220);
  //this->suporte->translacao(-20, -180, -220);
}