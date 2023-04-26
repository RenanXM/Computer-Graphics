#include <vector>
#include "alglin.h"
#include "cenario.h"
#include "iluminacao.h"
#include "imagem.h"
#include "objeto.h"
#include "observador.h"
using std::vector;

//função que veririca se um determinado objeto é iluminado.
bool Cenario::intersecLuz(Objeto *Obj, Cenario *cenario, Ponto *Pi, LuzPontual *Lp)
{
  //vetor l vai ser o vetor L do objeto, que é o mesmo pra qlqr
  //objeto e multiplico por -1. (duvida brando)
  //mudamos o sentido do vetor L
  Vetor *l = multEscV(Obj->calcL(Pi, Lp->Pf), -1);

  //passamos como parâmetro para a função intersecObj 
  //que originalmente recebe "intersecObj(Ponto *P0, Vetor *dr)"
  //o ponto onde está a luz e o vetor l. 
  float t_verdadeiro = Obj->intersecObj(Lp->Pf, l);

  //
  // float t_atual = Modulo(subP(Lp->Pf, Pi));

  // if (t_atual != t_verdadeiro) return false;

  // 1) Verificamos se há algum objeto entre a Luz e o ponto Pi
  float aux;
  for (int i = 0; i < cenario->Objetos.size(); i++)
  {
    aux = cenario->Objetos[i]->intersecObj(Lp->Pf, l);
    if (aux > 0 && aux < t_verdadeiro) //tem alguém na frente
      return false;
  }
  //verificamos se o 't' do objeto 'i' é positivo e menor que o 
  //t_verdadeiro. Em caso positivo, true. 
  //caso negativo, false (sombra???) (duvida brando)
  return true;
}


//Retorna a soma de Intesidades Difusa + Especular
Intensidade *Cenario::iluminarIndiv(Objeto *obj, Ponto *Pi, Cenario *cenario, Vetor *dr, LuzPontual *Lp)
{
  Intensidade *Total = new Intensidade(0, 0, 0);

  //se houver intersecção da luz no objeto:
  if (intersecLuz(obj, cenario, Pi, Lp))
  { 
    // alimentamos os ingredientes com as devidas funções do objeto
    Vetor *n = obj->calcN(Pi);
    Vetor *l = obj->calcL(Pi, Lp->Pf);
    Vetor *r = obj->calcR(n, l);
    Vetor *v = obj->calcV(dr);

    //difusa
    float fdif = prodEsc(l, n);

    //especular
    float fesp = 0;
    //Dúvida Brando
    if (prodEsc(r, v) > 0) fesp = pow(prodEsc(r, v), obj->m);

    //entendido
    Intensidade *Dif = new Intensidade(0, 0, 0);
    if (fdif > 0)
      Dif = escalarI(arroba(Lp->If, obj->Kd), fdif);

    //entendido
    Intensidade *Esp = new Intensidade(0, 0, 0);
    if (fesp > 0)
      Esp = escalarI(arroba(Lp->If, obj->Ke), fesp);

    Total = somaI(Dif, Esp);
  }
  
  //retornamos a soma da especular + difusa.
  return Total;
}


//
Cor *Cenario::iluminarFinal(Ponto *Pi, Objeto *escolhido, Vetor *dr)
{
  Intensidade *Total = new Intensidade(0, 0, 0);
  Intensidade *LuzIndividual;
  Intensidade *LuzAmbiente = arroba(this->LA->Ia, escolhido->Ka);
  ;
  for (int i = 0; i < this->Luzes.size(); i++)
  {
    LuzIndividual = iluminarIndiv(escolhido, Pi, this, dr, this->Luzes[i]);
    Total = somaI(Total, LuzIndividual);
  }

  Total = somaI(Total, LuzAmbiente);
  if (Total->r > 1)
    Total->r = 1;
  if (Total->g > 1)
    Total->g = 1;
  if (Total->b > 1)
    Total->b = 1;

  return new Cor(Total->r * MAX, Total->g * MAX, Total->b * MAX);
}

//retorna o objeto visto pelo observador.
int Cenario::escolheObj(Ponto *P0, Vetor *dr)
{
  float t, min;
  int indice = -1;
  min = -1;
  for (int i = 0; i < this->Objetos.size(); i++)
  {
    t = this->Objetos[i]->intersecObj(P0, dr);
    if ((indice < 0 && t > 0) || (indice > 0 && t > 0 && t < min))
    {
      min = t;
      indice = i;
    }
  }
  //depois de percorrer, e verificarmos a cada iteração se o t do objeto atual
  //é menor que o t atual (significa que o observador vê antes), ao final do laço
  //teremos o valor minímo e seu respectivo índice, que é retornado para sabermos
  //que objeto está nessa posição do vetor de objetos. 
  return indice;
}


void Cenario::desenhar(SDL_Renderer *renderer, Observador *Obs, float d)
{
  Ponto *P0 = Obs->P0;
  float dx = (float)Wj / nCol;
  float dy = (float)Hj / nLin;
  float x, y;
  Vetor *dr;
  Objeto *escolhido;
  int indice;
  Ponto *Pi;
  Cor *cor;

  for (int l = 0; l < nLin; l++)
  {
    y = (Hj / 2) - (dy * (l + 0.5));
    for (int c = 0; c < nCol; c++)
    {
      x = -(Wj / 2) + (dx * (c + 0.5));

      dr = new Vetor(x - P0->x, y - P0->y, -d - P0->z);

      indice = this->escolheObj(P0, dr);

      if (indice >= 0)
      {
        escolhido = this->Objetos[indice];
        Pi = addPV(P0, multEscV(dr, escolhido->intersecObj(P0, dr)));
        cor = this->iluminarFinal(Pi, escolhido, dr);
      }
      else
      {
        cor = new Cor(255, 0, 0);
      }
      SDL_SetRenderDrawColor(renderer, cor->r, cor->g, cor->b, 255);
      SDL_RenderDrawPoint(renderer, c, l);
    }
  }
  SDL_RenderPresent(renderer);
}
