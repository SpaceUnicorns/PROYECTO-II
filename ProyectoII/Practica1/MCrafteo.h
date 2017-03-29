#pragma once
#include "EstadoPG.h"
#include "Mochila.h"

class MCrafteo: public EstadoPG
{
	struct coords {
		std::string name; int x; int y;
	};
public:
	MCrafteo(juegoPG*jug, int puntos, Mochila* m);
	virtual ~MCrafteo();

	void draw();
	void update() {};
	void onKeyUp(char k);

	void animacionS();
	void animacionA();

	void comprobar(std::vector<coords> const& v);

private:
	SDL_Rect pag1, pag2, sombra, rFondo, niños, recuadros, font;
	TexturasSDL * fondo;
	SDL_Color fuente;
	int numPag, aux = 0;

	bool derecha, izquierda, flag;
	
	Mochila* mochila;
	std::vector<coords> equipables = { //5 elems
		{ "Hacha", 746, 76 },{ "Antorcha", 902, 77 },{ "Pico", 1054, 76 },{ "Pala", 820, 216 },{ "TrampaAbierta", 982, 216 }
	};
	std::vector<coords> materiales = { //8 elems
		{ "Madera", 725, 431 },{ "Piedra", 838, 430 },{ "Hueso", 956, 430 },{ "Cebo", 1071, 430 },
		{ "Enredadera", 725, 545 },{ "Yesca", 838, 545 },{ "Cuerda", 956, 545 },{ "TrampaCerrada", 1072, 547 }
	};
};

