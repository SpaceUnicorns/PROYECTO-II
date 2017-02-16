#pragma once
#include "EstadoPG.h"
#include "Boton.h"
#include "MenuPG.h"
class Pausa :
	public EstadoPG
{
protected:
	Boton * menu;
	Boton * resume;
public:
	Pausa(juegoPG*jug, int puntos);
	virtual ~Pausa();
	//Funciones-----------------------------------------------------------------------------------------------------------
	static void goMenu(juegoPG *jug){ 
		EstadoJuego* borrar = jug->estados.top();
		jug->estados.pop(); jug->estados.push(new MenuPG(jug,0));
		delete borrar;
	}
	static void setResume(juegoPG *jug){ 
		EstadoJuego* borrar = jug->estados.top();
		jug->estados.pop();
		delete borrar;
	}
};

