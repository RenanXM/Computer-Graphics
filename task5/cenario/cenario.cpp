#include "cenario.h"

bool Cenario::intersecLuz(Objeto *Obj, Ponto Pi, LuzPontual Lp)
{
  Vetor l = multEscV(Obj->calcL(Pi, Lp.Pf), -1);

  double t = Obj->intersecObj(Lp.Pf, l);

  // Verificamos se há algum objeto entre a Luz e o ponto Pi
  double aux;
  for (int i = 0; i < this->Objetos.size(); i++)
  {
    aux = this->Objetos[i]->intersecObj(Lp.Pf, l);
    if (aux > 0 && aux < t)
      return false;
  }
  return true;
}

Intensidade Cenario::iluminarIndiv(Objeto *obj, Ponto Pi, Vetor dr, LuzPontual Lp)
{
  Intensidade Total = Intensidade(0, 0, 0);

  if (intersecLuz(obj, Pi, Lp))
  {
    Vetor l = obj->calcL(Pi, Lp.Pf);
    Vetor n = obj->calcN(Pi, multEscV(l, -1));
    Vetor r = obj->calcR(n, l);
    Vetor v = obj->calcV(dr);

    double fdif = prodEsc(l, n);
  
    double fesp = 0;
    if (prodEsc(r, v) > 0) fesp = pow(prodEsc(r, v), obj->m);

    Intensidade Dif = Intensidade(0, 0, 0);
    if (fdif > 0)
      Dif = escalarI(arroba(Lp.If, obj->Kd), fdif);

    Intensidade Esp = Intensidade(0, 0, 0);
    if (fesp > 0)
      Esp = escalarI(arroba(Lp.If, obj->Ke), fesp);

    Total = somaI(Dif, Esp);
  }

  return Total;
}

Cor Cenario::iluminarFinal(Ponto Pi, Objeto *escolhido, Vetor dr)
{
  // Já inicializamos Total como LuzAmbiente
  Intensidade Total = arroba(this->LA.Ia, escolhido->Ka);
  Intensidade LuzIndividual;

  for (int i = 0; i < this->Luzes.size(); i++)
  {
    LuzIndividual = iluminarIndiv(escolhido, Pi, dr, this->Luzes[i]);
    Total = somaI(Total, LuzIndividual);
  }
  if (Total.r > 1)
    Total.r = 1;
  if (Total.g > 1)
    Total.g = 1;
  if (Total.b > 1)
    Total.b = 1;

  return Cor(Total.r * MAX, Total.g * MAX, Total.b * MAX);
}

int Cenario::escolheObj(Ponto P0, Vetor dr, double* pont_ti)
{
  double t, min;
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

  *pont_ti = min;

  return indice;
}

void Cenario::desenhar(SDL_Renderer *renderer, Observador Obs, Janela janela)
{
  Ponto P0 = Obs.P0;
  double dx = (double)Wj / nCol;
  double dy = (double)Hj / nLin;
  double x, y;
  Vetor dr;
  Objeto *escolhido;
  int indice;
  Ponto Pi;
  Cor cor;
  double janelaX = janela.x;
  double janelaY = janela.y;
  double janelaZ = janela.z;
  double ti;
  double *pont_ti = &ti;
  
  for (int l = 0; l < nLin; l++)
  {
    y = (Hj / 2) - (dy * (l + 0.5)) + janelaY;
    for (int c = 0; c < nCol; c++)
    {
      x = -(Wj / 2) + (dx * (c + 0.5)) + janelaX;

      dr = Vetor(x - P0.x, y - P0.y, janelaZ - P0.z);

      indice = this->escolheObj(P0, dr, pont_ti);

      if (indice >= 0)
      {
        escolhido = this->Objetos[indice];
        Pi = addPV(P0, multEscV(dr, ti));
        escolhido->intersecTextura(Pi);
        cor = this->iluminarFinal(Pi, escolhido, dr);
      }
      else
      {
        cor = Cor(100, 100, 100);
      }
      SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
      SDL_RenderDrawPoint(renderer, c, l);
    }
  }
  SDL_RenderPresent(renderer);
}
