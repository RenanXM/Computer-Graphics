#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "alglin.h"
#include "iluminacao.h"
#include "imagem.h"
#include "objeto.h"
#include "observador.h"
using std::vector;

//MUITO IMPORTANTE!!!!
class Cenario{
  public:
    //entendido : Atributos

    //Vetor dinâmico para objetos(esfera,cilindro, etc)
    vector<Objeto*> Objetos;
    //Vetor dinâmico para todas as luzes do cenário.
    vector<LuzPontual*> Luzes;
    //Cada Cenário tem uma luz ambiente definida.
    LuzAmbiente* LA;

    // Retorna o objeto visto pelo observador. Se o observador não ver nada,
    // retorna alguma coisa (ver essa questão)
    int escolheObj(Ponto* P0, Vetor* dr);

    //
    Cor* iluminarFinal(Ponto* Pi, Objeto* escolhido, Vetor* dr);


    void desenhar(SDL_Renderer *renderer, Observador* Obs, float d);

    //função que veririca se um determinado objeto é iluminado.
    bool intersecLuz(Objeto* Obj, Cenario* cenario, Ponto* Pi, LuzPontual* Lp);

    //retorna a soma da difusa + especular.
    Intensidade* iluminarIndiv(Objeto* obj, Ponto* Pi, Cenario* cenario, Vetor* dr, LuzPontual* Lp);
};