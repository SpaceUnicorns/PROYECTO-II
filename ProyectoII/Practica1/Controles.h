#pragma once
#include "EstadoPG.h"
class Controles :
	public EstadoPG
{
public:
	Controles(juegoPG*jug);
	~Controles();

	void onKeyUp(char t);
	void volver();
	virtual void draw();

private:
	SDL_Rect pag, rFondo;
	TexturasSDL * fondo;
	bool gamepad;
};

