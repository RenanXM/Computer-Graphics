#pragma once
#include <SDL2/SDL.h>
#define TAM 1000
#define Hj 60
#define Wj 60
#define Hc 500
#define Wc 500
#define nCol 500
#define nLin 500
#define MAX 255

void initialize(SDL_Window **window, SDL_Renderer **renderer);

void listenEventQuit(SDL_Window *window);