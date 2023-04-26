all: main

main: main.o alglin.o cenario.o iluminacao.o imagem.o objeto.o observador.o
	g++ main.o alglin.o cenario.o iluminacao.o imagem.o objeto.o observador.o `sdl2-config --cflags --libs` -o main

main.o: main.cpp alglin.h cenario.h iluminacao.h imagem.h objeto.h observador.h
	g++ -c main.cpp -o main.o

alglin.o: alglin.cpp alglin.h
	g++ -c alglin.cpp -o alglin.o

cenario.o: cenario.cpp alglin.h cenario.h iluminacao.h imagem.h objeto.h observador.h
	g++ -c cenario.cpp -o cenario.o

iluminacao.o: iluminacao.cpp alglin.h iluminacao.h
	g++ -c iluminacao.cpp -o iluminacao.o

imagem.o: imagem.cpp imagem.h
	g++ -c imagem.cpp -o imagem.o

objeto.o: objeto.cpp alglin.h iluminacao.h objeto.h
	g++ -c objeto.cpp -o objeto.o

observador.o: observador.cpp observador.h alglin.h
	g++ -c observador.cpp -o observador.o

clean:
	rm main *.o