#include "cilindro.h"

Cilindro::Cilindro() {}

Cilindro::Cilindro(double Rc, double H, Ponto Cb, Vetor dc, bool inf, bool sup, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m) : Objeto(Ke, Kd, Ka, m)
{
  this->Rc = Rc;
  this->H = H;
  this->Cb = Cb;
  this->dc = dc;
  this->tampaInf = inf;
  this->tampaSup = sup;
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

Vetor Cilindro::normalSup(Ponto Pi, Vetor drLuz)
{
  Matriz M = subM(identidade(), prodV(this->dc, this->dc));
  Vetor M_PiCb = prodMV(M, subP(Pi, this->Cb));
  Vetor n = divEscV(M_PiCb, Modulo(M_PiCb));

  if (prodEsc(n, drLuz) > 0)
    return multEscV(n, -1);

  return n;
}

Vetor Cilindro::calcN(Ponto Pi, Vetor drLuz)
{
  if (this->escolha == 0)
    return this->normalSup(Pi, drLuz);

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

  Ponto base;
  if ((dc.x == n.x) && (dc.y == n.y) && (dc.z == n.z))
    base = this->Ct;
  else
    base = this->Cb;

  Vetor w = subP(P0, base);
  double t = -(prodEsc(w, n) / prodEsc(dr, n));
  if (t > 0)
  {
    Ponto Pi = addPV(P0, multEscV(dr, t));
    if (Modulo(subP(Pi, base)) <= this->Rc)
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
double Cilindro::escolhaObj(double tTampaInf, double tTampaSup, double tSuperficie, int i)
{
  if (tSuperficie > 0)
  {
    // 2 negativos
    if ((tTampaInf < 0) && (tTampaSup < 0))
    {
      if (i == 0) this->escolha = 0;
      return tSuperficie;
    }

    // Somente tTampaSup > 0
    if (tTampaInf < 0)
    {
      if (tTampaSup < tSuperficie)
      {
        if (i == 0) this->escolha = 2;
        return tTampaSup;
      }

      if (i == 0) this->escolha = 0;
      return tSuperficie;
    }

    // Somente tTampaInf > 0
    if (tTampaSup < 0)
    {
      if (tTampaInf < tSuperficie)
      {
        if (i == 0) this->escolha = 1;
        return tTampaInf;
      }

      if (i == 0) this->escolha = 0;
      return tSuperficie;
    }

    // 2 Positivos
    if ((tSuperficie < tTampaInf) && (tSuperficie < tTampaSup))
    {
      if (i == 0) this->escolha = 0;
      return tSuperficie;
    }

    if ((tTampaInf < tSuperficie) && (tTampaInf < tTampaSup))
    {
      if (i == 0) this->escolha = 1;
      return tTampaInf;
    }

    if (i == 0) this->escolha = 2;
    return tTampaSup;
  }

  // tSup é negativo
  if (tTampaInf > 0 && tTampaSup > 0)
  {
    if (tTampaInf < tTampaSup)
    {
      if (i == 0) this->escolha = 1;
      return tTampaInf;
    }

    if (i == 0) this->escolha = 2;
    return tTampaSup;
  }

  if (tTampaInf > 0)
  {
    if (i == 0) this->escolha = 1;
    return tTampaInf;
  }

  if (tTampaSup > 0)
  {
    if (i == 0) this->escolha = 2;
    return tTampaSup;
  }

  return -1;
}

double Cilindro::intersecObj(Ponto P0, Vetor dr, int i)
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

  return this->escolhaObj(tTampaInf, tTampaSup, tSuperficie, i);
}

void Cilindro::transformacaoSemCorrecaoDc(Matriz m)
{
  this->Cb = prodMP(m, this->Cb);
  this->Ct = prodMP(m, this->Ct);
}

void Cilindro::transformacaoECorrecaoDc(Matriz m)
{
  this->Cb = prodMP(m, this->Cb);
  this->Ct = prodMP(m, this->Ct);
  this->dc = prodMV(m, this->dc);
}

void Cilindro::translacao(double tx, double ty, double tz)
{
  Matriz m = Mtranslacao(tx, ty, tz);
  this->transformacaoSemCorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x + tx,
                   this->Cb.y + ty,
                   this->Cb.z + tz);

  this->Ct = Ponto(this->Ct.x + tx,
                   this->Ct.y + ty,
                   this->Ct.z + tz);
                   */                 
}

void Cilindro::escala(double e)
{
  this->Rc = this->Rc * e;
  this->H = this->H * e;
  this->Ct = addPV(Cb, multEscV(dc, H));
}

void Cilindro::rx(double alfa)
{
  Matriz m = Mrx(alfa);
  this->transformacaoECorrecaoDc(m);

  /*
  this->Cb = Ponto(this->Cb.x,
                   this->Cb.y * cos(alfa) - this->Cb.z * sin(alfa),
                   this->Cb.y * sin(alfa) + this->Cb.z * cos(alfa));

  this->Ct = Ponto(this->Ct.x,
                   this->Ct.y * cos(alfa) - this->Ct.z * sin(alfa),
                   this->Ct.y * sin(alfa) + this->Ct.z * cos(alfa));

  this->dc = Vetor(this->dc.x,
                   this->dc.y * cos(alfa) - this->dc.z * sin(alfa),
                   this->dc.y * sin(alfa) + this->dc.z * cos(alfa));
                   */
}

void Cilindro::ry(double alfa)
{
  Matriz m = Mry(alfa);
  this->transformacaoECorrecaoDc(m);

  /*
  this->Cb = Ponto(this->Cb.x * cos(alfa) + this->Cb.z * sin(alfa),
                   this->Cb.y,
                   -this->Cb.x * sin(alfa) + this->Cb.z * cos(alfa));

  this->Ct = Ponto(this->Ct.x * cos(alfa) + this->Ct.z * sin(alfa),
                   this->Ct.y,
                   -this->Ct.x * sin(alfa) + this->Ct.z * cos(alfa));

  this->dc = Vetor(this->dc.x * cos(alfa) + this->dc.z * sin(alfa),
                   this->dc.y,
                   -this->dc.x * sin(alfa) + this->dc.z * cos(alfa));
  */
}

void Cilindro::rz(double alfa)
{
  Matriz m = Mrz(alfa);
  this->transformacaoECorrecaoDc(m);

  /*
  this->Cb = Ponto(this->Cb.x * cos(alfa) - this->Cb.y * sin(alfa),
                   this->Cb.x * sin(alfa) + this->Cb.y * cos(alfa), this->Cb.z);

  this->Ct = Ponto(this->Ct.x * cos(alfa) - this->Ct.y * sin(alfa),
                   this->Ct.x * sin(alfa) + this->Ct.y * cos(alfa), this->Ct.z);

  this->dc = Vetor(this->dc.x * cos(alfa) - this->dc.y * sin(alfa),
                   this->dc.x * sin(alfa) + this->dc.y * cos(alfa), this->dc.z);
                   */
}

void Cilindro::espXY()
{
  Matriz m = Mespxy();
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x,
                   this->Cb.y, 
                  -this->Cb.z);

  this->Ct = Ponto(this->Ct.x,
                   this->Ct.y, 
                  -this->Ct.z);

  this->dc = Vetor(this->dc.x,
                   this->dc.y, 
                  -this->dc.z);
                  */
}

void Cilindro::espXZ()
{
  Matriz m = Mespxz();
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x,
                   -this->Cb.y, 
                   this->Cb.z);

  this->Ct = Ponto(this->Ct.x,
                   -this->Ct.y, 
                   this->Ct.z);

  this->dc = Vetor(this->dc.x,
                   -this->dc.y, 
                   this->dc.z);
                   */
}

void Cilindro::espYZ()
{
  Matriz m = Mespyz();
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(-this->Cb.x,
                   this->Cb.y, 
                   this->Cb.z);

  this->Ct = Ponto(-this->Ct.x,
                   this->Ct.y, 
                   this->Ct.z);

  this->dc = Vetor(-this->dc.x,
                   this->dc.y, 
                   this->dc.z);
                   */
}