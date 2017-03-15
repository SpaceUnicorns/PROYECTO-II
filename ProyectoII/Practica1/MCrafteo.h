#pragma once
#include "EstadoPG.h"

class MCrafteo: public EstadoPG
{
public:
	MCrafteo(juegoPG*jug, int puntos);
	virtual ~MCrafteo();

	void draw();
	void update();
	SDL_Rect kek = { 0,0,1024,768 };
	void onKeyUp(char k);

private:
	SDL_Rect pag1, pag2, sombra;
	TexturasSDL * fondo;
	int numPag;

	bool derecha, izquierda, flag;
};

