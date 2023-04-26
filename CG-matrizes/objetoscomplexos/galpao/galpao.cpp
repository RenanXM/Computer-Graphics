# include"galpao.h"

Galpao::Galpao()
{
  Intensidade r = Intensidade(1, 0, 0);
  Intensidade g = Intensidade(0, 1, 0);
  Intensidade b = Intensidade(0, 0, 1);
  Intensidade amarelo = Intensidade(1, 1, 0);
  Intensidade roxo = Intensidade(0.5, 0, 0.5);
  Intensidade turquesa = Intensidade(0, 0.5, 0.5);

  this->PorticoFrontal = new Portico(amarelo, 1);
  this->PorticoTraseiro = new Portico(amarelo, 1);
  this->TelhadoDir = new Cubo(r, r, r, 1);
  this->TelhadoEsq = new Cubo(r, r, r, 1);
  this->ParedeDir = new Cubo(g, g, g, 1);
  this->ParedeEsq = new Cubo(b, b, b, 1);
  this->ParedeFundo = new Cubo(roxo, roxo, roxo, 1);

  this->Objetos.push_back(PorticoFrontal);
  this->Objetos.push_back(PorticoTraseiro);
  this->Objetos.push_back(TelhadoDir);
  this->Objetos.push_back(TelhadoEsq);
  this->Objetos.push_back(ParedeDir);
  this->Objetos.push_back(ParedeEsq);
  this->Objetos.push_back(ParedeFundo);

  this->inicializar();
}

Galpao::Galpao(string tFrontal, string tTraseiro, string tTelEsq, string tTelDir, string tParEsq, string tParDir, string tParFundo, string tChao, double m)
{
  Intensidade nada = Intensidade(0, 0, 0);
  Portico* porticoFrontal = new Portico(nada, m);
  Portico* porticoTraseiro = new Portico(nada, m);
  Cubo* telhadoDir = new Cubo(nada, nada, nada, m);
  Cubo* telhadoEsq = new Cubo(nada, nada, nada, m);
  Cubo* paredeDir = new Cubo(nada, nada, nada, m);
  Cubo* paredeEsq = new Cubo(nada, nada, nada, m);
  Cubo* paredeFundo = new Cubo(nada, nada, nada, m);
  Cubo* chao = new Cubo(nada, nada, nada, m);

  this->PorticoFrontal = new Textura(porticoFrontal, tFrontal);
  this->PorticoTraseiro = new Textura(porticoTraseiro, tTraseiro);

  this->TelhadoDir = new Textura(telhadoDir, tTelDir);
  this->TelhadoEsq = new Textura(telhadoEsq, tTelEsq);

  this->ParedeEsq = new Textura(paredeEsq, tParEsq);
  this->ParedeDir = new Textura(paredeDir, tParDir);
  this->ParedeFundo = new Textura(paredeFundo, tParFundo);

  this->Chao = new Textura(chao, tChao);


  this->Objetos.push_back(PorticoFrontal);
  this->Objetos.push_back(PorticoTraseiro);
  this->Objetos.push_back(TelhadoDir);
  this->Objetos.push_back(TelhadoEsq);
  this->Objetos.push_back(ParedeDir);
  this->Objetos.push_back(ParedeEsq);
  this->Objetos.push_back(ParedeFundo);
  this->Objetos.push_back(Chao);

  this->inicializar();
}

void Galpao::inicializar()
{
  this->PorticoTraseiro->translacao(0, 0, -1000);

  this->ParedeDir->escala(20, 450, 1000);
  this->ParedeEsq->escala(20, 450, 1000);
  this->ParedeFundo->escala(600, 450, 20);
  this->TelhadoDir->escala(370, 50, 1000);
  this->TelhadoEsq->escala(370, 50, 1000);
  this->Chao->escala(640, 1, 980);

  this->TelhadoDir->rz(-atan(0.75));
  this->TelhadoEsq->rz(atan(0.75));

  this->ParedeEsq->translacao(-320, -300, -1400);
  this->ParedeDir->translacao(300, -300, -1400);
  this->ParedeFundo->translacao(-300, -300, -1400);
  this->Chao->translacao(-320, -323.1, -1380.5);

  this->TelhadoDir->translacao(-2, 368, -1400);
  this->TelhadoEsq->translacao(-296, 148, -1400);
  
  this->translacao(0, 0, 50);  
}