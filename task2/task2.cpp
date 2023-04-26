#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

//FEITO
void paintPixel(SDL_Renderer *renderer, int x, int y)
{
  SDL_RenderDrawPoint(renderer, x, y);
}

//FEITO
void update(SDL_Renderer *renderer)
{
  SDL_RenderPresent(renderer);
}

//FEITO
void setPaintColor(SDL_Renderer *renderer, int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

//FEITO
void setWindowBackground(SDL_Renderer *renderer, int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderClear(renderer);
}

//FEITO
void listenEventQuit(SDL_Window *window)
{
  SDL_Event event;
  bool isRunning = true;

  while (isRunning)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT)
        isRunning = false;
    }

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

// FEITO
void initializeSDLAndWindow(
    SDL_Window **window,
    SDL_Renderer **renderer,
    int width,
    int height)
{
  SDL_Init(SDL_INIT_VIDEO);

  // SDL_CreateWindowAndRenderer (
  //     500*4, 600*4, 0, &window, &renderer
  // );
  // SDL_RenderSetScale(renderer, 4, 4);

  SDL_CreateWindowAndRenderer(
      width, height, 0, window, renderer);
}

// FEITO
class Cor
{
public:
  int red;
  int green;
  int blue;
  Cor(){};
  Cor(int red, int green, int blue)
  {
    this->red = red;
    this->green = green;
    this->blue = blue;
  };
};

// FEITO
class Ponto
{
public:
  float x;
  float y;
  float z;
  Ponto(){};
  Ponto(float x, float y, float z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  };
};

// FEITO
class Intensidade
{
public:
  float x;
  float y;
  float z;
  Intensidade(){};
  Intensidade(float x, float y, float z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  };
};

// FEITO
class Vetor
{
public:
  float x;
  float y;
  float z;
  Vetor(){};
  Vetor(float x, float y, float z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  };
  void set(float x, float y, float z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

// Feito
class Esfera
{
public:
  int raio;
  Ponto centro;
  Cor cor;
  Esfera(int raio, Ponto centro, Cor cor)
  {
    this->raio = raio;
    this->centro = centro;
    this->cor = cor;
  };
};

// Não precisa
class Janela
{
public:
  int Hj = 500;
  int Wj = 500;
  int ncol = 500;
  int nlin = 500;
  Ponto centro;
  Janela(Ponto centro)
  {
    this->centro = centro;
  };
};

// Não precisa
class Canvas
{
public:
  int Hj = 500;
  int Wj = 500;
  int ncol = 500;
  int nlin = 500;
  Cor matriz[500][500];
};

// Feito
class Observador
{
public:
  Ponto P0;
  Observador(Ponto P0)
  {
    this->P0 = P0;
  };
};

// Feito
class Luz
{
public:
  Ponto Pf;
  Intensidade If;
  Luz(Ponto Pf, Intensidade If)
  {
    this->If = If;
    this->Pf = Pf;
  }
};

// Ok
float produtoEscalar(Vetor v1, Vetor v2)
{
  return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

// Ok
Intensidade Arroba(Intensidade I, Intensidade K)
{
  return Intensidade(I.x * K.x, I.y * K.y, I.z * K.z);
}

// Ok
float Modulo(Ponto P)
{
  return sqrt((P.x * P.x) + (P.y * P.y) + (P.z * P.z));
}


// Ok
float ModuloVetor(Vetor v)
{
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

// Ok
Ponto subtracao(Ponto P1, Ponto P2)
{
  return Ponto(P1.x - P2.x, P1.y - P2.y, P1.z - P2.z);
}

Cor iluminar(Ponto Pi, int raio, Luz fonte, Intensidade Ke, Intensidade Kd, Ponto C, Vetor dr)
{
  // Ingredientes
  Vetor n(subtracao(Pi, C).x / raio, subtracao(Pi, C).y / raio, subtracao(Pi, C).z / raio);

  Ponto Pf_Pi(subtracao(fonte.Pf, Pi).x, subtracao(fonte.Pf, Pi).y, subtracao(fonte.Pf, Pi).z);

  Vetor l(Pf_Pi.x / Modulo(Pf_Pi), Pf_Pi.y / Modulo(Pf_Pi), Pf_Pi.z / Modulo(Pf_Pi));

  Vetor r(n.x * 2 * produtoEscalar(l, n) - l.x, n.y * 2 * produtoEscalar(l, n) - l.y, n.z * 2 * produtoEscalar(l, n) - l.z);

  Vetor v(-dr.x / ModuloVetor(dr), -dr.y / ModuloVetor(dr), -dr.z / ModuloVetor(dr));

  float fdif = produtoEscalar(l, n);

  float fesp = produtoEscalar(r, v);

  // Difusa
  Intensidade Dif(0, 0, 0);
  if (fdif > 0) Dif = Intensidade(Arroba(fonte.If, Kd).x * fdif, Arroba(fonte.If, Kd).y * fdif, Arroba(fonte.If, Kd).z * fdif);

  // Especular
  Intensidade Esp (0, 0, 0);
  if (fesp > 0) Esp = Intensidade(Arroba(fonte.If, Ke).x * fesp, Arroba(fonte.If, Ke).y * fesp, Arroba(fonte.If, Ke).z * fesp);


  Intensidade Total(Dif.x + Esp.x, Dif.y + Esp.y, Dif.z + Esp.z);

  return Cor(Total.x * 255, Total.y * 255, Total.z * 255);
};

Cor verificaIntersecao(Ponto P0, Vetor dr, Ponto cEsfera, int r, Cor corEsfera, Cor background, Luz Fonte, Intensidade Ke, Intensidade Kd)
{
  Vetor w(P0.x - cEsfera.x, P0.y - cEsfera.y, P0.z - cEsfera.z);

  float a = produtoEscalar(dr, dr);
  float b = 2 * produtoEscalar(w, dr);
  float c = produtoEscalar(w, w) - r * r;

  float delta = b * b - 4 * a * c;
  if (delta < 0)
    return background;

  float t = (-b - sqrt(delta)) / (2 * a);
  Ponto Pi(P0.x + dr.x * t, P0.y + dr.y * t, P0.z + dr.z * t);

  return iluminar(Pi, r, Fonte, Ke, Kd, cEsfera, dr);
}

void pintarCanvas(Observador observador, Janela janela, Canvas *canvas, Esfera esfera, Cor background, int d, Luz Fonte, Intensidade Ke, Intensidade Kd)
{
  Ponto P0 = observador.P0;
  int Wj = janela.Wj;
  int Hj = janela.Hj;
  // A tela de mosquito é igual tanto para a janela quanto para o canvas
  int ncol = janela.ncol;
  int nlin = janela.nlin;

  float dx = ((float)Wj) / ncol;
  float dy = ((float)Hj) / nlin;
  float x;
  float y;
  Vetor dr;
  for (int l = 0; l < ncol; l++)
  {
    y = (Hj >> 1) - (dy * (l + 0.5));
    for (int c = 0; c < nlin; c++)
    {
      x = -(Wj >> 1) + (dx * (c + 0.5));
      dr.set(x, y, -d);
      canvas->matriz[l][c] = verificaIntersecao(P0, dr, esfera.centro, esfera.raio, esfera.cor, background, Fonte, Ke, Kd);
    }
  }
};

void renderSphere(SDL_Renderer *renderer, Canvas canvas)
{
  for (int l = 0; l < 500; l++)
  {
    for (int c = 0; c < 500; c++)
    {
      if (canvas.matriz[l][c].green == 0)
      {
        setPaintColor(renderer, canvas.matriz[l][c].red, canvas.matriz[l][c].green, canvas.matriz[l][c].blue, 255);
        paintPixel(renderer, c, l);
      }
    }
  }
}

// zEsfera > zObservador
int main(int argc, char *argv[])
{
  int dJanela = 200;
  int raio = 100;
  // O centro da janela está sobre o eixo z do sistema de coordenadas na posição (0, 0, - dJanela) em metros.
  Ponto cJanela(0, 0, -dJanela);

  // O centro da esfera deve estar sobre o eixo z com coordenada z < - (dJanela + rEsfera)
  Ponto cEsfera(0, 0, -(dJanela + raio));

  // O olho do pintor está na origem do sistema de coordenadas (0,0,0)
  Ponto P0(0, 0, 0);

  // A cor da esfera deve ser esfColor = 255, 0, 0
  Cor corEsfera(255, 0, 0);

  // A cor de background deve ser cinza bgColor = 100, 100, 100
  Cor cBackground(100, 100, 100);

  // Observador
  Observador observador(P0);

  // Janela
  Janela janela(cJanela);

  // Canvas
  Canvas canvas;

  // Esfera
  Esfera esfera(raio, cEsfera, corEsfera);

  // Elementos Novos
  Ponto Pf(-200, 0, 0);
  Intensidade If(0.7, 0.7, 0.7);
  Intensidade Ke(0.3, 0, 0);
  Intensidade Kd(0.5, 0, 0);

  Luz Fonte(Pf, If);

  pintarCanvas(observador, janela, &canvas, esfera, cBackground, dJanela, Fonte, Ke, Kd);

  // setup SDL
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  initializeSDLAndWindow(&window, &renderer, 500, 500);

  setWindowBackground(renderer, 100, 100, 100, 255);

  // render graphics
  renderSphere(renderer, canvas);
  update(renderer);

  // listen to close window event
  listenEventQuit(window);
  return 0;
}
