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

void Cenario::desenhar(SDL_Renderer *renderer, SDL_Window *window)
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

  while (!(this->exit))
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
        
        if (camera->tipo_visao == 1)
        {
          dr = subP(Patualizado, P0);
        }

        else if (camera->tipo_visao == 2)
        {
          P0 = Patualizado;
          dr = camera->dr_camera;
        }
        
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

    this->menuGeral();
  }
}

void Cenario::menuGeral()
{
  int a;
  cout << "\n1 -> CâmeraXYZ\n2 -> CâmeraObservador\n3 -> Picking\n4 -> Encerrar programa\n";
  cin >> a;
  getchar();

  if (a == 1)
  {
    this->menuCameraXYZ();
  }

  else if (a == 2)
  {
    this->menuCameraObservador();
  }

  else if (a == 3)
  {
    this->picking();
  }

  else if (a == 4)
  {
    this->exit = true;
  }

  else
  {
    cout << "\nPor favor, digite uma opção válida!\n";
    this->menuGeral();
  }
}

void Cenario::picking()
{
  bool quit = false;
  SDL_Event e;
  int cMouse, lMouse;

  Objeto* objClicado;
  Ponto P0 = camera->obs->P0;
  Ponto Pdesatualizado, Patualizado;
  double dx = (double)Wj / nCol;
  double dy = (double)Hj / nLin;
  double x, y;
  Vetor dr;
  int indice;
  double janelaX = camera->janela->cj.x;
  double janelaY = camera->janela->cj.y;
  double janelaZ = camera->janela->cj.z;
  double ti;
  double *pont_ti = &ti;

  cout << "\nClique em algum objeto\n";
  while(quit == false)
  {
      while(SDL_PollEvent(&e) != 0)
      {
          if(e.type == SDL_MOUSEBUTTONDOWN)
          {
              SDL_GetMouseState(&cMouse,&lMouse);

              y = (Hj / 2) - (dy * (lMouse + 0.5)) + janelaY;
              x = -(Wj / 2) + (dx * (cMouse + 0.5)) + janelaX;

              Pdesatualizado = Ponto(x, y, janelaZ);

              Patualizado = prodMP(camera->m, Pdesatualizado);
              
              if (camera->tipo_visao == 1)
              {
                dr = subP(Patualizado, P0);
              }

              else if (camera->tipo_visao == 2)
              {
                P0 = Patualizado;
                dr = camera->dr_camera;
              }
              quit = true;
              indice = this->escolheObj(P0, dr, pont_ti);
              if (indice >= 0)
              {
                objClicado = this->Objetos[indice];
                this->menuPicking(objClicado);
              }
              else
              {
                cout << "\nNenhum objeto clicado!\n";
              }
          }
      }
  }
}

void Cenario::menuPicking(Objeto* objClicado)
{
  int a;

  cout << "\n1 -> Translação\n2 -> rx    3 -> ry    4 -> rz\n5 -> espxy    6 -> espxz    7 -> espyz\n8 -> cisYX    9 -> cisXY    10 -> cisXZ\n11 -> cisZX    12 -> cisYZ    13 -> cisZY\n";
  cin >> a;
  getchar();
  
  double tx, ty, tz, alfa;
  if (a == 1)
  {
    cout << "x: ";
    cin >> tx;
    cout << "y: ";
    cin >> ty;
    cout << "z: ";
    cin >> tz;
    objClicado->translacao(tx, ty, tz);
  }

  else if (a == 2 || a == 3 || a == 4 || ((a > 7) && (a < 14)))
  {
    cout << "angulo (em graus): ";
    cin >> alfa;
    alfa = (alfa * M_PI) / 180;
    /*
      2 pi = 360
        x  = alfa
    
    */
    if (a == 2)
    {
      objClicado->rx(alfa);
    }

    else if (a == 3)
    {
      objClicado->ry(alfa);
    }

    else if (a == 4)
    {
      objClicado->rz(alfa);
    }

    else if (a == 8)
    {
      objClicado->cisalhamentoYX(alfa);
    }

    else if (a == 9)
    {
      objClicado->cisalhamentoXY(alfa);
    }

    else if (a == 10)
    {
      objClicado->cisalhamentoXZ(alfa);
    }

    else if (a == 11)
    {
      objClicado->cisalhamentoZX(alfa);
    }

    else if (a == 12)
    {
      objClicado->cisalhamentoYZ(alfa);
    }

    else
    {
      objClicado->cisalhamentoZY(alfa);
    }
  }

  else if (a == 5)
  {
    objClicado->espXY();
  }

  else if (a == 6)
  {
    objClicado->espXZ();
  } 

  else if (a == 7)
  {
    objClicado->espYZ();
  }

  else
  {
    cout << "\nPor favor, digite uma opção válida!\n";
    this->menuPicking(objClicado);
  }

}

void Cenario::menuCameraXYZ()
{
int a;
  cout << "\n1 -> Translação\n2 -> rx    3 -> ry    4 -> rz\n5 -> espxy    6 -> espxz    7 -> espyz\n8 -> mudar visão\n";
  cin >> a;
  getchar();
  
  double tx, ty, tz, alfa;

  if (a == 1)
  {
    cout << "x: ";
    cin >> tx;
    cout << "y: ";
    cin >> ty;
    cout << "z: ";
    cin >> tz;
    camera->translacao(tx, ty, tz);
  }

  else if (a == 2 || a == 3 || a == 4)
  {
    cout << "angulo (em graus): ";
    cin >> alfa;
    alfa = (alfa * M_PI) / 180;
    if (a == 2)
    {
      camera->rx(alfa);
    }

    else if (a == 3)
    {
      camera->ry(alfa);
    }

    else
    {
      camera->rz(alfa);
    }
  }
  else if (a == 5)
  {
    camera->espxy();
  }

  else if (a == 6)
  {
    camera->espxz();
  } 

  else if (a == 7)
  {
    camera->espyz();
  }

  else if (a == 8)
  {
    cout << "\n1 - Visão perspectiva\n2 - Ortográfica\n";
    cin >> camera->tipo_visao;
  }

  else
  {
    cout << "\nPor favor, digite uma opção válida!\n";
    this->menuCameraXYZ();
  }
}

void Cenario::menuCameraObservador()
{
int a;
  cout << "\n1 -> Translação\n2 -> Virar Direita    3 -> Virar Esquerda\n4 -> Virar Cima    5 -> Virar Baixo\n6 -> mudar visão\n";
  cin >> a;
  getchar();
  
  double tx, ty, tz, alfa;
  if (a == 1)
  {
    cout << "x: ";
    cin >> tx;
    cout << "y: ";
    cin >> ty;
    cout << "z: ";
    cin >> tz;

    if (camera->dr_camera.z < 0)
    {
      tz = -tz;
    }

    if (camera->dr_camera.y < 0)
    {
      ty = -ty;
    }

    if (camera->dr_camera.x < 0)
    {
      tx = -tx;
    }

    camera->translacao(tx, ty, tz);
  }

  else if ( (a > 1) && (a < 6))
  {
    cout << "angulo (em graus): ";
    cin >> alfa;
    alfa = (alfa * M_PI) / 180;

    // VIRAR DIREITA
    if (a == 2)
    {
      camera->ry(-alfa);
    }

    // VIRAR ESQUERDA
    else if (a == 3)
    {
      camera->ry(alfa);
    }

    // VIRAR CIMA
    else if (a == 4)
    {
      camera->rx(alfa);
    }

    // VIRAR BAIXO
    else
    {
      camera->rx(-alfa);
    }
  }

  else if (a == 6)
  {
    cout << "\n1 - Visão perspectiva\n2 - Ortográfica\n";
    cin >> camera->tipo_visao;
  }

  else
  {
    cout << "\nPor favor, digite uma opção válida!\n";
    this->menuCameraObservador();
  }
}