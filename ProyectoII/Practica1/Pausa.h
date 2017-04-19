#pragma once
#include "EstadoPG.h"
#include "Recolector.h"

class Pausa :
	public EstadoPG
{
	enum estadosPausa { Resume, Menu, Opciones };

public:
	Pausa(juegoPG*jug,Recolector* pRec, int puntos);
	virtual ~Pausa();

	/*static void goMenu(juegoPG *jug){ 
		EstadoJuego* borrar = jug->estados.top();
		jug->estados.pop(); jug->estados.push(new MenuPG(jug,0));
		delete borrar;
	}
	static void setResume(juegoPG *jug){ 
		EstadoJuego* borrar = jug->estados.top();
		jug->estados.pop();
		delete borrar;
	}*/

	void draw();
	void update();

private:
	TexturasSDL * fondo;
	SDL_Rect rFondo, rect, boton;
	Recolector* pRecolector;
	
	int temp;
	int aux;
	estadosPausa estado;
};

