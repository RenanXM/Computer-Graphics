#include "camera.h"

Camera::Camera(){}

Camera::Camera(Observador* obs, double d)
{
  this->obs = obs;
  this->d = d;
  this->janela = new Janela(addPV(obs->P0, Vetor(0, 0, d)));
  this->m = identidade();
  this->exit = false;

  this->tipo_visao = 1;
  Vetor Dr = subP(this->janela->cj, this->obs->P0);
  this->dr_camera = divEscV(Dr, Modulo(Dr));
  //this->inicializar();
}

/*
void Camera::inicializar()
{
  // Inicialização
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  initialize(&window, &renderer);

  // Colocando cor ao Background
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

  // Limpar o Renderer
  SDL_RenderClear(renderer);
}
*/

void Camera::mudarPontoDeVista()
{
  int a;
  cout << "0 -> Fechar programa\n1 -> Translação\n2 -> rx\n3 -> ry\n4 -> rz\n5 -> espxy\n6 -> espxz\n7 -> espyz\n8 -> mudar visão\n";
  cin >> a;
  getchar();
  
  double tx, ty, tz, alfa;
  if (a == 0)
  {
    this->exit = true;
  }

  else if (a == 1)
  {
    cout << "x: ";
    cin >> tx;
    cout << "y: ";
    cin >> ty;
    cout << "z: ";
    cin >> tz;
    this->translacao(tx, ty, tz);
  }

  else if (a == 2 || a == 3 || a == 4)
  {
    cout << "angulo: ";
    cin >> alfa;
    if (a == 2)
    {
      this->rx(alfa);
    }

    if (a == 3)
    {
      this->ry(alfa);
    }

    if (a == 4)
    {
      this->rz(alfa);
    }
  }
  else if (a == 5)
  {
    this->espxy();
  }

  else if (a == 6)
  {
    this->espxz();
  } 

  else if (a == 7)
  {
    this->espyz();
  }

  else if (a == 8)
  {
    cout << "1 - Visão perspectiva\n2 - Ortográfica\n";
    cin >> this->tipo_visao;
  }

  else
  {
    // NADA
  }
}

void Camera::atualizarM(Matriz transformacao)
{
  this->m = prodMM(transformacao, this->m);

  // Atualizando dr_camera
  Ponto cjAtualizado = prodMP(this->m, this->janela->cj);
  Vetor Dr = subP(cjAtualizado, this->obs->P0);
  this->dr_camera = divEscV(Dr, Modulo(Dr));
}

void Camera::translacao(double tx, double ty, double tz)
{
  this->obs->translacao(tx, ty, tz);
  this->atualizarM(Mtranslacao(tx, ty, tz));
}

void Camera::rx(double alfa)
{
  // this->obs->rx(alfa);
  this->atualizarM(this->Correcao(Mrx(alfa)));
}

void Camera::ry(double alfa)
{
  // this->obs->ry(alfa);
  this->atualizarM(this->Correcao(Mry(alfa)));
}

void Camera::rz(double alfa)
{
  // this->obs->rz(alfa);
  this->atualizarM(this->Correcao(Mrz(alfa)));
}

void Camera::espxy()
{
  // this->obs->espxy();
  this->atualizarM(this->Correcao(Mespxy()));
}

void Camera::espxz()
{
  // this->obs->espxz();
  this->atualizarM(this->Correcao(Mespxz()));
}

void Camera::espyz()
{
  // this->obs->espyz();
  this->atualizarM(this->Correcao(Mespyz()));
}


Matriz Camera::Correcao(Matriz transformacaoSemCorrecao)
{
  Ponto P0modificado = prodMP(transformacaoSemCorrecao, this->obs->P0);
  double dx = this->obs->P0.x - P0modificado.x;
  double dy = this->obs->P0.y - P0modificado.y;
  double dz = this->obs->P0.z - P0modificado.z;

  Matriz Translacao = Mtranslacao(dx, dy, dz);
  Matriz Correcao = prodMM(Translacao, transformacaoSemCorrecao);

  return Correcao;
}

/*
        P0                P1    
        |                 |
.       |         .       |
        |                 |

        P1 = M1 * P0
        P2 = M2 * P1
        P3 = M3 * P2 = M3 * M2 * P1 = M3 * M2 * M1 * P0

        M0 = Identidade
        M1 = MT1 * M0
        M2 = MT2 * M1 = MT2 * MT1 * M0
*/