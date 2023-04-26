#include "alglin.h"
#include "iluminacao.h"
#include "objeto.h"
#include "math.h"

//           OBJETO THINGS

//CalcN da classe Objeto. entendido
Vetor *Objeto::calcN(Ponto *Pi)
{
  return new Vetor(1, 1, 1);
}

//implementação qualquer pra Objeto. entendido
float Objeto::intersecObj(Ponto *P0, Vetor *dr)
{
  return -4000;
}

//implementação qualquer. entendido
bool Objeto::sombraPropria(Ponto *Pi, LuzPontual *Lp, Vetor *L, float t)
{
  return false;
}

//Calculo do L para qualquer objeto é isso: entendio.
Vetor *Objeto::calcL(Ponto *Pi, Ponto *Pf)
{
  return multEscV(subP(Pf, Pi), 1 / Modulo(subP(Pf, Pi)));
}

//Cálculo do R para qualaquer objeto é isso: entendido.
Vetor *Objeto::calcR(Vetor *n, Vetor *l)
{
  // Vetor *r = subV(multEscV(n, 2 * prodEsc(l, n)), l);
  // return multEscV(r, 1/Modulo(r));
  return subV(multEscV(n, 2 * prodEsc(l, n)), l);
}

//Cálculo do V para qualaquer objeto é isso: entendido.
Vetor *Objeto::calcV(Vetor *dr)
{
  return multEscV(dr, -1 / Modulo(dr));
}

//                  ESFERA THINGS

//
Esfera::Esfera() {}

//Construtor de uma esfera. entendido
Esfera::Esfera(float r, Ponto *c, Intensidade *Ke, Intensidade *Kd, Intensidade *Ka, float m)
{
  this->r = r;
  this->c = c;
  this->Ke = Ke;
  this->Kd = Kd;
  this->Ka = Ka;
  this->m = m;
}

//Cálculo do vetor N de uma *esfera* é feito assim.
Vetor *Esfera::calcN(Ponto *Pi)
{
  // Vetor* n = multEscV(subP(Pi, this->c), 1 / this->r);
  // return multEscV(n, 1/Modulo(n));
  return multEscV(subP(Pi, this->c), 1 / this->r);
}


// Verifica se o raio, em teoria, bate na Esfera
//retorna o valor das raízes t1 t2 se forem positivas.
float Esfera::intersecObj(Ponto *P0, Vetor *dr)
{
  Ponto *C = this->c; //Pegando o ponto central
  float radium = this->r; //Pegando o raio

  //aqui aplicamos a fórmula vista em sala e conseguimos os ingredientes
  //necessários para termos nossa equação do 2 grau.
  Vetor *w = subP(P0, C); 
  float a = prodEsc(dr, dr);
  float b = 2 * prodEsc(w, dr);
  float c = prodEsc(w, w) - (radium * radium);

  //delta
  float delta = (b * b) - (4 * a * c);
  if (delta < 0)
    //nao tem interseccao.
    return -1;

  float t1 = (-b - sqrt(delta)) / (2 * a);
  float t2 = (-b + sqrt(delta)) / (2 * a);

  if (t1 > 0)
    return t1; //retornamos o valor da primeira raiz
  if (t2 > 0)
    return t2; //retornamos o valor da segunda raiz
  return -1;
}


//??? serve de nada
//T serve pra achar o 
//ponto de intersção com algum objeto
//P(t) é é o ponto de intersecção de alguma coisa
//Escolhemos o objeto que retornar o menor t positivo
//Que é o que vai ser visto pelo observador.
//Isso sao apenas informações úteis. 
bool Esfera::sombraPropria(Ponto *Pi, LuzPontual *Lp, Vetor *l, float t)
{
  float t_correto = Modulo(subP(Lp->Pf, Pi));
  if (t > t_correto)
    return true;

  return false;
}

//               PLANO THINGS

//construtor vazio
Plano::Plano() {}

// construtor de um plano.
Plano::Plano(Ponto *Ppi, Vetor *npi, Intensidade *Ke, Intensidade *Kd, Intensidade *Ka, float m)
{
  this->Ppi = Ppi;
  this->npi = npi;
  this->Ke = Ke;
  this->Kd = Kd;
  this->Ka = Ka;
  this->m = m;
}

//
// Verifica se o raio, em teoria, bate no Plano
float Plano::intersecObj(Ponto *P0, Vetor *dr)
{
  //retorna esse valor aí.
  Vetor *w = subP(P0, this->Ppi);
  return -(prodEsc(w, this->npi) / prodEsc(dr, this->npi));
}

// Calculo do vetor Normal ao plano
Vetor *Plano::calcN(Ponto *Pi)
{
  return multEscV(this->npi, 1/Modulo(this->npi));
}

//inutil
bool Plano::sombraPropria(Ponto *Pi, LuzPontual *Lp, Vetor *l, float t)
{
  return false;
}