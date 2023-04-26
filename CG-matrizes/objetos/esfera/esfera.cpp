#include "esfera.h"

Esfera::Esfera() {}

Esfera::Esfera(double r, Ponto c, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m) : Objeto(Ke, Kd, Ka, m)
{
  this->r = r;
  this->c = c;
}

Vetor Esfera::calcN(Ponto Pi, Vetor drLuz)
{
  // Vetor n = multEscV(subP(Pi, this->c), 1 / this->r);
  // return multEscV(n, 1/Modulo(n));
  return divEscV(subP(Pi, this->c), this->r);
}

// Verifica se o raio, em teoria, bate na Esfera
double Esfera::intersecObj(Ponto P0, Vetor dr, int i)
{
  Vetor w = subP(P0, this->c);
  double a = prodEsc(dr, dr);
  double b = 2 * prodEsc(w, dr);
  double c = prodEsc(w, w) - (this->r * this->r);

  double delta = (b * b) - (4 * a * c);
  if (delta < 0)
    return -1;

  double t1 = (-b - sqrt(delta)) / (2 * a);
  double t2 = (-b + sqrt(delta)) / (2 * a);
  if (t1 > 0)
    return t1;
  if (t2 > 0)
    return t2;
  return -1;
}

void Esfera::transformacao(Matriz m)
{
  this->c = prodMP(m, this->c);
}

void Esfera::translacao(double tx, double ty, double tz)
{
  Matriz m = Mtranslacao(tx, ty, tz);
  this->transformacao(m);
  //this->c = Ponto(this->c.x + tx, this->c.y + ty, this->c.z + tz);
}


void Esfera::escala(double e)
{
  this->r = this->r * e;  
}

void Esfera::rx(double alfa)
{
  Matriz m = Mrx(alfa);
  this->transformacao(m);
  /*
  this->c = Ponto(this->c.x,
                   this->c.y * cos(alfa) - this->c.z * sin(alfa),
                   this->c.y * sin(alfa) + this->c.z * cos(alfa));
                   */
}

void Esfera::ry(double alfa)
{
  Matriz m = Mry(alfa);
  this->transformacao(m);
  /*
  this->c = Ponto(this->c.x * cos(alfa) + this->c.z * sin(alfa),
                   this->c.y,
                   -this->c.x * sin(alfa) + this->c.z * cos(alfa));
                   */
}
void Esfera::rz(double alfa)
{
  Matriz m = Mrz(alfa);
  this->transformacao(m);
  /*
  this->c = Ponto(this->c.x * cos(alfa) - this->c.y * sin(alfa),
                   this->c.x * sin(alfa) + this->c.y * cos(alfa), this->c.z);
                   */
}
void Esfera::espXY()
{
  Matriz m = Mespxy();
  this->transformacao(m);
  /*
  this->c = Ponto(this->c.x,
                   this->c.y, 
                  -this->c.z);
                  */
}
void Esfera::espXZ()
{
  Matriz m = Mespxz();
  this->transformacao(m);
  /*
  this->c = Ponto(this->c.x,
                  -this->c.y, 
                  this->c.z);
                  */
}
void Esfera::espYZ()
{
  Matriz m = Mespxy();
  this->transformacao(m);
  /*
  this->c = Ponto(-this->c.x,
                  this->c.y, 
                  this->c.z);
                  */
}