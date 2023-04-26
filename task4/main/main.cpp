#include <iostream>
#include "../cenario/cenario.h"

int main()
{
  // Snowmen
  //Esfera* S1 = new Esfera(40, Ponto(0, 0, -160), Intensidade(0.8, 0.8, 0.8), Intensidade(0.8, 0.8, 0.8), Intensidade(0.8, 0.8, 0.8), 20);

  //Esfera* S2 = new Esfera(25, Ponto(0, 65, -150), Intensidade(0.8, 0.8, 0.8), Intensidade(0.8, 0.8, 0.8), Intensidade(0.8, 0.8, 0.8), 20);

  // Plano da Parede esquerda
  //Plano* esq = new Plano(Ponto(-120, 0,0), Vetor(1, 0, 0), Intensidade(0, 0, 0), Intensidade(0.8, 0.2, 0.2), Intensidade(0.8, 0.2, 0.2), 1);

  // PLano da Parede Direita
  //Plano* dir = new Plano(Ponto(100, 0, 0), Vetor(-1, 0, 0), Intensidade(0, 0, 0), Intensidade(0.5, 0.5, 0.5), Intensidade(0.5, 0.5, 0.5), 1);


  // Dados iniciais
  // 1) Esfera
  Esfera* S = new Esfera(40, Ponto(0, 0, -100), Intensidade(0.7, 0.2, 0.2), Intensidade(0.7, 0.2, 0.2), Intensidade(0.7, 0.2, 0.2), 10);

  // Cilindro
  Cilindro* C = new Cilindro((double) 40/3, 120, Ponto(0, 0, -100), Vetor(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3)), false, false, Intensidade(0.2, 0.3, 0.8), Intensidade(0.2, 0.3, 0.8), Intensidade(0.2, 0.3, 0.8), 1);

  Ponto novo = Ponto(0, 0, -100);
  Cone* cone = new Cone(60, C->Ct, 20, false, Vetor(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3)), Intensidade (0.8, 0.3, 0.2), Intensidade (0.8, 0.3, 0.2), Intensidade (0.8, 0.3, 0.2), 1);

  // 2) Plano do chão
  Plano* chao = new Plano(Ponto(0, -40, 0), Vetor(0, 1, 0), Intensidade(0, 0, 0), Intensidade(0.2, 0.7, 0.2), Intensidade(0.2, 0.7, 0.2), 1);

  // 3) Plano de Fundo
  Plano* fundo = new Plano(Ponto(0, 0, -200), Vetor(0, 0, 1), Intensidade(0, 0, 0), Intensidade(0.3, 0.3, 0.7), Intensidade(0.3, 0.3, 0.7), 1);

  // 4) Observador
  Observador Obs = Observador(Ponto(0, 0, 0));

  // 5) Fonte Pontual
  LuzPontual Lp = LuzPontual(Ponto(0, 60, -30), Intensidade(0.7, 0.7, 0.7));

  // 6) Luz Ambiente
  LuzAmbiente La = LuzAmbiente(Intensidade(0.3, 0.3, 0.3));

  // 7) Janela
  Janela janela = Janela(0, 0, -30);

  // 8) Cenário em si
  Cenario* cenario = new Cenario();
  cenario->Objetos.push_back(S);
  cenario->Objetos.push_back(C);
  cenario->Objetos.push_back(cone);
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

  cenario->desenhar(renderer, Obs, janela);


  listenEventQuit(window);

  return 0;
}