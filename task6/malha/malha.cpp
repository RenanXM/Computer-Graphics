#include "malha.h"
#include <iostream>
Malha::Malha()
{
}

Malha::Malha(Intensidade Ke, Intensidade Kd, Intensidade Ka, double m) : Objeto(Ke, Kd, Ka, m)
{
}

Malha::Malha(string path, Intensidade Kd, Intensidade Ke, Intensidade Ka, double m) : Objeto(Ke, Kd, Ka, m)
{
  this->inicializar(path);
}

void Malha::inicializar(string path)
{
}

void Malha::calcN_e_R1xR2(Face *f)
{
  int idVertice11 = this->arestas[f->idAresta1]->idVI;
  int idVertice12 = this->arestas[f->idAresta1]->idVF;

  int idVertice21 = this->arestas[f->idAresta2]->idVI;
  int idVertice22 = this->arestas[f->idAresta2]->idVF;

  int v1, v2, v3, n1, n;
  n1 = (idVertice11 + 1) * (idVertice12 + 1);
  n = n1 / (idVertice21 + 1);

  if (n == (idVertice11 + 1) || n == (idVertice12 + 1))
  {
    v1 = idVertice21;
    v2 = idVertice22;
    v3 = n - 1;
  }
  else
  {
    v1 = idVertice22;
    v2 = idVertice21;
    v3 = (n1 / (v1 + 1)) - 1;
  }

  Ponto P1 = this->vertices[v1]->p;
  Ponto P2 = this->vertices[v2]->p;
  Ponto P3 = this->vertices[v3]->p;

  Vetor r1 = subP(P2, P1);
  Vetor r2 = subP(P3, P1);
  Vetor r1xr2 = prodVetorial(r1, r2);

  Vetor normal = divEscV(r1xr2, Modulo(r1xr2));
  f->setVetores(normal, r1, r2, r1xr2);
  f->setP1(P1);
}

void Malha::calcFaces()
{
  /*
  for (int i = 0; i < (this->faces).size(); i++)
    this->calcN_e_R1xR2(this->faces[i]);
  */
  for (Face *F : this->faces)
  {
    this->calcN_e_R1xR2(F);
  }
}

double Malha::intersecObj(Ponto P0, Vetor dr, int iescolha)
{
  double ti, tmin, c1, c2;
  int idmin = 0;
  // Face* face;
  Vetor n, v;
  Ponto Pplano, Pi;

  tmin = -1;

  /*
  for (int i = 0; i < this->faces.size(); i++)
  {
    face = this->faces[i];
    n = face->n;
    if (prodEsc(dr, n) < 0)
    {
      Pplano = face->P1;
      ti = -((prodEsc(subP(P0, Pplano), n)) / prodEsc(dr, n));

      if (ti > 0)
      {
        Pi = addPV(P0, multEscV(dr, ti));
        v = subP(Pi, Pplano);
        if (prodEsc(face->r1xr2, n) != 0)
        {
          c1 = prodEsc(prodVetorial(v, face->r2), n) / prodEsc(face->r1xr2, n);
          c2 = prodEsc(prodVetorial(face->r1, v), n) / prodEsc(face->r1xr2, n);
          if ((c1 >= 0) && (c2 >= 0) && ((c1 + c2) <= 1) && ((tmin < 0) || ((tmin > 0) && (ti < tmin))))
          {
            // tplano é válido
            idmin = i;
            tmin = ti;
          }
        }
      }
    }
  }
  */
  int i = 0;
  for (Face *face : this->faces)
  {
    n = face->n;
    if (prodEsc(dr, n) < 0)
    {
      Pplano = face->P1;
      ti = -((prodEsc(subP(P0, Pplano), n)) / prodEsc(dr, n));

      if (ti > 0)
      {
        Pi = addPV(P0, multEscV(dr, ti));
        v = subP(Pi, Pplano);
        if (prodEsc(face->r1xr2, n) != 0)
        {
          c1 = prodEsc(prodVetorial(v, face->r2), n) / prodEsc(face->r1xr2, n);
          c2 = prodEsc(prodVetorial(face->r1, v), n) / prodEsc(face->r1xr2, n);
          if ((c1 >= 0) && (c2 >= 0) && ((c1 + c2) <= 1) && ((tmin < 0) || ((tmin > 0) && (ti < tmin))))
          {
            // tplano é válido
            idmin = i;
            tmin = ti;
          }
        }
      }
    }
    i++;
  }

  if (tmin > 0)
  {
    if (iescolha == 0) this->escolha = idmin;
    return tmin;
  }
  return -1;
}

Vetor Malha::calcN(Ponto Pi, Vetor dr)
{
  return this->faces[this->escolha]->n;
}

// Ponto Novo = M * Ponto Antigo
// 1) Translação
/*
        1 0 0 tx
        0 1 0 ty
  T =   0 0 1 tz
        0 0 0 1
*/
void Malha::transformacaoECorrecaoFaces(Matriz m)
{
  // Modificando os pontos
  for (Vertice *V : this->vertices)
  {
    V->setP(prodMP(m, V->p));
  }

  // Consertando as faces
  this->calcFaces();
}

void Malha::translacao(double tx, double ty, double tz)
{
  Matriz m = Mtranslacao(tx, ty, tz);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {
    V->setP(Ponto(V->p.x + tx,
                  V->p.y + ty,
                  V->p.z + tz));
    // V->setP(prodMP(m, V->p));
  }
  this->calcFaces();
  */
}

// 2) Escala
/*
        Ex 0  0  0
        0  Ey 0  0
  E =   0  0  Ez 0
        0  0  0  1
*/
void Malha::escala(double ex, double ey, double ez)
{
  Matriz m = Mescala(ex, ey, ez);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x * ex,
                  V->p.y * ey,
                  V->p.z * ez));
    //V->setP(prodMP(m, V->p));
  }
  this->calcFaces();
  */
}

void Malha::escala(double e)
{
  this->escala(e, e, e);
}

// 3) Rotação
// 3.1) Rotação em x
/*
         1    0     0    0      x
         0   cosA -senA  0      y
  Rx =   0   senA  cosA  0      z
         0    0     0    1
*/
void Malha::rx(double alfa)
{
  Matriz m = Mrx(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x,
                  V->p.y * cos(alfa) - V->p.z * sin(alfa),
                  V->p.y * sin(alfa) + V->p.z * cos(alfa)));

    //V->setP(prodMP(m, V->p));
  }
  this->calcFaces();
  */
}

// 3.2) Rotação em y
/*
         cosA    0     senA    0   x
         0       1     0       0   y
  Ry =   -senA   0     cosA    0   z
         0       0     0       1
*/
void Malha::ry(double alfa)
{
  Matriz m = Mry(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x * cos(alfa) + V->p.z * sin(alfa),
                  V->p.y,
                 -V->p.x * sin(alfa) + V->p.z * cos(alfa)));

    //V->setP(prodMP(m, V->p));
  }
  this->calcFaces();
  */
}

// 3.3) Rotação em z
/*
         cosA -senA 0 0   x
         senA cosA  0 0   y
  Rz =   0    0     1 0   z
         0    0     0 1
*/
void Malha::rz(double alfa)
{
  Matriz m = Mrz(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x * cos(alfa) - V->p.y * sin(alfa),
                  V->p.x * sin(alfa) + V->p.y * cos(alfa),
                  V->p.z));

    // V->setP(prodMP(m, V->p));
  }
  this->calcFaces();
  */
}

// 4) Espelhamento
// 4.1) Espelhamento xy
/*
          1 0 0  0
          0 1 0  0
  Exy =   0 0 -1 0
          0 0 0  1
*/
void Malha::espXY()
{
  Matriz m = Mespxy();
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {
    V->setP(Ponto(V->p.x,
                  V->p.y,
                 -V->p.z));

    // V->setP(prodMP(Mespxy(), V->p));
  }
  this->calcFaces();
  */
}

// 4.2) Espelhamento xz
/*
          1 0  0 0
          0 -1 0 0
  Exz =   0 0  1 0
          0 0  0 1
*/
void Malha::espXZ()
{
  Matriz m = Mespxz();
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x,
                 -V->p.y,
                  V->p.z));

    // V->setP(prodMP(Mespxz(), V->p));
  }
  this->calcFaces();
  */
}

// 4.3) Espelhamento yz
/*
          -1 0 0 0
          0  1 0 0
  Eyz =   0  0 1 0
          0  0 0 1
*/
void Malha::espYZ()
{
  Matriz m = Mespyz();
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {
    V->setP(Ponto(-V->p.x,
                   V->p.y,
                   V->p.z));

    // V->setP(prodMP(Mespyz(), V->p));
  }
  this->calcFaces();
  */
}

// 5) Cisalhamento
// 5.1) Cisalhamento yx
/*
          1 tgA 0 0
          0  1  0 0
  Cyx =   0  0  1 0
          0  0  0 1
*/
void Malha::cisalhamentoYX(double alfa)
{
  Matriz m = Mcisyx(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x + V->p.y * tan(alfa),
                  V->p.y,
                  V->p.z));
    // V->setP(prodMP(Mcisyx(alfa), V->p));
  }
  this->calcFaces();
  */
}

// 5.2) Cisalhamento xy
/*
          1   0 0 0
          tgA 1  0 0
  Cxy =   0   0  1 0
          0   0  0 1
*/
void Malha::cisalhamentoXY(double alfa)
{
  Matriz m = Mcisxy(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {
    V->setP(Ponto(V->p.x,
                  V->p.x * tan(alfa) + V->p.y,
                  V->p.z));
    // V->setP(prodMP(Mcisxy(alfa), V->p));
  }
  this->calcFaces();
  */
}

// 5.3) Cisalhamento xz
/*
          1   0  0 0
          0   1  0 0
  Cxz =   tgA 0  1 0
          0   0  0 1
*/
void Malha::cisalhamentoXZ(double alfa)
{
  Matriz m = Mcisxz(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x,
                  V->p.y,
                  V->p.x * tan(alfa) + V->p.z));

    // V->setP(prodMP(Mcisxz(alfa), V->p));
  }
  this->calcFaces();
  */
}

// 5.4) Cisalhamento zx
/*
          1  0 tgA 0
          0  1  0  0
  Czx =   0  0  1  0
          0  0  0  1
*/
void Malha::cisalhamentoZX(double alfa)
{
  Matriz m = Mciszx(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {
    V->setP(Ponto(V->p.x + V->p.z * tan(alfa),
                  V->p.y,
                  V->p.z));
    // V->setP(prodMP(Mciszx(alfa), V->p));
  }
  this->calcFaces();
  */
}

// 5.5) Cisalhamento yz
/*
          1 0    0 0
          0 1    0  0
  Cyz =   0 tgA  1 0
          0  0   0 1
*/
void Malha::cisalhamentoYZ(double alfa)
{
  Matriz m = Mcisyz(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  // Modificando os pontos
  for (Vertice *V : this->vertices)
  {

    V->setP(Ponto(V->p.x,
                  V->p.y,
                  V->p.y * tan(alfa) + V->p.z));
    V->setP(prodMP(Mcisyz(alfa), V->p));
  }
  this->calcFaces();
  */
}

// 5.6) Cisalhamento zy
/*
          1  0  0    0
          0  1  tgA  0
  Czy =   0  0  1    0
          0  0  0    1
*/
void Malha::cisalhamentoZY(double alfa)
{
  Matriz m = Mciszy(alfa);
  this->transformacaoECorrecaoFaces(m);

  /*
  for (Vertice *V : this->vertices)
  {
    V->setP(Ponto(V->p.x,
                  V->p.y + V->p.z * tan(alfa),
                  V->p.z));
    V->setP(prodMP(Mciszy(alfa), V->p));
  }
  this->calcFaces();
  */
}