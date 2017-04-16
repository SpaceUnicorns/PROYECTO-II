#pragma once
#include "EstadoPG.h"
#include <fstream>
#include <iostream>
#include "Cazador.h"
#include "Recolector.h"
#include "SDL_ttf.h"
#include <string>
#include "GrafoMapa.h"

class Nivel1 :
	public EstadoPG
{
public:
	Nivel1(juegoPG*jug);
	virtual ~Nivel1();
	virtual void draw();
	Cazador* getCazador() { return pCazador; }
	Recolector* getRecolector() { return pRecolector; }
	std::string getActivePlayer() { return activePlayer; }

protected:
	SDL_Rect animNieve1;
	SDL_Rect animNieve2;
	int x, y;
	Cazador* pCazador;
	Recolector *pRecolector;
	std::string activePlayer;
	void swPlayer();	
	void onKeyUp(char k);

	GrafoMapa* mapa;
};

