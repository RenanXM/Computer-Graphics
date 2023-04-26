#include "janela.h"

Janela::Janela() {}

Janela::Janela(Ponto cj)
{
  this->cj = cj;
}

/*
void Janela::translacao(double tx, double ty, double tz)
{
  this->cj = Ponto(cj.x + tx, cj.y + ty, cj.z + tz);
}

void Janela::rx(double alfa)
{
  this->cj = Ponto(this->cj.x,
                   this->cj.y * cos(alfa) - this->cj.z * sin(alfa),
                   this->cj.y * sin(alfa) + this->cj.z * cos(alfa));
}

void Janela::ry(double alfa)
{
  this->cj = Ponto(this->cj.x * cos(alfa) + this->cj.z * sin(alfa),
                   this->cj.y,
                   -this->cj.x * sin(alfa) + this->cj.z * cos(alfa));
}

void Janela::rz(double alfa)
{
  this->cj = Ponto(this->cj.x * cos(alfa) - this->cj.y * sin(alfa),
                   this->cj.x * sin(alfa) + this->cj.y * cos(alfa),
                   this->cj.z);
}
*/