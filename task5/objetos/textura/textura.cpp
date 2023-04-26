#include "textura.h"

Textura::Textura()
{
}

Textura::Textura(Objeto* obj, string path)
{
  this->obj = obj;
  this->image = new Image(path);
  this->larguraImage = this->image->getImageWidth();
  this->alturaImage = this->image->getImageHeight();
}

double Textura::intersecObj(Ponto P0, Vetor dr)
{
  return this->obj->intersecObj(P0, dr);
}

Vetor Textura::calcN(Ponto Pi, Vetor dr)
{
  return this->obj->calcN(Pi, dr);  
}

void Textura::intersecTextura(Ponto Pi)
{
  int Px = abs((int) Pi.x);
  int Pz = abs((int) Pi.z);
  int x, y;
  
  x = Px % (this->larguraImage);
  y = Pz % (this->alturaImage);

  Pixel P = this->image->getPixel(x, y);

  Intensidade CorPixel = Intensidade((double)P.r / 255, (double) P.g /255, (double) P.b/255);
  
  this->Ke = CorPixel;
  this->Kd = CorPixel;
  this->Ka = CorPixel;
  this->m = 1;
}