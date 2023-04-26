#pragma once
#include "../observador/observador.h"
#include "../janela/janela.h"
#include "../imagem/imagem.h"

class Camera
{
public:
  Observador* obs;
  Janela* janela;
  double d;
  bool exit;
  Matriz m;
  //SDL_Window *window;
  //SDL_Renderer *renderer;
  Camera();
  Camera(Observador* obs, double d);

  //void inicializar();
  void mudarPontoDeVista();
  void translacao(double tx, double ty, double tz);
  void rx(double alfa);
  void ry(double alfa);
  void rz(double alfa);
  void espxy();
  void espxz();
  void espyz();
  
  void atualizarM(Matriz transformacao);
};