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
	Boton* cargar;
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
		Punto rec; rec.x = 6905; rec.y = 8930; Punto caz; caz.x = 6970; caz.y = 8930;
		jug->estados.push(new Nivel1(jug, "../docs/mapa1.txt", "../docs/objetos.txt", rec, caz, "R", "../sounds/reverb/ReverbBosque.wav"));
		delete borrar;
	}
	virtual void drawFont(){}
};

