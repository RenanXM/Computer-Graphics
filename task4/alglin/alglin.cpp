#include "alglin.h"

Vetor::Vetor() {}
Ponto::Ponto() {}
Matriz::Matriz() {}

Vetor::Vetor(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Ponto::Ponto(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
};

Matriz::Matriz(Vetor v1, Vetor v2, Vetor v3)
{
  this->v1 = v1;
  this->v2 = v2;
  this->v3 = v3;
}

double prodEsc(Vetor v1, Vetor v2)
{
  return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double Modulo(Vetor v)
{
  return sqrt(prodEsc(v, v));
}

Vetor subV(Vetor v1, Vetor v2)
{
  return Vetor(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vetor subP(Ponto P1, Ponto P2)
{
  return Vetor(P1.x - P2.x, P1.y - P2.y, P1.z - P2.z);
}

Vetor addV(Vetor v1, Vetor v2)
{
  return Vetor(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vetor multEscV(Vetor v1, double k)
{
  return Vetor(v1.x * k, v1.y * k, v1.z * k);
}

Vetor divEscV(Vetor v, double k){
  return Vetor(v.x / k, v.y / k, v.z / k);
}

Ponto addPV(Ponto p, Vetor v)
{
  return Ponto(p.x + v.x, p.y + v.y, p.z + v.z);
}

Matriz subM(Matriz A, Matriz B)
{
  return Matriz(subV(A.v1, B.v1), subV(A.v2, B.v2), subV(A.v3, B.v3));
}

Matriz prodV(Vetor vcoluna, Vetor vlinha)
{
  /*
  Vetor v1 = Vetor(vcoluna.x * vlinha.x, vcoluna.y * vlinha.x, vcoluna.z * vlinha.x);
  Vetor v2 = Vetor(vcoluna.x * vlinha.y, vcoluna.y * vlinha.y, vcoluna.z * vlinha.y);
  Vetor v3 = Vetor(vcoluna.x * vlinha.z, vcoluna.y * vlinha.z, vcoluna.z * vlinha.z);

     vcoluna     vlinha         v1    v2    v3
      x1        x2 y2 z3      x1*x2 x1*y2 x1*z2
      y1                   =  y1*x2 y1*y2 y1*z2
      z1                      z1*x1 z1*y2 z1*z2

  */
  return Matriz(Vetor(vcoluna.x * vlinha.x, vcoluna.y * vlinha.x, vcoluna.z * vlinha.x), 
                Vetor(vcoluna.x * vlinha.y, vcoluna.y * vlinha.y, vcoluna.z * vlinha.y),
                Vetor(vcoluna.x * vlinha.z, vcoluna.y * vlinha.z, vcoluna.z * vlinha.z));
}


Vetor prodMV(Matriz m, Vetor vcoluna)
{
  /*
        v1 v2 v3       vcoluna                v
        x1 x2 x3         x4         x1*x4 + x2*y4 + x3*z4
        y1 y2 y3         y4     =   y1*x4 + y2*y4 + y3*z4
        z1 z3 z3         z4         z1*x4 + z2*y4 + z3*z4
  

  double x = m.v1.x * vcoluna.x + m.v2.x * vcoluna.y + m.v3.x * vcoluna.z;
  double y = m.v1.y * vcoluna.x + m.v2.y * vcoluna.y + m.v3.y * vcoluna.z;
  double z = m.v1.z * vcoluna.x + m.v2.z * vcoluna.y + m.v3.z * vcoluna.z;
  */

  return Vetor(m.v1.x * vcoluna.x + m.v2.x * vcoluna.y + m.v3.x * vcoluna.z, 
               m.v1.y * vcoluna.x + m.v2.y * vcoluna.y + m.v3.y * vcoluna.z, 
               m.v1.z * vcoluna.x + m.v2.z * vcoluna.y + m.v3.z * vcoluna.z);
}


Vetor prodVM(Vetor vlinha, Matriz m)
{
  /*
     vlinha      v1 v2 v3                       v
    x4 y4 z4     x1 x2 x3         x4*x1 + y4*y1 + z4*z1
                 y1 y2 y3      =   
                 z1 z2 z3         
  
  double x = vlinha.x * m.v1.x + vlinha.y * m.v1.y + vlinha.z * m.v1.z;
  double y = vlinha.x * m.v2.x + vlinha.y * m.v2.y + vlinha.z * m.v2.z;
  double z = vlinha.x * m.v3.x + vlinha.y * m.v3.y + vlinha.z * m.v3.z;
  */
  return Vetor(vlinha.x * m.v1.x + vlinha.y * m.v1.y + vlinha.z * m.v1.z, 
               vlinha.x * m.v2.x + vlinha.y * m.v2.y + vlinha.z * m.v2.z, 
               vlinha.x * m.v3.x + vlinha.y * m.v3.y + vlinha.z * m.v3.z);
}


Matriz identidade()
{
  return Matriz(Vetor(1, 0, 0), Vetor(0, 1, 0), Vetor(0, 0, 1));
}

Vetor prodVetorial(Vetor v, Vetor u)
{
  /*
  double x = v.y*u.z - v.z * u.y;
  double y = v.z*u.x - v.x * u.z;
  double z = v.x*u.y - v.y * u.x;
  */
  return Vetor(v.y*u.z - v.z * u.y, 
               v.z*u.x - v.x * u.z,
               v.x*u.y - v.y * u.x);
}