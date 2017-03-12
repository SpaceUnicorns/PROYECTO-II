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

private:
	SDL_Rect pag1, pag2, sombra;

	int numPag;

	bool derecha, izquierda, flag;
};

