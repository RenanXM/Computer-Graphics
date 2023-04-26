all: ./main/main

./main/main: ./build/main.o ./build/alglin.o ./build/cenario.o ./build/iluminacao.o ./build/imagem.o ./build/janela.o ./build/objeto.o ./build/observador.o ./build/esfera.o ./build/plano.o ./build/cilindro.o ./build/cone.o ./build/malha.o ./build/aresta.o ./build/face.o ./build/vertice.o ./build/cubo.o ./build/textura.o ./build/texturapixel.o ./build/luzes.o ./build/camera.o ./build/complexos.o ./build/mesa.o ./build/arvore.o ./build/portico.o ./build/galpao.o
	g++ ./build/main.o ./build/alglin.o ./build/cenario.o ./build/iluminacao.o ./build/imagem.o ./build/janela.o ./build/objeto.o ./build/observador.o ./build/esfera.o ./build/plano.o ./build/cilindro.o ./build/cone.o ./build/malha.o ./build/aresta.o ./build/face.o ./build/vertice.o ./build/cubo.o ./build/textura.o ./build/texturapixel.o ./build/luzes.o ./build/camera.o ./build/complexos.o ./build/mesa.o ./build/arvore.o ./build/portico.o ./build/galpao.o `sdl2-config --cflags --libs` -lSDL2_image -Wall -Wextra -pedantic -o ./main/main

./build/main.o: ./main/main.cpp ./cenario/cenario.h
	g++ -c ./main/main.cpp -o ./build/main.o

./build/alglin.o: ./alglin/alglin.cpp ./alglin/alglin.h
	g++ -c ./alglin/alglin.cpp -o ./build/alglin.o

./build/cenario.o: ./cenario/cenario.cpp ./cenario/cenario.h
	g++ -c ./cenario/cenario.cpp -o ./build/cenario.o

./build/iluminacao.o: ./auxiliares/iluminacao/iluminacao.cpp ./auxiliares/iluminacao/iluminacao.h
	g++ -c ./auxiliares/iluminacao/iluminacao.cpp -o ./build/iluminacao.o

./build/imagem.o: ./auxiliares/imagem/imagem.cpp ./auxiliares/imagem/imagem.h
	g++ -c ./auxiliares/imagem/imagem.cpp -o ./build/imagem.o

./build/janela.o: ./auxiliares/janela/janela.cpp ./auxiliares/janela/janela.h
	g++ -c ./auxiliares/janela/janela.cpp -o ./build/janela.o

./build/objeto.o: ./objeto/objeto.cpp ./objeto/objeto.h
	g++ -c ./objeto/objeto.cpp -o ./build/objeto.o

./build/observador.o: ./auxiliares/observador/observador.cpp ./auxiliares/observador/observador.h
	g++ -c ./auxiliares/observador/observador.cpp -o ./build/observador.o

./build/esfera.o: ./objetos/esfera/esfera.cpp ./objetos/esfera/esfera.h
	g++ -c ./objetos/esfera/esfera.cpp -o ./build/esfera.o

./build/plano.o: ./objetos/plano/plano.cpp ./objetos/plano/plano.h
	g++ -c ./objetos/plano/plano.cpp -o ./build/plano.o

./build/cilindro.o: ./objetos/cilindro/cilindro.cpp ./objetos/cilindro/cilindro.h
	g++ -c ./objetos/cilindro/cilindro.cpp -o ./build/cilindro.o

./build/cone.o: ./objetos/cone/cone.cpp ./objetos/cone/cone.h
	g++ -c ./objetos/cone/cone.cpp -o ./build/cone.o

./build/malha.o: ./malha/malha.cpp ./malha/malha.h
	g++ -c ./malha/malha.cpp -o ./build/malha.o

./build/aresta.o: ./malha/aresta.cpp ./malha/aresta.h
	g++ -c ./malha/aresta.cpp -o ./build/aresta.o

./build/face.o: ./malha/face.cpp ./malha/face.h
	g++ -c ./malha/face.cpp -o ./build/face.o

./build/vertice.o: ./malha/vertice.cpp ./malha/vertice.h
	g++ -c ./malha/vertice.cpp -o ./build/vertice.o

./build/cubo.o: ./malhas/cubo/cubo.cpp ./malhas/cubo/cubo.h
	g++ -c ./malhas/cubo/cubo.cpp -o ./build/cubo.o

./build/textura.o: ./objeto/textura.cpp ./objeto/textura.h
	g++ -c ./objeto/textura.cpp -o ./build/textura.o

./build/texturapixel.o: ./texturapixel/texturapixel.cpp ./texturapixel/texturapixel.h
	g++ -c ./texturapixel/texturapixel.cpp -o ./build/texturapixel.o

./build/luzes.o: ./auxiliares/luzes/luzes.cpp ./auxiliares/luzes/luzes.h
	g++ -c ./auxiliares/luzes/luzes.cpp -o ./build/luzes.o

./build/camera.o: ./auxiliares/camera/camera.cpp ./auxiliares/camera/camera.h
	g++ -c ./auxiliares/camera/camera.cpp -o ./build/camera.o

./build/complexos.o: ./objetoscomplexos/complexos/complexos.cpp ./objetoscomplexos/complexos/complexos.h
	g++ -c ./objetoscomplexos/complexos/complexos.cpp -o ./build/complexos.o

./build/mesa.o: ./objetoscomplexos/mesa/mesa.cpp ./objetoscomplexos/mesa/mesa.h
	g++ -c ./objetoscomplexos/mesa/mesa.cpp -o ./build/mesa.o

./build/arvore.o: ./objetoscomplexos/arvore/arvore.cpp ./objetoscomplexos/arvore/arvore.h
	g++ -c ./objetoscomplexos/arvore/arvore.cpp -o ./build/arvore.o

./build/portico.o: ./objetoscomplexos/portico/portico.cpp ./objetoscomplexos/portico/portico.h
	g++ -c ./objetoscomplexos/portico/portico.cpp -o ./build/portico.o

./build/galpao.o: ./objetoscomplexos/galpao/galpao.cpp ./objetoscomplexos/galpao/galpao.h
	g++ -c ./objetoscomplexos/galpao/galpao.cpp -o ./build/galpao.o