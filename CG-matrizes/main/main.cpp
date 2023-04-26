#include <iostream>
#include "../cenario/cenario.h"

int main()
{
  double alfa = 3.14/8;
  // Esfera
  Esfera* S = new Esfera(5, Ponto(0, 95, -200), Intensidade(0.854, 0.647, 0.125), Intensidade(0.854, 0.647, 0.125), Intensidade(0.854, 0.647, 0.125), 1);

  Esfera* Snow = new Esfera(50, Ponto(0, -100, -200), Intensidade(0.854, 0.647, 0.125), Intensidade(0.854, 0.647, 0.125), Intensidade(0.854, 0.647, 0.125), 1);

  Textura* Snowman = new Textura(Snow, "assets/Neve.jpg");
  Snowman->espXZ();

  // Cilindro
  Cilindro* C = new Cilindro(5, 90, Ponto(0, -150, -200), Vetor(0, 1, 0), false, false, Intensidade(0.824, 0.706, 0.549), Intensidade(0.824, 0.706, 0.549), Intensidade(0.824, 0.706, 0.549), 1);

  Cilindro* cilindroSnow = new Cilindro(50, 90, Ponto(0, -150, -200), Vetor(0, 1, 0), false, true, Intensidade(0.824, 0.706, 0.549), Intensidade(0.824, 0.706, 0.549), Intensidade(0.824, 0.706, 0.549), 1);

  Textura* cilindroNeve = new Textura(cilindroSnow, "assets/Neve.jpg");
  cilindroNeve->escala(1.5);

  // Cone
  Cone* cone = new Cone(50.0, Ponto(0, -60, -200), 50.0, false, Vetor(0, 1, 0), Intensidade (0, 1, 0.498), Intensidade (0, 1, 0.498), Intensidade (0, 1, 0.498), 1);

  Textura* coneNeve = new Textura(cone, "assets/Neve.jpg");
  //cone->rz(3.14/2);
  //cone->rz(3.14/2);
  //coneNeve->ry(3.14/2);
  //coneNeve->espYZ();
  //coneNeve->rx(-3.14/2);
  Textura* coneMadeira = new Textura(cone, "assets/Madeira.jpg");
  // Cubo
  Cubo* cubo = new Cubo(30, Ponto (0, -20, -100), Intensidade(1, 0.078, 0.576), Intensidade(1, 0.078, 0.576), Intensidade(1, 0.078, 0.576), 1);

  Textura* cuboMadeira = new Textura(cubo, "assets/Madeira.jpg");
  //cuboMadeira->translacao(50, 0, 0);
  //cuboMadeira->escala(2, 3, 0.5);
  //cubo->rx(alfa);
  //cubo->ry(alfa);
  //cubo->rz(alfa);
  //cubo->espXY();
  //cubo->espXZ();
  //cubo->espYZ();
  //cubo->cisalhamentoXY(alfa);
  //cubo->cisalhamentoXZ(alfa);
  //cubo->cisalhamentoYX(alfa);
  //cubo->cisalhamentoYZ(alfa);
  //cubo->cisalhamentoZY(alfa);
  //cubo->cisalhamentoZX(alfa);   

  // Plano do chão
  Plano* chao = new Plano(Ponto(0, -350, 0), Vetor(0, 1, 0), Intensidade(0, 0, 0), Intensidade(0.2, 0.7, 0.2), Intensidade(0.2, 0.7, 0.2), 1);
  
  Textura* chaoGrama = new Textura(chao, "assets/Grama.jpg");

  // Plano da Parede Direita
  Plano* dir = new Plano(Ponto(200, -150, 0), Vetor(-1, 0, 0), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), 1);

  // Plano da Parede Frontal
  Plano* frontal = new Plano(Ponto(200, -150, -400), Vetor(0, 0, 1), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), 1);

  // Plano da Parede esquerda
  Plano* esq = new Plano(Ponto(-200, -150, 0), Vetor(1, 0, 0), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), Intensidade(0.686, 0.933, 0.933), 1);

  // Plano do teto
  Plano* teto = new Plano(Ponto(0, 150, 0), Vetor(0, -1, 0), Intensidade(0.933, 0.933, 0.933), Intensidade(0.933, 0.933, 0.933), Intensidade(0.933, 0.933, 0.933), 1);
                    
  // Fonte Pontual
  LuzPontual* Lp = new LuzPontual(Ponto(-100, 140, -20), Intensidade(0.7, 0.7, 0.7));

  // Luz Ambiente
  LuzAmbiente* La = new LuzAmbiente(Intensidade(0.3, 0.3, 0.3));

  LuzSpot* Ls = new LuzSpot(Ponto(0, 0, 10), Intensidade(0.7, 0.7, 0.7), Vetor(0, 0, -1), 3.14/4);

  LuzDirecional* Ld = new LuzDirecional(Intensidade(0.7, 0.7, 0.7), false, Vetor (0, 1, 0));

  // Observador
  Observador* Obs = new Observador(Ponto(0, 0, 0));

  // Janela
  //Janela* janela = new Janela(0, 0, -20);

  // TAREFA 6
  // Objeto Complexo 1: Mesa
  Intensidade imesa = Intensidade(1, 0, 0);
  Intensidade isup1 = Intensidade(0, 1, 0);
  Intensidade isup2 = Intensidade(0, 0, 1);
  Mesa* mesa = new Mesa("assets/MadeiraBranca.jpg", "assets/MadeiraBranca.jpg", "assets/MadeiraBranca.jpg", 1, 1, 1);

  // Objeto Complexo 2: Árvore de Natal
  Intensidade ibola = Intensidade(1, 0, 0);
  Intensidade icone = Intensidade(0, 1, 0);
  Intensidade itronco = Intensidade(0, 0, 1);
  Intensidade isuporte = Intensidade(1, 0, 0);
  Arvore* arvore = new Arvore("assets/Ouro.jpg","assets/Metal.jpg","assets/Folha.jpg","assets/Madeira.jpg", 1, 1, 1, 1);

  // Objeto complexo 3: Galpão
  Galpao* galpao = new Galpao("assets/ParedeGalpao.jpg", "assets/ParedeGalpao.jpg", "assets/Telhado.jpg", "assets/Telhado.jpg", "assets/Tijolo.jpg", "assets/Tijolo.jpg", "assets/Tijolo.jpg", "assets/Madeira.jpg", 1);
  /*
  • Pórtico frontal (instância de pórtico)
  • Pórtico traseiro (instância de pórtico e paralelo ao pórtico frontal),
  • Painel de telhado esquerdo (instância de cubo com escala, rotação e translação)
  • Painel de telhado direito (instância de cubo com escala, rotação e translação)
  • Parede de fechamento esquerda (instância de cubo com escala, rotação e translação)
  • Parede de fechamento direita (instância de cubo com escala, rotação e translação)
  • Parede de fechamento de fundo.
  */

  Cenario* cenario = new Cenario();
  
  /*
  cenario->Objetos.push_back(cubo);
  //cenario->Objetos.push_back(cuboMadeira);

  //cenario->Objetos.push_back(S);
  //cenario->Objetos.push_back(Snowman);

  //cenario->Objetos.push_back(C);
  //cenario->Objetos.push_back(cilindroNeve);

  //cenario->Objetos.push_back(cone);
  //cenario->Objetos.push_back(coneNeve);
  //cenario->Objetos.push_back(coneMadeira);

  //cenario->Objetos.push_back(chao);
  cenario->Objetos.push_back(chaoMadeira);
  cenario->Objetos.push_back(teto);
  cenario->Objetos.push_back(esq);
  cenario->Objetos.push_back(dir);
  cenario->Objetos.push_back(frontal);


  */ 
  LuzPontual* Teste = new LuzPontual(Ponto(0, 0, 0), Intensidade(0.7, 0.7, 0.7));

  mesa->translacao(63.5, -200, -420);
  arvore->translacao(0, -60, -330);
  // CHECKPOINT 1 mesa->translacao(63.5, -70, -220);
  // CHECKPOINT 1 arvore->translacao(0, 10, -130);
  // CHECKPOINT 2 arvore->translacao(0, 20, -140);
  // CHECKPOINT 3 arvore->translacao(0, 30, -150);
  // CHECKPOINT 4 arvore->translacao(0, 50, -90);
  // CHECKPOINT 5 arvore->translacao(0, 45, -80);
  // CHECKPOINT NOVO arvore->translacao(0, -240, -300);

  /*
    CHECKPOINT
    mesa->translacao(63.5, -300, -450);
    arvore->translacao(0, -140, -350);
  */

  // Construção do cenário
  //cenario->Objetos.push_back(mesa);
  //cenario->Objetos.push_back(arvore);
  //cenario->Objetos.push_back(galpao);
  cenario->Objetos.push_back(cuboMadeira);

  //cenario->Objetos.push_back(esq);
  //cenario->Objetos.push_back(dir);
  //cenario->Objetos.push_back(frontal);
  cenario->Objetos.push_back(chaoGrama);
  // cenario->Luzes.push_back(Lp);
  // cenario->Luzes.push_back(Ls);
  // cenario->Luzes.push_back(Ld);
  cenario->Luzes.push_back(La);
  cenario->Luzes.push_back(Teste);

  // Inicialização

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  initialize(&window, &renderer);

  // Colocando cor ao Background
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

  // Limpar o Renderer
  SDL_RenderClear(renderer);
  

  Camera* camera = new Camera(Obs, -20);
  cenario->camera = camera;

  cenario->desenhar(renderer, window);

  encerrar(window);
  // listenEventQuit(window);

  return 0;
}