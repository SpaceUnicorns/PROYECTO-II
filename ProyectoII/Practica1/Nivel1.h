#pragma once
#include "EstadoPG.h"
#include <fstream>
#include <iostream>
#include "SDL_ttf.h"
#include <string>
class Nivel1 :
	public EstadoPG
{
public:
	Nivel1(juegoPG*jug);
	//PlayPG(juegoPG*jug, int puntos);
	virtual ~Nivel1();
	virtual void draw();
	/*//m�todos-----------------------------------------------------------------
	int getPuntos(){ return contPuntos; }
	virtual void onClick();
	virtual void update();

	void onKeyUp(char k);
	virtual void newBaja(ObjetoJuego* ob);
	virtual void newPuntos(ObjetoJuego* ob);
	virtual void newPremio(ObjetoJuego* ob);
	virtual void reproduce(ObjetoJuego* ob);*/

private:


	/*int contGlobos, globosTot, pmx, pmy;
	int numPremios;
	bool gameOver,pause;

	//M�todos ------------------------------------------------------------------------------------------------------------------------------------------

	int tipoGlobo();*/
};

