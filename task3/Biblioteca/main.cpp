#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "alglin.h"
#include "cenario.h"
#include "iluminacao.h"
#include "imagem.h"
#include "objeto.h"
#include "observador.h"

int main()
{
  // Dados iniciais
  // 1) Esfera
  Esfera* S = new Esfera(40, new Ponto(0, 0, -100), new Intensidade(0.7, 0.2, 0.2), new Intensidade(0.7, 0.2, 0.2), new Intensidade(0.7, 0.2, 0.2), 10);
  //Esfera* E1 = new Esfera(15, new Ponto(0, 35, -60), new Intensidade(0.7, 0.2, 0.2), new Intensidade(0.7, 0.2, 0.2), new Intensidade(0.7, 0.2, 0.2), 10);

  // Snowman
  Esfera* S1 = new Esfera(40, new Ponto(0, 0, -160), new Intensidade(0.5, 0.5, 0.5), new Intensidade(0.5, 0.5, 0.5), new Intensidade(0.5, 0.5, 0.5), 10);

  Esfera* S2 = new Esfera(30, new Ponto(0, 60, -150), new Intensidade(0.5, 0.5, 0.5), new Intensidade(0.5, 0.5, 0.5), new Intensidade(0.5, 0.5, 0.5), 10);

  // 2) Plano do chão
  Plano* chao = new Plano(new Ponto(0, -40, 0), new Vetor(0, 1, 0), new Intensidade(0, 0, 0), new Intensidade(0.2, 0.7, 0.2), new Intensidade(0.2, 0.7, 0.2), 1);

  // 3) Plano de Fundo
  Plano* fundo = new Plano(new Ponto(0, 0, -200), new Vetor(0, 0, 1), new Intensidade(0, 0, 0), new Intensidade(0.3, 0.3, 0.7), new Intensidade(0.3, 0.3, 0.7), 1);

  // 4) Observador
  Observador* Obs = new Observador(new Ponto(0, 0, 0));

  // 5) Fonte Pontual
  LuzPontual* Lp = new LuzPontual(new Ponto(0, 60, -30), new Intensidade(0.7, 0.7, 0.7));

  // 6) Luz Ambiente
  LuzAmbiente* La = new LuzAmbiente(new Intensidade(0.3, 0.3, 0.3));

  // 7) d
  float d = 30;

  // 8) Cenário em si
  Cenario* cenario = new Cenario();
  cenario->Objetos.push_back(S1);
  cenario->Objetos.push_back(S2);
  cenario->Objetos.push_back(chao);
  cenario->Objetos.push_back(fundo);
  cenario->Luzes.push_back(Lp);
  cenario->LA = La;
  // Inicialização
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  initialize(&window, &renderer);

  // Colocando cor ao Background
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

  // Limpar o Renderer
  SDL_RenderClear(renderer);

  cenario->desenhar(renderer, Obs, d);


  listenEventQuit(window);

  return 0;
}