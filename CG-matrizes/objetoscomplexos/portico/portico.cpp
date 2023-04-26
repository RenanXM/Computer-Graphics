#include "portico.h"

Portico::Portico()
{
  /*
  Intensidade r = Intensidade(1, 0, 0);
  Intensidade g = Intensidade(0, 1, 0);
  Intensidade b = Intensidade(0, 0, 1);
  Intensidade c = Intensidade(0.3, 0.3, 0.3);

  this->ColunaDireita = new Cubo(r, r, r, 1);
  this->ColunaEsquerda = new Cubo(g, g, g, 1);
  this->VigaDireita = new Cubo(b, b, b, 1);
  this->VigaEsquerda = new Cubo(c, c, c, 1);

  this->Objetos.push_back(ColunaDireita);
  this->Objetos.push_back(ColunaEsquerda);
  this->Objetos.push_back(VigaDireita);
  this->Objetos.push_back(VigaEsquerda);

  this->inicializar();
  */
}

Portico::Portico(Intensidade iColEsq, double mColEsq, Intensidade iColDir, double mColDir, Intensidade iVigaDir, double mVigaDir, Intensidade iVigaEsq, double mVigaEsq)
{
  this->ColunaDireita = new Cubo(iColDir, iColDir, iColDir, mColDir);
  this->ColunaEsquerda = new Cubo(iColEsq, iColEsq, iColEsq, mColEsq);
  this->VigaDireita = new Cubo(iVigaDir, iVigaDir, iVigaDir, mVigaDir);
  this->VigaEsquerda = new Cubo(iVigaEsq, iVigaEsq, iVigaEsq, mVigaEsq);

  this->Objetos.push_back(ColunaDireita);
  this->Objetos.push_back(ColunaEsquerda);
  this->Objetos.push_back(VigaDireita);
  this->Objetos.push_back(VigaEsquerda);

  this->inicializar();
}

Portico::Portico(string TextColEsq, double mColEsq, string TextColDir, double mColDir, string TextVigaDir, double mVigaDir, string TextVigaEsq, double mVigaEsq)
{
  Intensidade nada = Intensidade(0, 0, 0);

  Cubo* colunaDireita = new Cubo(nada, nada, nada, mColDir);
  Cubo* colunaEsquerda = new Cubo(nada, nada, nada, mColEsq);
  Cubo* vigaDireita = new Cubo(nada, nada, nada, mVigaDir);
  Cubo* vigaEsquerda = new Cubo(nada, nada, nada, mVigaEsq);

  this->ColunaDireita = new Textura(colunaDireita, TextColDir);
  this->ColunaEsquerda = new Textura(colunaEsquerda, TextColEsq);
  this->VigaDireita = new Textura(vigaDireita, TextVigaDir);
  this->VigaEsquerda = new Textura(vigaEsquerda, TextVigaEsq);

  this->Objetos.push_back(ColunaDireita);
  this->Objetos.push_back(ColunaEsquerda);
  this->Objetos.push_back(VigaDireita);
  this->Objetos.push_back(VigaEsquerda);

  this->inicializar();
}

Portico::Portico(string T, double m) : Portico(T, m, T, m, T, m, T, m)
{
}

Portico::Portico(Intensidade i, double m) : Portico(i, m, i, m, i, m, i, m)
{
}

void Portico::inicializar()
{
  this->ColunaEsquerda->escala(50, 500, 30);
  this->ColunaDireita->escala(50, 500, 30);
  this->VigaEsquerda->escala(300, 50, 30);
  this->VigaDireita->escala(300, 50, 30);

  this->VigaEsquerda->cisalhamentoXY(atan(0.75));
  this->VigaDireita->cisalhamentoXY(atan(0.75));

  this->ColunaEsquerda->translacao(-325, -300, -400);
  this->ColunaDireita->translacao(325, -300, -400);
  this->VigaEsquerda->translacao(-325, 150, -400);
  this->VigaDireita->translacao(-325, 150, -400);

  this->VigaDireita->espYZ();
  this->VigaEsquerda->espYZ();

  this->VigaEsquerda->espXZ();
  this->VigaEsquerda->translacao(-300, 575, 0);

  this->translacao(-26, 0, 0);
}