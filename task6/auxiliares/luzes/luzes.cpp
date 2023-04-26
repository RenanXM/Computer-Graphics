#include "luzes.h"

// 1) LUZ
Luz::Luz(){}

Luz::Luz(Ponto Pluz, Intensidade Iluz)
{
  this->Pluz = Pluz;
  this->Iluz = Iluz;
}

Intensidade Luz::iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos)
{
  return Intensidade(0, 0, 0);
}



// 2) LUZ AMBIENTE
LuzAmbiente::LuzAmbiente(){}

LuzAmbiente::LuzAmbiente(Intensidade Iluz): Luz(Ponto(0, 0, 0), Iluz) {}

Intensidade LuzAmbiente::iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos)
{
  return arroba(this->Iluz, obj->Ka);
}



// 3) LUZ PONTUAL
LuzPontual::LuzPontual(){}

LuzPontual::LuzPontual(Ponto Pluz, Intensidade Iluz): Luz(Pluz, Iluz){}

bool LuzPontual::luzInterceptaObjeto(Objeto* obj, Ponto Pi, vector<Objeto*> objetos)
{
  Vetor l = multEscV(obj->calcL(Pi, this->Pluz), -1);

  double t = obj->intersecObj(this->Pluz, l, 2);

  // Verificamos se há algum objeto entre a Luz e o ponto Pi
  double aux;
  /*
  for (int i = 0; i < objetos.size(); i++)
  {
    aux = objetos[i]->intersecObj(this->Pluz, l);
    if (aux > 0 && aux < t)
      return false;
  }
  */

  for (Objeto* obj: objetos)
  {
    aux = obj->intersecObj(this->Pluz, l, 2);
    if (aux > 0 && aux < t)
      return false;    
  }

  return true;
}

Intensidade LuzPontual::iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos)
{
  Intensidade Total = Intensidade(0, 0, 0);

  if (luzInterceptaObjeto(obj, Pi, objetos))
  {
    Vetor l = obj->calcL(Pi, this->Pluz);
    Vetor n = obj->calcN(Pi, multEscV(l, -1));
    Vetor r = obj->calcR(n, l);
    Vetor v = obj->calcV(dr);

    double fdif = prodEsc(l, n);
  
    double fesp = 0;
    if (prodEsc(r, v) > 0) fesp = pow(prodEsc(r, v), obj->m);

    Intensidade Dif = Intensidade(0, 0, 0);
    if (fdif > 0)
      Dif = escalarI(arroba(this->Iluz, obj->Kd), fdif);

    Intensidade Esp = Intensidade(0, 0, 0);
    if (fesp > 0)
      Esp = escalarI(arroba(this->Iluz, obj->Ke), fesp);

    Total = somaI(Dif, Esp);
  }

  return Total;
}



// 4) LUZ DIRECIONAL
LuzDirecional::LuzDirecional(){}

LuzDirecional::LuzDirecional(Intensidade Iluz, bool lNegativo, Vetor D)
{
  this->D = divEscV(D, Modulo(D));
  this->Iluz = Iluz;
  this->lNegativo = lNegativo;
  if (this->lNegativo)
  {
    this->lINV = this->D;
    this->Pluz = Ponto (-1.5E+305 * D.x, -1.5E+305 * D.y, -1.5E+305 * D.z);
  }
  else
  {
    this->lINV = multEscV(this->D, -1);
    this->Pluz = Ponto (1.5E+305 * D.x, 1.5E+305 * D.y, 1.5E+305 * D.z);
  }
  this->l = multEscV(this->lINV, -1);
}

bool LuzDirecional::luzInterceptaObjeto(Objeto* obj, Ponto Pi, vector<Objeto*> objetos, Vetor dr)
{
  // lINV é o vetor que representa "Luz -> obj"
  if (prodEsc(this->lINV, obj->calcN(Pi, dr)) >= 0)
  {
    return false;
  }
  double t = obj->intersecObj(this->Pluz, this->lINV, 2);

  double aux;
  // Verificamos se há algum objeto na frente do objeto
  /*
  for (int i = 0; i < objetos.size(); i++)
  {
    aux = objetos[i]->intersecObj(this->Pluz, this->lINV);
    if ((aux > 0) && (aux < t))
      return false;
  }
  */

  for (Objeto* obj: objetos)
  {
    aux = obj->intersecObj(this->Pluz, this->lINV, 2);
    if (aux > 0 && aux < t)
      return false;    
  }

  return true;
}

Intensidade LuzDirecional::iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos)
{
  Intensidade Total = Intensidade(0, 0, 0);

  if (luzInterceptaObjeto(obj, Pi, objetos, dr))
  {
    Vetor n = obj->calcN(Pi, multEscV(this->l, -1));
    Vetor r = obj->calcR(n, this->l);
    Vetor v = obj->calcV(dr);

    double fdif = prodEsc(this->l, n);
  
    double fesp = 0;
    if (prodEsc(r, v) > 0) fesp = pow(prodEsc(r, v), obj->m);

    Intensidade Dif = Intensidade(0, 0, 0);
    if (fdif > 0)
      Dif = escalarI(arroba(this->Iluz, obj->Kd), fdif);

    Intensidade Esp = Intensidade(0, 0, 0);
    if (fesp > 0)
      Esp = escalarI(arroba(this->Iluz, obj->Ke), fesp);

    Total = somaI(Dif, Esp);
  }

  return Total;
}



// 5) LUZ SPOT
LuzSpot::LuzSpot(){}

LuzSpot::LuzSpot(Ponto Pluz, Intensidade Iluz, Vetor ds, double alfa): Luz(Pluz, Iluz)
{
  this->ds = ds;
  this->alfa = alfa;
}

bool LuzSpot::luzInterceptaObjeto(Objeto* obj, Ponto Pi, vector<Objeto*> objetos)
{
  
  Vetor l = obj->calcL(Pi, this->Pluz);
  double lds = prodEsc(l, this->ds);
  if (-lds < cos(this->alfa))
  {
    return false;
  }
  

  Vetor lINV = multEscV(l, -1);

  double t = obj->intersecObj(this->Pluz, lINV, 2);

  // Verificamos se há algum objeto entre a Luz e o ponto Pi
  double aux;
  /*
  for (int i = 0; i < objetos.size(); i++)
  {
    aux = objetos[i]->intersecObj(this->Pluz, lINV);
    if (aux > 0 && aux < t)
      return false;
  }
  */

  for (Objeto* obj: objetos)
  {
    aux = obj->intersecObj(this->Pluz, lINV, 2);
    if (aux > 0 && aux < t)
      return false;    
  }

  return true;
}

Intensidade LuzSpot::iluminar(Objeto* obj, Ponto Pi, Vetor dr, vector<Objeto*> objetos)
{
  Intensidade Total = Intensidade(0, 0, 0);

  if (luzInterceptaObjeto(obj, Pi, objetos))
  {
    Vetor l = obj->calcL(Pi, this->Pluz);
    double lds = prodEsc(l, this->ds);
    /*
    Já verifico o processo abaixo na função luzInterceptaObjeto
    if (-lds < cos(this->alfa))
    {
      return Total;
    }
    */
    Vetor n = obj->calcN(Pi, multEscV(l, -1));
    Vetor r = obj->calcR(n, l);
    Vetor v = obj->calcV(dr);

    Intensidade Is = escalarI(this->Iluz, -lds);

    double fdif = prodEsc(l, n);
  
    double fesp = 0;
    if (prodEsc(r, v) > 0) fesp = pow(prodEsc(r, v), obj->m);

    Intensidade Dif = Intensidade(0, 0, 0);
    if (fdif > 0)
      Dif = escalarI(arroba(Is, obj->Kd), fdif);

    Intensidade Esp = Intensidade(0, 0, 0);
    if (fesp > 0)
      Esp = escalarI(arroba(Is, obj->Ke), fesp);

    Total = somaI(Dif, Esp);
  }

  return Total;
}