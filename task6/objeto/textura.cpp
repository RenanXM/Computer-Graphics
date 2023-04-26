#include "textura.h"

Textura::Textura()
{
}

Textura::Textura(Objeto *obj, string path)
{
  this->obj = obj;
  this->image = new Image(path);
  this->larguraImage = this->image->getImageWidth();
  this->alturaImage = this->image->getImageHeight();
}

double Textura::intersecObj(Ponto P0, Vetor dr, int i)
{
  return this->obj->intersecObj(P0, dr, i);
}

Vetor Textura::calcN(Ponto Pi, Vetor dr)
{
  return this->obj->calcN(Pi, dr);
}

void Textura::intersecTextura(Ponto Pi)
{
  int Px = abs((int)Pi.x);
  int Pz = abs((int)Pi.z);
  int x, y;

  x = Px % (this->larguraImage);
  y = Pz % (this->alturaImage);

  Pixel P = this->image->getPixel(x, y);

  Intensidade CorPixel = Intensidade((double)P.r / 255, (double)P.g / 255, (double)P.b / 255);

  this->Ke = CorPixel;
  this->Kd = CorPixel;
  this->Ka = CorPixel;
  this->m = this->obj->m;
}

void Textura::translacao(double tx, double ty, double tz)
{
  this->obj->translacao(tx, ty, tz);
}

void Textura::escala(double ex, double ey, double ez){
  this->obj->escala(ex, ey, ez);
}

void Textura::escala(double e)
{
  this->obj->escala(e);
}

void Textura::rx(double alfa)
{
  this->obj->rx(alfa);
}

void Textura::ry(double alfa)
{
  this->obj->ry(alfa);
}

void Textura::rz(double alfa)
{
  this->obj->rz(alfa);
}

void Textura::espXY()
{
  this->obj->espXY();
}

void Textura::espXZ()
{
  this->obj->espXZ();
}

void Textura::espYZ()
{
  this->obj->espYZ();
}

void Textura::cisalhamentoYX(double alfa)
{
  this->obj->cisalhamentoYX(alfa);
}

void Textura::cisalhamentoXY(double alfa)
{
  this->obj->cisalhamentoXY(alfa);
}

void Textura::cisalhamentoXZ(double alfa)
{
  this->obj->cisalhamentoXZ(alfa);
}

void Textura::cisalhamentoZX(double alfa)
{
  this->obj->cisalhamentoZX(alfa);
}

void Textura::cisalhamentoYZ(double alfa)
{
  this->obj->cisalhamentoYZ(alfa);
}

void Textura::cisalhamentoZY(double alfa)
{
  this->obj->cisalhamentoZY(alfa);
}