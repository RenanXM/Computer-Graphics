#include "cone.h"

Cone::Cone() {}

Cone::Cone(double Rc, Ponto Cb, double H, bool tampa, Vetor dc, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m)
{
  this->Rc = Rc;
  this->Cb = Cb;
  this->tampa = tampa;
  this->Ke = Ke;
  this->Kd = Kd;
  this->Ka = Ka;
  this->m = m;
  this->H = H;
  this->dc = dc;
  this->V = addPV(Cb, multEscV(dc, H));
}

// 1) Cálculo das normais
Vetor Cone::normalTampa()
{
  return multEscV(this->dc, -1);
}

Vetor Cone::normalSup(Ponto Pi, Vetor dr)
{
  Vetor N = prodVetorial(prodVetorial(subP(this->V, Pi), this->dc), subP(this->V, Pi));

  Vetor n = divEscV(N, Modulo(N));

  if (prodEsc(n, dr) > 0)
    return multEscV(n, -1);

  return n;
}

Vetor Cone::calcN(Ponto Pi, Vetor dr)
{
  if (escolha == 0)
    return normalSup(Pi, dr);
    
  return this->normalTampa();
}


// 2) Cálculo das interseções
double Cone::intersecTampa(Ponto P0, Vetor dr)
{
  Vetor n = this->normalTampa();

  if (prodEsc(dr, n) == 0)
    return -1;

  Vetor w = subP(P0, this->Cb);
  double t = -(prodEsc(w, n) / prodEsc(dr, n));
  if (t > 0)
  {
    Ponto Pi = addPV(P0, multEscV(dr, t));
    if (Modulo(subP(Pi, this->Cb)) <= this->Rc)
      return t;
  }
  return -1;
}

double Cone::intersecSup(Ponto P0, Vetor dr)
{
  Vetor v = subP(this->V, P0);
  double cos2 = (this->H * this->H) / (this->Rc * this->Rc + this->H * this->H);
  double dn = prodEsc(dr, this->dc);

  double a = dn * dn - prodEsc(dr, dr) * cos2;
  double b = 2 * (prodEsc(v, dr) * cos2 - prodEsc(v, this->dc) * dn);
  double c = prodEsc(v, this->dc) * prodEsc(v, this->dc) - prodEsc(v, v) * cos2;

  double delta = (b * b) - (4 * a * c);
  if ((delta < 0) || (a == 0))
    return -1;

  double t1 = (-b - sqrt(delta)) / (2 * a);
  double t2 = (-b + sqrt(delta)) / (2 * a);
  Ponto Pi;
  double aux;

  if (t1 > 0)
  {
    Pi = addPV(P0, multEscV(dr, t1));
    aux = prodEsc(subP(this->V, Pi), this->dc);
    if ((aux >= 0) && (aux <= this->H))
      return t1;
  }

  if (t2 > 0)
  {
    Pi = addPV(P0, multEscV(dr, t2));
    aux = prodEsc(subP(this->V, Pi), this->dc);
    if ((aux >= 0) && (aux <= this->H))
      return t2;
  }

  return -1;
}

// 3) Interseção com objeto
double Cone::escolhaObj(double tTampa, double tSuperficie)
{
  if ((tTampa < 0) || ((tTampa > 0) && (tSuperficie > 0) && (tSuperficie < tTampa)))
  {
    this->escolha = 0;
    return tSuperficie;
  }
  
  this->escolha = 1;
  return tTampa;
}

double Cone::intersecObj(Ponto P0, Vetor dr)
{
  double tTampa;
  if (this->tampa)
    tTampa = this->intersecTampa(P0, dr);
  else
    tTampa = -1;

  double tSuperficie = this->intersecSup(P0, dr);

  return this->escolhaObj(tTampa, tSuperficie);
}
