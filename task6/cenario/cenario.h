#pragma once
#include "../auxiliares/imagem/imagem.h"
#include "../auxiliares/luzes/luzes.h"
#include "../auxiliares/observador/observador.h"
#include "../auxiliares/janela/janela.h"
#include "../objeto/textura.h"
#include "../objetos/esfera/esfera.h"
#include "../objetos/plano/plano.h"
#include "../objetos/cilindro/cilindro.h"
#include "../objetos/cone/cone.h"
#include "../malha/malha.h"
#include "../malhas/cubo/cubo.h"
#include "../texturapixel/texturapixel.h"
#include "../auxiliares/camera/camera.h"
#include "../objetoscomplexos/mesa/mesa.h"
#include "../objetoscomplexos/arvore/arvore.h"

class Cenario{
  public:
    vector<Objeto*> Objetos;
    vector<Luz*> Luzes;

    // Retorna o objeto visto pelo observador. Se o observador não ver nada, retorna alguma coisa (ver essa questão)
    int escolheObj(Ponto P0, Vetor dr, double* ti);
    Cor iluminarFinal(Ponto Pi, Objeto* escolhido, Vetor dr);
    void desenhar(SDL_Renderer *renderer, SDL_Window *window, Camera* camera);
};