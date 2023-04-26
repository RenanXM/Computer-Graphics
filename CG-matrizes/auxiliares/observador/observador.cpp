#include "observador.h"

Observador::Observador(){}

Observador::Observador(Ponto P0)
{
  this->P0 = P0;
}

void Observador::transformacao(Matriz m)
{
  this->P0 = prodMP(m, this->P0);
}

void Observador::translacao(double tx, double ty, double tz)
{
  this->transformacao(Mtranslacao(tx, ty, tz));
	//this->P0 = Ponto(P0.x + tx, P0.y + ty, P0.z + tz);
}

void Observador::rx(double alfa)
{
  this->transformacao(Mrx(alfa));
  /*
  this->P0 = Ponto(this->P0.x,
                   this->P0.y * cos(alfa) - this->P0.z * sin(alfa),
                   this->P0.y * sin(alfa) + this->P0.z * cos(alfa));
                   */
}

void Observador::ry(double alfa)
{
  this->transformacao(Mry(alfa));
  /*
  this->P0 = Ponto(this->P0.x * cos(alfa) + this->P0.z * sin(alfa),
                   this->P0.y,
                   -this->P0.x * sin(alfa) + this->P0.z * cos(alfa));
                   */
}

void Observador::rz(double alfa)
{
  this->transformacao(Mrz(alfa));
  /*
  this->P0 = Ponto(this->P0.x * cos(alfa) - this->P0.y * sin(alfa),
                   this->P0.x * sin(alfa) + this->P0.y * cos(alfa),
                   this->P0.z);
                   */
}

void Observador::espxy()
{
  this->transformacao(Mespxy());
}

void Observador::espxz()
{
  this->transformacao(Mespxz());
}

void Observador::espyz()
{
  this->transformacao(Mespyz());
}