#include "cone.h"

Cone::Cone() {}

Cone::Cone(double Rc, Ponto Cb, double H, bool tampa, Vetor dc, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m):Objeto(Ke, Kd, Ka, m)
{
  this->Rc = Rc;
  this->Cb = Cb;
  this->H = H;
  this->tampa = tampa;
  this->dc = dc;
  this->V = addPV(Cb, multEscV(dc, H));
}

// 1) Cálculo das normais
Vetor Cone::normalTampa()
{
  return multEscV(this->dc, -1);
}

Vetor Cone::normalSup(Ponto Pi, Vetor drLuz)
{
  Vetor N = prodVetorial(prodVetorial(subP(this->V, Pi), this->dc), subP(this->V, Pi));

  Vetor n = divEscV(N, -Modulo(N));

  if (prodEsc(n, drLuz) > 0)
    return multEscV(n, -1);

  return n;
}

Vetor Cone::calcN(Ponto Pi, Vetor drLuz)
{
  if (escolha == 0)
  {
    return normalSup(Pi, drLuz);
  }

  return this->normalTampa();
}


// 2) Cálculo das interseções
double Cone::intersecTampa(Ponto P0, Vetor dr)
{
  Vetor dc = this->dc;

  if (prodEsc(dr, dc) == 0)
    return -1;

  Vetor w = subP(P0, this->Cb);
  double t = -(prodEsc(w, dc) / prodEsc(dr, dc));

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
  double cos2 = (this->H * this->H) / ((this->Rc * this->Rc) + (this->H * this->H));
  double dn = prodEsc(dr, this->dc);
  double vdc = prodEsc(v, this->dc);

  double a = (dn * dn) - (prodEsc(dr, dr) * cos2);
  double b = (prodEsc(v, dr) * cos2) - (vdc * dn);
  double c = (vdc * vdc) - (prodEsc(v, v) * cos2);

  double delta = (b * b) - (a * c);
  if ((delta < 0) || (a == 0))
    return -1;

  double t1 = ((-b) - sqrt(delta)) / (a);
  double t2 = ((-b) + sqrt(delta)) / (a);
  
  Ponto Pi;
  double aux;

  if (t2 > 0)
  {
    Pi = addPV(P0, multEscV(dr, t2));
    aux = prodEsc(subP(this->V, Pi), this->dc);
    if ((aux >= 0) && (aux <= this->H))
    {
      return t2;
    }   
  }

  if (t1 > 0)
  {
    Pi = addPV(P0, multEscV(dr, t1));
    aux = prodEsc(subP(this->V, Pi), this->dc);
    if ((aux >= 0) && (aux <= this->H))
    {
      return t1;
    }
  }

  return -1;
}

// 3) Interseção com objeto
double Cone::escolhaObj(double tTampa, double tSuperficie, int i)
{
  if((tTampa < 0) && (tSuperficie < 0))
    return -1;

  else if (tSuperficie < 0)
  {
    if (i == 0) this->escolha = 1;
    return tTampa;
  }

  else if (tTampa < 0)
  {
    if (i == 0) this->escolha = 0;
    return tSuperficie;
  }

  else if (tTampa < tSuperficie)
  {
    if (i == 0) this->escolha = 1;
    return tTampa;
  }

  if (i == 0) this->escolha = 0;
  return tSuperficie;
}

double Cone::intersecObj(Ponto P0, Vetor dr, int i)
{
  double tTampa;
  if (this->tampa)
    tTampa = this->intersecTampa(P0, dr);
  else
    tTampa = -1;

  double tSuperficie = this->intersecSup(P0, dr);
  return this->escolhaObj(tTampa, tSuperficie, i);
}


void Cone::transformacaoSemCorrecaoDc(Matriz m)
{
  this->Cb = prodMP(m, this->Cb);
  this->V = prodMP(m, this->V);
}

void Cone::transformacaoECorrecaoDc(Matriz m)
{
  this->Cb = prodMP(m, this->Cb);
  this->V = prodMP(m, this->V);
  this->dc = prodMV(m, this->dc);
}

void Cone::translacao(double tx, double ty, double tz)
{
  Matriz m = Mtranslacao(tx, ty, tz);
  this->transformacaoSemCorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x + tx,
                   this->Cb.y + ty,
                   this->Cb.z + tz);

  this->V = Ponto(this->V.x + tx,
                   this->V.y + ty,
                   this->V.z + tz); 
  */               
}

void Cone::escala(double e)
{
  this->Rc = this->Rc * e;
  this->H = this->H * e;

  this->V = addPV(Cb, multEscV(dc, H));
}

void Cone::rx(double alfa)
{
  Matriz m = Mrx(alfa);
  this->transformacaoECorrecaoDc(m);

  /*
  this->Cb = Ponto(this->Cb.x,
                   this->Cb.y * cos(alfa) - this->Cb.z * sin(alfa),
                   this->Cb.y * sin(alfa) + this->Cb.z * cos(alfa));

  this->V = Ponto(this->V.x,
                   this->V.y * cos(alfa) - this->V.z * sin(alfa),
                   this->V.y * sin(alfa) + this->V.z * cos(alfa));

  this->dc = Vetor(this->dc.x,
                   this->dc.y * cos(alfa) - this->dc.z * sin(alfa),
                   this->dc.y * sin(alfa) + this->dc.z * cos(alfa));
                   */

}

void Cone::ry(double alfa)
{
  Matriz m = Mry(alfa);
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x * cos(alfa) + this->Cb.z * sin(alfa),
                   this->Cb.y,
                   -this->Cb.x * sin(alfa) + this->Cb.z * cos(alfa));

  this->V = Ponto(this->V.x * cos(alfa) + this->V.z * sin(alfa),
                   this->V.y,
                   -this->V.x * sin(alfa) + this->V.z * cos(alfa));

  this->dc = Vetor(this->dc.x * cos(alfa) + this->dc.z * sin(alfa),
                   this->dc.y,
                   -this->dc.x * sin(alfa) + this->dc.z * cos(alfa));
                   */

}

void Cone::rz(double alfa)
{
  Matriz m = Mrx(alfa);
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x * cos(alfa) - this->Cb.y * sin(alfa),
                   this->Cb.x * sin(alfa) + this->Cb.y * cos(alfa), 
                   this->Cb.z);

  this->V = Ponto(this->V.x * cos(alfa) - this->V.y * sin(alfa),
                  this->V.x * sin(alfa) + this->V.y * cos(alfa), 
                  this->V.z);

  this->dc = Vetor(this->dc.x * cos(alfa) - this->dc.y * sin(alfa),
                   this->dc.x * sin(alfa) + this->dc.y * cos(alfa), 
                   this->dc.z);
                   */
}

void Cone::espXY()
{
  Matriz m = Mespxy();
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x,
                   this->Cb.y, 
                  -this->Cb.z);

  this->V = Ponto(this->V.x,
                   this->V.y, 
                  -this->V.z);

  this->dc = Vetor(this->dc.x,
                   this->dc.y, 
                  -this->dc.z);
                  */
}
void Cone::espXZ()
{
  Matriz m = Mespxz();
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(this->Cb.x,
                   -this->Cb.y, 
                   this->Cb.z);

  this->V = Ponto(this->V.x,
                   -this->V.y, 
                   this->V.z);

  this->dc = Vetor(this->dc.x,
                   -this->dc.y, 
                   this->dc.z);
                   */
}

void Cone::espYZ()
{
  Matriz m = Mespyz();
  this->transformacaoECorrecaoDc(m);
  
  /*
  this->Cb = Ponto(-this->Cb.x,
                   this->Cb.y, 
                   this->Cb.z);

  this->V = Ponto(-this->V.x,
                   this->V.y, 
                   this->V.z);

  this->dc = Vetor(-this->dc.x,
                   this->dc.y, 
                   this->dc.z);
                   */
}