#include <iostream>
#include <cmath>
#include "SDL.h"



void paintPixel(SDL_Renderer* renderer, int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}

void update(SDL_Renderer* renderer)
{
    SDL_RenderPresent(renderer);
}

void setPaintColor(SDL_Renderer* renderer, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void setWindowBackground(SDL_Renderer* renderer, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

void listenEventQuit(SDL_Window* window)
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

void initializeSDLAndWindow(
    SDL_Window** window,
    SDL_Renderer** renderer,
    int width,
    int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    // SDL_CreateWindowAndRenderer (
    //     200*4, 600*4, 0, &window, &renderer
    // );
    // SDL_RenderSetScale(renderer, 4, 4);

    SDL_CreateWindowAndRenderer(
        width, height, 0, window, renderer);
}


class Cor
{
public:
    int red;
    int green;
    int blue;
    Cor() {};
    Cor(int red, int green, int blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    };
};

class Ponto
{
public:
    float x;
    float y;
    float z;
    Ponto() {};
    Ponto(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    };
};

class Vetor
{
public:
    float x;
    float y;
    float z;
    Vetor() {};
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

class Janela
{
public:
    int Hj = 200;
    int Wj = 200;
    int ncol = 200;
    int nlin = 200;
    Ponto centro;
    Janela(Ponto centro)
    {
        this->centro = centro;
    };
};

class Canvas
{
public:
    int Hj = 200;
    int Wj = 200;
    int ncol = 200;
    int nlin = 200;
    Cor matriz[200][200];
};

class Observador
{
public:
    Ponto P0;
    Observador(Ponto P0)
    {
        this->P0 = P0;
    };
};

float produtoEscalar(Vetor v1, Vetor v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

Cor verificaIntersecao(Ponto P0, Vetor dr, Ponto cEsfera, int r, Cor corEsfera, Cor background)
{
    Vetor w(P0.x - cEsfera.x, P0.y - cEsfera.y, P0.z - cEsfera.z);

    float a = produtoEscalar(dr, dr);
    float b = 2 * produtoEscalar(w, dr);
    float c = produtoEscalar(w, w) - r * r;

    float delta = b * b - 4 * a * c;
    if (delta < 0) return background;
    return corEsfera;
}

void pintarCanvas(Observador observador, Janela janela, Canvas* canvas, Esfera esfera, Cor background, int d)
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
        y = (Hj >> 1) - (dy * (l - 0.5));
        for (int c = 0; c < nlin; c++)
        {
            x = -(Wj >> 1) + (dx * (c + 0.5));
            dr.set(x, y, -d);
            canvas->matriz[l][c] = verificaIntersecao(P0, dr, esfera.centro, esfera.raio, esfera.cor, background);
        }
    }
};

void renderSphere(SDL_Renderer* renderer, Canvas canvas)
{
    for (int l = 0; l < 200; l++)
    {
        for (int c = 0; c < 200; c++)
        {
            if (canvas.matriz[l][c].red == 255)
            {
                paintPixel(renderer, l, c);
            }
        }
    }
}


// zEsfera > zObservador
int main(int argc, char* argv[])
{
    int dJanela = 3000;
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

    pintarCanvas(observador, janela, &canvas, esfera, cBackground, dJanela);

    // setup SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    initializeSDLAndWindow(&window, &renderer, 200, 200);

    setWindowBackground(renderer, 100, 100, 100, 255);
    setPaintColor(renderer, 255, 0, 0, 255);

    // render graphics
    renderSphere(renderer, canvas);
    update(renderer);

    // listen to close window event
    listenEventQuit(window);
    return 0;
}
