#include "objeto.h"
Objeto::Objeto(){}

Objeto::Objeto(Intensidade Ke, Intensidade Kd, Intensidade Ka, double m)
{
  this->Ke = Ke;
  this->Kd = Kd;
  this->Ka = Ka;
  this->m = m;
}
Vetor Objeto::calcN(Ponto Pi, Vetor dr)
{
  return Vetor(1, 1, 1);
}

double Objeto::intersecObj(Ponto P0, Vetor dr, int i)
{
  return -1;
}


void Objeto::intersecTextura(Ponto Pi)
{
}

Vetor Objeto::calcL(Ponto Pi, Ponto Pf)
{
  return divEscV(subP(Pf, Pi), Modulo(subP(Pf, Pi)));
}

Vetor Objeto::calcR(Vetor n, Vetor l)
{
  // Vetor r = subV(multEscV(n, 2 * prodEsc(l, n)), l);
  // return multEscV(r, 1/Modulo(r));
  return subV(multEscV(n, 2 * prodEsc(l, n)), l);
}

Vetor Objeto::calcV(Vetor dr)
{
  return divEscV(dr, -Modulo(dr));
}


// Ponto Novo = M * Ponto Antigo
// 1) Translação
/*
        1 0 0 tx
        0 1 0 ty
  T =   0 0 1 tz
        0 0 0 1
*/
void Objeto::translacao(double tx, double ty, double tz){}

// 2) Escala
/*
        Ex 0  0  0
        0  Ey 0  0
  E =   0  0  Ez 0
        0  0  0  1
*/
void Objeto::escala(double ex, double ey, double ez){}

void Objeto::escala(double e){}


// 3) Rotação
// 3.1) Rotação em x
/*
         1    0     0    0
         0   cosA -senA  0
  Rx =   0   senA  cosA  0
         0    0     0    1
*/
void Objeto::rx(double alfa){}

// 3.2) Rotação em y
/*
         cosA    0     senA    0
         0       1     0       0
  Ry =   -senA   0     cosA    0
         0       0     0       1
*/
void Objeto::ry(double alfa){}

// 3.3) Rotação em z
/*
         cosA -senA 0 0
         senA cosA  0 0
  Rz =   0    0     1 0
         0    0     0 1
*/
void Objeto::rz(double alfa){}

// 4) Espelhamento
// 4.1) Espelhamento xy
/*
          1 0 0  0
          0 1 0  0
  Exy =   0 0 -1 0
          0 0 0  1
*/
void Objeto::espXY(){}

// 4.2) Espelhamento xz
/*
          1 0  0 0
          0 -1 0 0
  Exz =   0 0  1 0
          0 0  0 1
*/
void Objeto::espXZ(){}

// 4.3) Espelhamento yz
/*
          -1 0 0 0
          0  1 0 0
  Eyz =   0  0 1 0
          0  0 0 1
*/
void Objeto::espYZ(){}

// 5) Cisalhamento
// 5.1) Cisalhamento yx
/*
          1 tgA 0 0
          0  1  0 0
  Cyx =   0  0  1 0
          0  0  0 1
*/
void Objeto::cisalhamentoYX(double alfa){}

// 5.2) Cisalhamento xy
/*
          1   0 0 0
          tgA 1  0 0
  Cxy =   0   0  1 0
          0   0  0 1
*/
void Objeto::cisalhamentoXY(double alfa){}

// 5.3) Cisalhamento xz
/*
          1   0  0 0
          0   1  0 0
  Cxz =   tgA 0  1 0
          0   0  0 1
*/
void Objeto::cisalhamentoXZ(double alfa){}

// 5.4) Cisalhamento zx
/*
          1  0 tgA 0
          0  1  0  0
  Czx =   0  0  1  0
          0  0  0  1
*/
void Objeto::cisalhamentoZX(double alfa){}

// 5.5) Cisalhamento yz
/*
          1 0    0 0
          0 1    0  0
  Cyz =   0 tgA  1 0
          0  0   0 1
*/
void Objeto::cisalhamentoYZ(double alfa){}

// 5.6) Cisalhamento zy
/*
          1  0  0    0
          0  1  tgA  0
  Czy =   0  0  1    0
          0  0  0    1
*/
void Objeto::cisalhamentoZY(double alfa){}