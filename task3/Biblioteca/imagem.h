#pragma once
#include <SDL2/SDL.h>

//tamanho da imagem 1000
#define TAM 1000
//número de linhas
#define Hj 60
//número de colunas
#define Wj 60
//altura do canvas
#define Hc 500
//largura do canvas
#define Wc 500
//num colunas
#define nCol 500
//num linhas
#define nLin 500
//max para ...
#define MAX 255

//Coisa do SDL de Breno
void initialize(SDL_Window **window, SDL_Renderer **renderer);

//coisa de breno
void listenEventQuit(SDL_Window *window);