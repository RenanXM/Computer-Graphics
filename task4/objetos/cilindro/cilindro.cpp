#include "cilindro.h"

Cilindro::Cilindro() {}

Cilindro::Cilindro(double Rc, double H, Ponto Cb, Vetor dc, bool inf, bool sup, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m)
{
  this->Rc = Rc;
  this->H = H;
  this->Cb = Cb;
  this->dc = dc;
  this->tampaInf = inf;
  this->tampaSup = sup;
  this->Ke = Ke;
  this->Kd = Kd;
  this->Ka = Ka;
  this->m = m;
  this->Ct = addPV(Cb, multEscV(dc, H));
}

// 1) Cálculo das normais
Vetor Cilindro::normalTampaInf()
{
  return multEscV(this->dc, -1);
}

Vetor Cilindro::normalTampaSup()
{
  return this->dc;
}

Vetor Cilindro::normalSup(Ponto Pi, Vetor dr)
{
  Matriz M = subM(identidade(), prodV(this->dc, this->dc));
  Vetor M_PiCb = prodMV(M, subP(Pi, this->Cb));
  Vetor n = divEscV(M_PiCb, Modulo(M_PiCb));

  if (prodEsc(n, dr) > 0)
    return multEscV(n, -1);

  return n;
}

Vetor Cilindro::calcN(Ponto Pi, Vetor dr)
{
  if (this->escolha == 0)
    return this->normalSup(Pi, dr);

  if (this->escolha == 1)
    return this->normalTampaInf();

  return this->normalTampaSup();
}

// 2) Cálculo das interseções
double Cilindro::intersecSup(Ponto P0, Vetor dr)
{
  Vetor w = subP(P0, this->Cb);
  Matriz M = subM(identidade(), prodV(this->dc, this->dc));

  Vetor wM = prodVM(w, M);

  double a = prodEsc(prodVM(dr, M), dr);
  double b = 2 * prodEsc(wM, dr);
  double c = prodEsc(wM, w) - (this->Rc * this->Rc);

  double delta = (b * b) - (4 * a * c);
  
  if (delta < 0 || a == 0)
    return -1;

  double t1 = (-b - sqrt(delta)) / (2 * a);
  double t2 = (-b + sqrt(delta)) / (2 * a);
  Ponto Pi;
  double aux;

  if (t1 > 0)
  {
    Pi = addPV(P0, multEscV(dr, t1));
    aux = prodEsc(subP(Pi, this->Cb), this->dc);
    if ((aux >= 0) && (aux <= this->H))
      return t1;
  }

  if (t2 > 0)
  {
    Pi = addPV(P0, multEscV(dr, t2));
    aux = prodEsc(subP(Pi, this->Cb), this->dc);
    if ((aux >= 0) && (aux <= this->H))
      return t2;
  }

  return -1;
}

double Cilindro::intersecTampa(Vetor n, Ponto P0, Vetor dr)
{
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

double Cilindro::intersecTampaInf(Ponto P0, Vetor dr)
{
  return this->intersecTampa(this->normalTampaInf(), P0, dr);
}

double Cilindro::intersecTampaSup(Ponto P0, Vetor dr)
{
  return this->intersecTampa(this->normalTampaSup(), P0, dr);
}

// 3) Interseção objeto
double Cilindro::escolhaObj(double tTampaInf, double tTampaSup, double tSuperficie)
{
  if (tSuperficie > 0)
  {
    // 2 negativos
    if ((tTampaInf < 0) && (tTampaSup < 0))
    {
      this->escolha = 0;
      return tSuperficie;
    }

    // Somente tTampaSup > 0
    if (tTampaInf < 0)
    {
      if (tTampaSup < tSuperficie)
      {
        this->escolha = 2;
        return tTampaSup;
      }

      this->escolha = 0;
      return tSuperficie;
    }

    // Somente tTampaInf > 0
    if (tTampaSup < 0)
    {
      if (tTampaInf < tSuperficie)
      {
        this->escolha = 1;
        return tTampaInf;
      }

      this->escolha = 0;
      return tSuperficie;
    }

    // 2 Positivos
    if ((tSuperficie <= tTampaInf) && (tSuperficie <= tTampaSup))
    {
      this->escolha = 0;
      return tSuperficie;
    }

    if ((tTampaInf <= tSuperficie) && (tTampaInf <= tTampaSup))
    {
      this->escolha = 1;
      return tTampaInf;
    }

    this->escolha = 2;
    return tTampaSup;
  }

  // tSup é negativo
  if (tTampaInf > 0 && tTampaSup > 0)
  {
    if (tTampaInf < tTampaSup)
    {
      this->escolha = 1;
      return tTampaInf;
    }

    this->escolha = 2;
    return tTampaSup;
  }

  if (tTampaInf > 0)
  {
    this->escolha = 1;
    return tTampaInf;
  }

  if (tTampaSup > 0)
  {
    this->escolha = 2;
    return tTampaSup;
  }

  return -1;
}

double Cilindro::intersecObj(Ponto P0, Vetor dr)
{
  double tTampaInf, tTampaSup, tSuperficie;
  if (this->tampaInf)
    tTampaInf = this->intersecTampaInf(P0, dr);
  else
    tTampaInf = -1;

  if (this->tampaSup)
    tTampaSup = this->intersecTampaSup(P0, dr);
  else
    tTampaSup = -1;

  tSuperficie = this->intersecSup(P0, dr);

  return this->escolhaObj(tTampaInf, tTampaSup, tSuperficie);
}