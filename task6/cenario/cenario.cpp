#include "cenario.h"

Cor Cenario::iluminarFinal(Ponto Pi, Objeto *escolhido, Vetor dr)
{
  Intensidade Total = Intensidade(0, 0, 0);
  Intensidade LuzIndividual;

  /*
  for (int i = 0; i < this->Luzes.size(); i++)
  {
    LuzIndividual = this->Luzes[i]->iluminar(escolhido, Pi, dr, this->Objetos);
    Total = somaI(Total, LuzIndividual);
  }
  */

  for (Luz *luz : this->Luzes)
  {
    LuzIndividual = luz->iluminar(escolhido, Pi, dr, this->Objetos);
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

int Cenario::escolheObj(Ponto P0, Vetor dr, double *pont_ti)
{
  double t, min;
  int indice = -1;
  min = -1;
  /*
  for (int i = 0; i < this->Objetos.size(); i++)
  {
    t = this->Objetos[i]->intersecObj(P0, dr);
    if ((indice < 0 && t > 0) || (indice > 0 && t > 0 && t < min))
    {
      min = t;
      indice = i;
    }
  }
  */

  int i = 0;
  for (Objeto *obj : this->Objetos)
  {
    t = obj->intersecObj(P0, dr, 0);
    if ((indice < 0 && t > 0) || (indice > 0 && t > 0 && t < min))
    {
      min = t;
      indice = i;
    }
    i++;
  }

  *pont_ti = min;

  return indice;
}

void Cenario::desenhar(SDL_Renderer *renderer, SDL_Window *window, Camera *camera)
{
  
  Ponto P0 = camera->obs->P0;
  Ponto Pdesatualizado, Patualizado;
  double dx = (double)Wj / nCol;
  double dy = (double)Hj / nLin;
  double x, y;
  Vetor dr;
  Objeto *escolhido;
  int indice;
  Ponto Pi;
  Cor cor;
  double janelaX = camera->janela->cj.x;
  double janelaY = camera->janela->cj.y;
  double janelaZ = camera->janela->cj.z;
  double ti;
  double *pont_ti = &ti;

  while (!(camera->exit))
  {
    P0 = camera->obs->P0;
    /*
    double dx = (double)Wj / nCol;
    double dy = (double)Hj / nLin;
    double x, y;
    Vetor dr;
    Objeto *escolhido;
    int indice;
    Ponto Pi;
    Cor cor;
    double janelaX = camera->janela->cj.x;
    double janelaY = camera->janela->cj.y;
    double janelaZ = camera->janela->cj.z;
    double ti;
    double *pont_ti = &ti;
    */
    for (int l = 0; l < nLin; l++)
    {
      y = (Hj / 2) - (dy * (l + 0.5)) + janelaY;
      for (int c = 0; c < nCol; c++)
      {
        x = -(Wj / 2) + (dx * (c + 0.5)) + janelaX;
        
        Pdesatualizado = Ponto(x, y, janelaZ);

        Patualizado = prodMP(camera->m, Pdesatualizado);

        //dr = Vetor(x - P0.x, y - P0.y, janelaZ - P0.z);
        
        dr = subP(Patualizado, P0);
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
    /*
    if (camera->exit)
    {
      listenEventQuit(window);
    }
    */
    camera->mudarPontoDeVista();
    // camera->translacao(0, 0, 20);
    // camera->espxy();
  }
}
