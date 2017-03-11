#pragma once
#include "EstadoPG.h"
#include "Boton.h"
#include "Nivel1.h"
#include "MenuPrincipal.h"
class MenuPG :
	public EstadoPG
{
protected:
	Boton* play;
	Boton* exit;
public:
	MenuPG(juegoPG*jug, int puntos);
	virtual ~MenuPG();

	//Funciones---------------------------------------------------------------------------------------------------------------
	static void salir(juegoPG *jug){
		EstadoJuego* borrar = jug->estados.top();
		jug->estados.pop();
		delete borrar;
		jug->setSalir();
	}
	static void jugar(juegoPG*jug){
		EstadoJuego* borrar = jug->estados.top();
		jug->estados.pop();
		jug->estados.push(new Nivel1(jug));
		delete borrar;
	}
	virtual void drawFont(){}
};

