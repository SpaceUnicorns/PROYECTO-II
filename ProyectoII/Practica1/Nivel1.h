#pragma once
#include "EstadoPG.h"
#include <fstream>
#include <iostream>
#include "Cazador.h"
#include "SDL_ttf.h"
#include <string>
class Nivel1 :
	public EstadoPG
{
public:
	Nivel1(juegoPG*jug);
	virtual ~Nivel1();
	virtual void draw();

	//void onKeyUp(char k);

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

