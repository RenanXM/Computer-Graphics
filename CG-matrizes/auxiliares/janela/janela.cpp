#include "janela.h"

Janela::Janela() {}

Janela::Janela(Ponto cj)
{
  this->cj = cj;
}

void Janela::transformacao(Matriz m)
{
  this->cj = prodMP(m, this->cj);
}

void Janela::translacao(double tx, double ty, double tz)
{
  this->transformacao(Mtranslacao(tx, ty, tz));
}

void Janela::rx(double alfa)
{
  this->transformacao(Mrx(alfa));
}

void Janela::ry(double alfa)
{
  this->transformacao(Mry(alfa));
}

void Janela::rz(double alfa)
{
  this->transformacao(Mrz(alfa));
}

void Janela::espxy()
{
  this->transformacao(Mespxy());
}

void Janela::espxz()
{
  this->transformacao(Mespxz());
}

void Janela::espyz()
{
  this->transformacao(Mespyz());
}