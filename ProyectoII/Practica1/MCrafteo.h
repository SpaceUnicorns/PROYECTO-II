#pragma once
#include "EstadoPG.h"

class MCrafteo: public EstadoPG
{
public:
	MCrafteo(juegoPG*jug, int puntos);
	virtual ~MCrafteo();

	void draw();
	void update();
	void onKeyUp(char k);

	void animacionS();
	void animacionA();

private:
	SDL_Rect pag1, pag2, sombra, rFondo, niños, recuadros;
	TexturasSDL * fondo;
	int numPag, aux = 0;

	bool derecha, izquierda, flag;
};

