#pragma once
#include "../auxiliares/imagem/imagem.h"
#include "../auxiliares/observador/observador.h"
#include "../auxiliares/janela/janela.h"
#include "../objetos/esfera/esfera.h"
#include "../objetos/plano/plano.h"
#include "../objetos/cilindro/cilindro.h"
#include "../objetos/cone/cone.h"
#include "../objetos/textura/textura.h"
#include "../malha/malha.h"
#include "../malhas/cubo/cubo.h"
#include "../texturaImagem/texturapixel.h"
#include <vector>
using std::vector;

class Cenario{
  public:
    vector<Objeto*> Objetos;
    vector<LuzPontual> Luzes;
    LuzAmbiente LA;

    // Retorna o objeto visto pelo observador. Se o observador não ver nada, retorna alguma coisa (ver essa questão)
    int escolheObj(Ponto P0, Vetor dr, double* ti);
    Cor iluminarFinal(Ponto Pi, Objeto* escolhido, Vetor dr);
    void desenhar(SDL_Renderer *renderer, Observador Obs, Janela janela);
    bool intersecLuz(Objeto* Obj, Ponto Pi, LuzPontual Lp);
    Intensidade iluminarIndiv(Objeto* obj, Ponto Pi, Vetor dr, LuzPontual Lp);
};