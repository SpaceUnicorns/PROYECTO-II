#pragma once
#include "EstadoPG.h"
#include "Recolector.h"
#include "Nivel1.h"

class Pausa :
	public EstadoPG
{
	enum estadosPausa { Resume, Menu, Opciones, Control };

public:
	Pausa(juegoPG*jug,Nivel1* pRec, int puntos);
	virtual ~Pausa();
	virtual void onKeyUp(char k);
	virtual void draw();
	virtual void update();

private:
	bool arriba, abajo, enter;
	TexturasSDL * fondo;
	SDL_Rect rFondo, rect, boton;
	Nivel1* level;
	
	int temp;
	int aux;
	estadosPausa estado;
};

