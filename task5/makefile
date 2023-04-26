all: ./main/main

./main/main: ./build/main.o ./build/alglin.o ./build/cenario.o ./build/iluminacao.o ./build/imagem.o ./build/janela.o ./build/objeto.o ./build/observador.o ./build/esfera.o ./build/plano.o ./build/cilindro.o ./build/cone.o ./build/malha.o ./build/aresta.o ./build/face.o ./build/vertice.o ./build/cubo.o ./build/textura.o ./build/texturapixel.o
	g++ ./build/main.o ./build/alglin.o ./build/cenario.o ./build/iluminacao.o ./build/imagem.o ./build/janela.o ./build/objeto.o ./build/observador.o ./build/esfera.o ./build/plano.o ./build/cilindro.o ./build/cone.o ./build/malha.o ./build/aresta.o ./build/face.o ./build/vertice.o ./build/cubo.o ./build/textura.o ./build/texturapixel.o `sdl2-config --cflags --libs` -lSDL2_image -Wall -Wextra -pedantic -o ./main/main

./build/main.o: ./main/main.cpp ./cenario/cenario.h
	g++ -c ./main/main.cpp -o ./build/main.o

./build/alglin.o: ./alglin/*
	g++ -c ./alglin/alglin.cpp -o ./build/alglin.o

./build/cenario.o: ./cenario/*
	g++ -c ./cenario/cenario.cpp -o ./build/cenario.o

./build/iluminacao.o: ./auxiliares/iluminacao/*
	g++ -c ./auxiliares/iluminacao/iluminacao.cpp -o ./build/iluminacao.o

./build/imagem.o: ./auxiliares/imagem/*
	g++ -c ./auxiliares/imagem/imagem.cpp -o ./build/imagem.o

./build/janela.o: ./auxiliares/janela/*
	g++ -c ./auxiliares/janela/janela.cpp -o ./build/janela.o

./build/objeto.o: ./objeto/*
	g++ -c ./objeto/objeto.cpp -o ./build/objeto.o

./build/observador.o: ./auxiliares/observador/*
	g++ -c ./auxiliares/observador/observador.cpp -o ./build/observador.o

./build/esfera.o: ./objetos/esfera/*
	g++ -c ./objetos/esfera/esfera.cpp -o ./build/esfera.o

./build/plano.o: ./objetos/plano/*
	g++ -c ./objetos/plano/plano.cpp -o ./build/plano.o

./build/cilindro.o: ./objetos/cilindro/*
	g++ -c ./objetos/cilindro/cilindro.cpp -o ./build/cilindro.o

./build/cone.o: ./objetos/cone/*
	g++ -c ./objetos/cone/cone.cpp -o ./build/cone.o

./build/malha.o: ./malha/malha.cpp ./malha/malha.h
	g++ -c ./malha/malha.cpp -o ./build/malha.o

./build/aresta.o: ./malha/aresta.cpp ./malha/aresta.h
	g++ -c ./malha/aresta.cpp -o ./build/aresta.o

./build/face.o: ./malha/face.cpp ./malha/face.h
	g++ -c ./malha/face.cpp -o ./build/face.o

./build/vertice.o: ./malha/vertice.cpp ./malha/vertice.h
	g++ -c ./malha/vertice.cpp -o ./build/vertice.o

./build/cubo.o: ./malhas/cubo/*
	g++ -c ./malhas/cubo/cubo.cpp -o ./build/cubo.o

./build/textura.o: ./objetos/textura/*
	g++ -c ./objetos/textura/textura.cpp -o ./build/textura.o

./build/texturapixel.o: ./texturaImagem/*
	g++ -c ./texturaImagem/texturapixel.cpp -o ./build/texturapixel.o