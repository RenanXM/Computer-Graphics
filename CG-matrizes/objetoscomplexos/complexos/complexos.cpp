#include "complexos.h"

Complexo::Complexo() {}

double Complexo::intersecObj(Ponto P0, Vetor dr, int i)
{
  double min = -1;
  double t;

  for(Objeto* obj : this->Objetos)
  {
    t = obj->intersecObj(P0, dr, i);
    if ( (t > 0) && ( (min < 0) || (t < min) ) )
    {
      min = t;
      if (i == 0)
      {
        this->escolhido = obj;
        /*
        this->Ke = this->escolhido->Ke;
        this->Kd = this->escolhido->Kd;
        this->Ka = this->escolhido->Ka;
        */
      } 
    }
  }

  return min;
}

Vetor Complexo::calcN(Ponto Pi, Vetor dr)
{
  return this->escolhido->calcN(Pi, dr);
}

void Complexo::intersecTextura(Ponto Pi)
{
  this->escolhido->intersecTextura(Pi);
  this->Ke = this->escolhido->Ke;
  this->Kd = this->escolhido->Kd;
  this->Ka = this->escolhido->Ka;
}

// Transformação
void Complexo::translacao(double tx, double ty, double tz)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->translacao(tx, ty, tz);
  }
}

void Complexo::escala(double ex, double ey, double ez)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->escala(ex, ey, ez);
  }
}

void Complexo::escala(double e)
{
  this->escala(e, e, e);
}

void Complexo::rx(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->rx(alfa);
  }
}

void Complexo::ry(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->ry(alfa);
  }
}

void Complexo::rz(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->rz(alfa);
  }
}

void Complexo::espXY()
{
  for(Objeto* obj : this->Objetos)
  {
    obj->espXY();
  }
}

void Complexo::espXZ()
{
  for(Objeto* obj : this->Objetos)
  {
    obj->espXZ();
  }
}

void Complexo::espYZ()
{
  for(Objeto* obj : this->Objetos)
  {
    obj->espYZ();
  }
}

void Complexo::cisalhamentoYX(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->cisalhamentoYX(alfa);
  }
}

void Complexo::cisalhamentoXY(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->cisalhamentoXY(alfa);
  }
}

void Complexo::cisalhamentoXZ(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->cisalhamentoXZ(alfa);
  }
}

void Complexo::cisalhamentoZX(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->cisalhamentoZX(alfa);
  }
}

void Complexo::cisalhamentoYZ(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->cisalhamentoYZ(alfa);
  }
}

void Complexo::cisalhamentoZY(double alfa)
{
  for(Objeto* obj : this->Objetos)
  {
    obj->cisalhamentoZY(alfa);
  }
}
