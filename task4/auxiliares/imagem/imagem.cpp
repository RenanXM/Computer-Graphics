#include "imagem.h"

void initialize(SDL_Window **window, SDL_Renderer **renderer)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(Wc, Hc, 0, window, renderer);
}

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