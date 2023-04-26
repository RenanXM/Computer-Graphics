#include <iostream>
#include "../cenario/cenario.h"

int main()
{
  // Esfera
  Esfera* S = new Esfera(5, Ponto(0, 95, -200), Intensidade(0.854, 0.647, 0.125), Intensidade(0.854, 0.647, 0.125), Intensidade(0.854, 0.647, 0.125), 1);

  // Cilindro
  Cilindro* C = new Cilindro(5, 90, Ponto(0, -150, -200), Vetor(0, 1, 0), false, false, Intensidade(0.824, 0.706, 0.549), Intensidade(0.824, 0.706, 0.549), Intensidade(0.824, 0.706, 0.549), 1);
  
  // Cone
  Cone* cone = new Cone(90.0, Ponto(0, -60, -200), 150.0, false, Vetor(0, 1, 0), Intensidade (0, 1, 0.498), Intensidade (0, 1, 0.498), Intensidade (0, 1, 0.498), 1);

  // Cubo
  Cubo* cubo = new Cubo(40, Ponto (0, -150, -165), Intensidade(1, 0.078, 0.576), Intensidade(1, 0.078, 0.576), Intensidade(1, 0.078, 0.576), 1);


   // Plano do chão (receberá textura)
  Plano* chao = new Plano(Ponto(0, -150, 0), Vetor(0, 1, 0), Intensidade(0, 0, 0), Intensidade(0.2, 0.7, 0.2), Intensidade(0.2, 0.7, 0.2), 1);

  // PLano da Parede Direita
  Plano* dir = new Plano(Ponto(200, -150, 0), Vetor(-1, 0, 0), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), 1);

  Plano* frontal = new Plano(Ponto(200, -150, -400), Vetor(0, 0, 1), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), 1);

  // Plano da Parede esquerda
  Plano* esq = new Plano(Ponto(-200, -150,0), Vetor(1, 0, 0), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), 1);

  // Plano do teto
  Plano* teto = new Plano(Ponto(0, 150, 0), Vetor(0, -1, 0), Intensidade(0.933, 0.933, 0.933), Intensidade(0.933, 0.933, 0.933), Intensidade(0.933, 0.933, 0.933), 1);

  Textura* madeira = new Textura(chao, "assets/Breno.jpg");  // TEXTURA

  // Fonte Pontual
  LuzPontual Lp = LuzPontual(Ponto(-100, 140, -20), Intensidade(0.7, 0.7, 0.7));

  // Luz Ambiente
  LuzAmbiente La = LuzAmbiente(Intensidade(0.3, 0.3, 0.3));

  // Observador
  Observador Obs = Observador(Ponto(0, 0, 0));

  // Janela
  Janela janela = Janela(0, 0, -20);

  // Construção do cenário
  Cenario* cenario = new Cenario();
  cenario->Objetos.push_back(cubo);
  cenario->Objetos.push_back(S);
  cenario->Objetos.push_back(C);
  cenario->Objetos.push_back(cone);
  cenario->Objetos.push_back(madeira);
  cenario->Objetos.push_back(teto);
  cenario->Objetos.push_back(esq);
  cenario->Objetos.push_back(dir);
  cenario->Objetos.push_back(frontal);

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