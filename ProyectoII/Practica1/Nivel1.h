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
	void getTorch(){ hasTorch = true; }
	void dropTorch(){hasTorch = false;}
	void setAlpha(int i){ alpha = i; }
	void RemoveFogOfWar(int in_X, int in_Y);

protected:
	SDL_Surface *mFogOfWar, *punch;
	SDL_Texture* pTextMFogOfWar, *pTexPunch;
	SDL_Rect animNieve1, animNieve2, rectZonaOscura;
	bool hasTorch;
	int x, y, alpha;
	Cazador* pCazador;
	Recolector *pRecolector;
	std::string activePlayer;
	void swPlayer();	
	void onKeyUp(char k);
	void DrawSurface(SDL_Texture* in_Text);

	GrafoMapa* mapa;

	/*//métodos-----------------------------------------------------------------
	int getPuntos(){ return contPuntos; }
	virtual void onClick();
	virtual void update();

	virtual void newBaja(ObjetoJuego* ob);
	virtual void newPuntos(ObjetoJuego* ob);
	virtual void newPremio(ObjetoJuego* ob);
	virtual void reproduce(ObjetoJuego* ob);*/
	
	/*int contGlobos, globosTot, pmx, pmy;
	int numPremios;
	bool gameOver,pause;

	//Métodos ------------------------------------------------------------------------------------------------------------------------------------------

	int tipoGlobo();*/
};

