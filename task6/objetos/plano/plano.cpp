#include "plano.h"

Plano::Plano() {}

Plano::Plano(Ponto Ppi, Vetor npi, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m) : Objeto(Ke, Kd, Ka, m)
{
  this->Ppi = Ppi;
  this->npi = npi;
}

// Verifica se o raio, em teoria, bate no Plano
double Plano::intersecObj(Ponto P0, Vetor dr, int i)
{
  Vetor w = subP(P0, this->Ppi);
  return -(prodEsc(w, this->npi) / prodEsc(dr, this->npi));
}

Vetor Plano::calcN(Ponto Pi, Vetor drLuz)
{
  return this->npi;
}

void Plano::transformacaoECorrecaoNormal(Matriz m)
{
  this->Ppi = prodMP(m, this->Ppi);
  this->npi = prodMV(m, this->npi);
}
void Plano::transformacaoSemCorrecaoNormal(Matriz m)
{
  this->Ppi = prodMP(m, this->Ppi);
}

// Transformação
void Plano::translacao(double tx, double ty, double tz)
{
  Matriz m = Mtranslacao(tx, ty, tz);
  this->transformacaoSemCorrecaoNormal(m);

  //this->Ppi = Ponto(Ppi.x + tx, Ppi.y + ty, Ppi.z + tz);
}
void Plano::escala(double e)
{
}

void Plano::rx(double alfa)
{
  Matriz m = Mrx(alfa);
  this->transformacaoECorrecaoNormal(m);

  /*
  this->Ppi = Ponto(this->Ppi.x,
                   this->Ppi.y * cos(alfa) - this->Ppi.z * sin(alfa),
                   this->Ppi.y * sin(alfa) + this->Ppi.z * cos(alfa));

  this->npi = Vetor(this->npi.x,
                   this->npi.y * cos(alfa) - this->npi.z * sin(alfa),
                   this->npi.y * sin(alfa) + this->npi.z * cos(alfa));
  */
}
void Plano::ry(double alfa)
{
  Matriz m = Mry(alfa);
  this->transformacaoECorrecaoNormal(m);

  /*
  this->Ppi = Ponto(this->Ppi.x * cos(alfa) + this->Ppi.z * sin(alfa),
                   this->Ppi.y,
                   -this->Ppi.x * sin(alfa) + this->Ppi.z * cos(alfa));

  this->npi = Vetor(this->npi.x * cos(alfa) + this->npi.z * sin(alfa),
                   this->npi.y,
                   -this->npi.x * sin(alfa) + this->npi.z * cos(alfa));
  */
}

void Plano::rz(double alfa)
{
  Matriz m = Mrz(alfa);
  this->transformacaoECorrecaoNormal(m);

  /*
  this->Ppi = Ponto(this->Ppi.x * cos(alfa) - this->Ppi.y * sin(alfa),
                   this->Ppi.x * sin(alfa) + this->Ppi.y * cos(alfa), this->Ppi.z);

  this->npi = Vetor(this->npi.x * cos(alfa) - this->npi.y * sin(alfa),
                   this->npi.x * sin(alfa) + this->npi.y * cos(alfa), this->npi.z);
  */
}
void Plano::espXY()
{
  Matriz m = Mespxy();
  this->transformacaoECorrecaoNormal(m);

  /*
  this->Ppi = Ponto(this->Ppi.x,
                   this->Ppi.y, 
                  -this->Ppi.z);

  this->npi = Vetor(this->npi.x,
                   this->npi.y, 
                  -this->npi.z);
  */
}

void Plano::espXZ()
{
  Matriz m = Mespxz();
  this->transformacaoECorrecaoNormal(m);

  /*
  this->Ppi = Ponto(this->Ppi.x,
                   -this->Ppi.y, 
                   this->Ppi.z);

  this->npi = Vetor(this->npi.x,
                   -this->npi.y, 
                   this->npi.z);
  */
}
void Plano::espYZ()
{
  Matriz m = Mespyz();
  this->transformacaoECorrecaoNormal(m);

  /*
  this->Ppi = Ponto(-this->Ppi.x,
                    this->Ppi.y, 
                    this->Ppi.z);

  this->npi = Vetor(-this->npi.x,
                    this->npi.y, 
                    this->npi.z);
  */
}