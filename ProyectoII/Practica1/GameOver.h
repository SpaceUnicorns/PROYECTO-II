#pragma once
#include "EstadoPG.h"
#include "Boton.h"
#include "MenuPG.h"
class GameOver :
	public EstadoPG
{
protected:
	Boton* menu;
public:
	GameOver(juegoPG*jug, int puntos);
	virtual ~GameOver();

	//Funciones --------------------------------------------------------------
	static void goMenu(juegoPG *jug){
		EstadoJuego* borrar = jug->estados.top();
		jug->estados.pop();
		jug->estados.push(new MenuPG(jug,0));
		delete borrar;
	}

};

