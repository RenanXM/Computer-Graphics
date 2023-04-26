#include "alglin.h"

Vetor::Vetor() {}
Ponto::Ponto() {}
Matriz::Matriz() {}

Vetor::Vetor(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->d = 0;
}

Vetor::Vetor(double x, double y, double z, double d)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->d = d;
}

Ponto::Ponto(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->d = 1;
}

Matriz::Matriz(Vetor v1, Vetor v2, Vetor v3, Vetor v4)
{
  this->v1 = v1;
  this->v2 = v2;
  this->v3 = v3;
  this->v4 = v4;
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
  return Matriz(subV(A.v1, B.v1), subV(A.v2, B.v2), subV(A.v3, B.v3), subV(A.v4, B.v4));
}

Matriz somaM(Matriz A, Matriz B)
{
  return Matriz(addV(A.v1, B.v1), addV(A.v2, B.v2), addV(A.v3, B.v3), addV(A.v4, B.v4));
}

Matriz prodV(Vetor vcoluna, Vetor vlinha)
{
  /*
  Vetor v1 = Vetor(vcoluna.x * vlinha.x, vcoluna.y * vlinha.x, vcoluna.z * vlinha.x);
  Vetor v2 = Vetor(vcoluna.x * vlinha.y, vcoluna.y * vlinha.y, vcoluna.z * vlinha.y);
  Vetor v3 = Vetor(vcoluna.x * vlinha.z, vcoluna.y * vlinha.z, vcoluna.z * vlinha.z);

     vcoluna     vlinha           v1    v2    v3    v4
      x1        x2 y2 z2 d2      x1*x2 x1*y2 x1*z2 x1*d2
      y1                      =  y1*x2 y1*y2 y1*z2 y1*d2
      z1                         z1*x2 z1*y2 z1*z2 z1*d2
      d1                         d1*x2 d1*y2 d1*z2 d1*d2
  */
  return Matriz(Vetor(vcoluna.x * vlinha.x, vcoluna.y * vlinha.x, vcoluna.z * vlinha.x, vcoluna.d * vlinha.x), 
                Vetor(vcoluna.x * vlinha.y, vcoluna.y * vlinha.y, vcoluna.z * vlinha.y, vcoluna.d * vlinha.y),
                Vetor(vcoluna.x * vlinha.z, vcoluna.y * vlinha.z, vcoluna.z * vlinha.z, vcoluna.d * vlinha.z),
                Vetor(vcoluna.x * vlinha.d, vcoluna.y * vlinha.d, vcoluna.z * vlinha.d, vcoluna.d * vlinha.d));
}

double prodLinhaColuna(Vetor vlinha, Vetor vcoluna)
{
  return (vlinha.x * vcoluna.x + vlinha.y * vcoluna.y + vlinha.z * vcoluna.z + vlinha.d * vcoluna.d); 
}

Matriz prodMM(Matriz a, Matriz b)
{
  Vetor V1 = Vetor(prodLinhaColuna(Vetor(a.v1.x, a.v2.x, a.v3.x, a.v4.x), b.v1),
                   prodLinhaColuna(Vetor(a.v1.y, a.v2.y, a.v3.y, a.v4.y), b.v1),
                   prodLinhaColuna(Vetor(a.v1.z, a.v2.z, a.v3.z, a.v4.z), b.v1),
                   prodLinhaColuna(Vetor(a.v1.d, a.v2.d, a.v3.d, a.v4.d), b.v1));

  Vetor V2 = Vetor(prodLinhaColuna(Vetor(a.v1.x, a.v2.x, a.v3.x, a.v4.x), b.v2),
                   prodLinhaColuna(Vetor(a.v1.y, a.v2.y, a.v3.y, a.v4.y), b.v2),
                   prodLinhaColuna(Vetor(a.v1.z, a.v2.z, a.v3.z, a.v4.z), b.v2),
                   prodLinhaColuna(Vetor(a.v1.d, a.v2.d, a.v3.d, a.v4.d), b.v2));

  Vetor V3 = Vetor(prodLinhaColuna(Vetor(a.v1.x, a.v2.x, a.v3.x, a.v4.x), b.v3),
                   prodLinhaColuna(Vetor(a.v1.y, a.v2.y, a.v3.y, a.v4.y), b.v3),
                   prodLinhaColuna(Vetor(a.v1.z, a.v2.z, a.v3.z, a.v4.z), b.v3),
                   prodLinhaColuna(Vetor(a.v1.d, a.v2.d, a.v3.d, a.v4.d), b.v3));

  Vetor V4 = Vetor(prodLinhaColuna(Vetor(a.v1.x, a.v2.x, a.v3.x, a.v4.x), b.v4),
                   prodLinhaColuna(Vetor(a.v1.y, a.v2.y, a.v3.y, a.v4.y), b.v4),
                   prodLinhaColuna(Vetor(a.v1.z, a.v2.z, a.v3.z, a.v4.z), b.v4),
                   prodLinhaColuna(Vetor(a.v1.d, a.v2.d, a.v3.d, a.v4.d), b.v4));

  return Matriz(V1, V2, V3, V4);
}

Vetor prodMV(Matriz m, Vetor vcoluna)
{
  /*
        v1 v2 v3 v4      vcoluna                v
        x1 x2 x3 x4        x5         x1*x5 + x2*y5 + x3*z5 + x4*d5
        y1 y2 y3 y4        y5     =   y1*x5 + y2*y5 + y3*z5 + y4*d5
        z1 z2 z3 z4        z5         z1*x5 + z2*y5 + z3*z5 + z4*d5
        d1 d2 d3 d4        d5         d1*x5 + d2*y5 + d3*z5 + d4*d5

  double x = m.v1.x * vcoluna.x + m.v2.x * vcoluna.y + m.v3.x * vcoluna.z;
  double y = m.v1.y * vcoluna.x + m.v2.y * vcoluna.y + m.v3.y * vcoluna.z;
  double z = m.v1.z * vcoluna.x + m.v2.z * vcoluna.y + m.v3.z * vcoluna.z;
  */

  return Vetor(m.v1.x * vcoluna.x + m.v2.x * vcoluna.y + m.v3.x * vcoluna.z + m.v4.x * vcoluna.d, 
               m.v1.y * vcoluna.x + m.v2.y * vcoluna.y + m.v3.y * vcoluna.z + m.v4.y * vcoluna.d, 
               m.v1.z * vcoluna.x + m.v2.z * vcoluna.y + m.v3.z * vcoluna.z + m.v4.z * vcoluna.d,
               m.v1.d * vcoluna.x + m.v2.d * vcoluna.y + m.v3.d * vcoluna.z + m.v4.d * vcoluna.d);
}

Ponto prodMP(Matriz m, Ponto p)
{
  return Ponto(m.v1.x * p.x + m.v2.x * p.y + m.v3.x * p.z + m.v4.x * p.d, 
               m.v1.y * p.x + m.v2.y * p.y + m.v3.y * p.z + m.v4.y * p.d, 
               m.v1.z * p.x + m.v2.z * p.y + m.v3.z * p.z + m.v4.z * p.d);
}

Vetor prodVM(Vetor vlinha, Matriz m)
{
  /*
     vlinha        v1 v2 v3 v4                 
    x5 y5 z5 d5    x1 x2 x3 x4        
                   y1 y2 y3 y4    
                   z1 z2 z3 z4
                   d1 d2 d3 d3       
  
  double x = vlinha.x * m.v1.x + vlinha.y * m.v1.y + vlinha.z * m.v1.z + vlinha.d * m.v1.d;
  double y = vlinha.x * m.v2.x + vlinha.y * m.v2.y + vlinha.z * m.v2.z + vlinha.d * m.v2.d;
  double z = vlinha.x * m.v3.x + vlinha.y * m.v3.y + vlinha.z * m.v3.z + vlinha.d * m.v3.d;
  double d = 0;
  */
  return Vetor(vlinha.x * m.v1.x + vlinha.y * m.v1.y + vlinha.z * m.v1.z + vlinha.d * m.v1.d, 
               vlinha.x * m.v2.x + vlinha.y * m.v2.y + vlinha.z * m.v2.z + vlinha.d * m.v2.d, 
               vlinha.x * m.v3.x + vlinha.y * m.v3.y + vlinha.z * m.v3.z + vlinha.d * m.v3.d);
}


Matriz identidade()
{
  return Matriz(Vetor(1, 0, 0, 0), Vetor(0, 1, 0, 0), Vetor(0, 0, 1, 0), Vetor(0, 0, 0, 1));
}

Vetor prodVetorial(Vetor v, Vetor u)
{
  /*
  double x = v.y*u.z - v.z * u.y;
  double y = v.z*u.x - v.x * u.z;
  double z = v.x*u.y - v.y * u.x;
  double d = 0;
  */
  return Vetor(v.y*u.z - v.z * u.y, 
               v.z*u.x - v.x * u.z,
               v.x*u.y - v.y * u.x);
}

// Ponto Novo = M * Ponto Antigo
// 1) Translação
/*
        1 0 0 tx
        0 1 0 ty
  T =   0 0 1 tz
        0 0 0 1
*/
Matriz Mtranslacao(double tx, double ty, double tz)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(tx, ty, tz, 1));
}

// 2) Escala
/*
        Ex 0  0  0
        0  Ey 0  0
  E =   0  0  Ez 0
        0  0  0  1
*/
Matriz Mescala(double ex, double ey, double ez)
{
  return Matriz(Vetor(ex, 0, 0, 0),
                Vetor(0, ey, 0, 0),
                Vetor(0, 0, ez, 0),
                Vetor(0, 0, 0, 1));
}

Matriz Mescala(double e)
{
  return Mescala(e, e, e);
}

// 3) Rotação
// 3.1) Rotação em x
/*
         1    0     0    0
         0   cosA -senA  0
  Rx =   0   senA  cosA  0
         0    0     0    1
*/
Matriz Mrx(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, cos(alfa), sin(alfa), 0),
                Vetor(0, -sin(alfa), cos(alfa), 0),
                Vetor(0, 0, 0, 1));
}

// 3.2) Rotação em y
/*
         cosA    0     senA    0
         0       1     0       0
  Ry =   -senA   0     cosA    0
         0       0     0       1
*/
Matriz Mry(double alfa)
{
  return Matriz(Vetor(cos(alfa), 0, -sin(alfa), 0),
                Vetor(0, 1, 0, 0),
                Vetor(sin(alfa), 0, cos(alfa), 0),
                Vetor(0, 0, 0, 1));
}

// 3.3) Rotação em z
/*
         cosA -senA 0 0
         senA cosA  0 0
  Rz =   0    0     1 0
         0    0     0 1
*/
Matriz Mrz(double alfa)
{
  return Matriz(Vetor(cos(alfa), sin(alfa), 0, 0),
                Vetor(-sin(alfa), cos(alfa), 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

// 4) Espelhamento
// 4.1) Espelhamento xy
/*
          1 0 0  0
          0 1 0  0
  Exy =   0 0 -1 0
          0 0 0  1
*/
Matriz Mespxy()
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, 0, -1, 0),
                Vetor(0, 0, 0, 1));
}

// 4.2) Espelhamento xz
/*
          1 0  0 0
          0 -1 0 0
  Exz =   0 0  1 0
          0 0  0 1
*/
Matriz Mespxz()
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, -1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

// 4.3) Espelhamento yz
/*
          -1 0 0 0
          0  1 0 0
  Eyz =   0  0 1 0
          0  0 0 1
*/
Matriz Mespyz()
{
  return Matriz(Vetor(-1, 0, 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

// 5) Cisalhamento
// 5.1) Cisalhamento yx
/*
          1 tgA 0 0
          0  1  0 0
  Cyx =   0  0  1 0
          0  0  0 1
*/
Matriz Mcisyx(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(tan(alfa), 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

// 5.2) Cisalhamento xy
/*
          1   0  0 0
          tgA 1  0 0
  Cxy =   0   0  1 0
          0   0  0 1
*/
Matriz Mcisxy(double alfa)
{
  return Matriz(Vetor(1, tan(alfa), 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

// 5.3) Cisalhamento xz
/*
          1   0  0 0
          0   1  0 0
  Cxz =   tgA 0  1 0
          0   0  0 1
*/
Matriz Mcisxz(double alfa)
{
  return Matriz(Vetor(1, 0, tan(alfa), 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

// 5.4) Cisalhamento zx
/*
          1  0 tgA 0
          0  1  0  0
  Czx =   0  0  1  0
          0  0  0  1
*/
Matriz Mciszx(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(tan(alfa), 0, 1, 0),
                Vetor(0, 0, 0, 1));
}


// 5.5) Cisalhamento yz
/*
          1 0    0 0
          0 1    0  0
  Cyz =   0 tgA  1 0
          0  0   0 1
*/
Matriz Mcisyz(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, tan(alfa), 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

// 5.6) Cisalhamento zy
/*
          1  0  0    0
          0  1  tgA  0
  Czy =   0  0  1    0
          0  0  0    1
*/
Matriz Mciszy(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, tan(alfa), 1, 0),
                Vetor(0, 0, 0, 1));
}


Matriz CorrecaoCisyx(double alfa)
{
  return Matriz(Vetor(1, -tan(alfa), 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

Matriz CorrecaoCisxy(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(-tan(alfa), 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

Matriz CorrecaoCisxz(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(-tan(alfa), 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

Matriz CorrecaoCiszx(double alfa)
{
  return Matriz(Vetor(1, 0, -tan(alfa), 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

Matriz CorrecaoCisyz(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, 0, 0),
                Vetor(0, -tan(alfa), 1, 0),
                Vetor(0, 0, 0, 1));
}

Matriz CorrecaoCiszy(double alfa)
{
  return Matriz(Vetor(1, 0, 0, 0),
                Vetor(0, 1, -tan(alfa), 0),
                Vetor(0, 0, 1, 0),
                Vetor(0, 0, 0, 1));
}

Matriz CorrecaoEscalaNaoUniforme(double ex, double ey, double ez)
{
  return Matriz(Vetor(1/ex, 0, 0, 0),
                Vetor(0, 1/ey, 0, 0),
                Vetor(0, 0, 1/ez, 0),
                Vetor(0, 0, 0, 1));
}