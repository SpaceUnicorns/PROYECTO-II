#include "Enemigo.h"


Enemigo::Enemigo(juegoPG * juego, Cazador* hunter, Recolector* collector, int px, int py) : ObjetoPG (juego,px,py),cazador(hunter), recolector(collector)
{
	//newComponente(new ColisionBox(this), "ColisionBox");
	objetivo = nullptr;
}


Enemigo::~Enemigo()
{
}

void Enemigo::draw() {
	ObjetoPG::draw();
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	posIni.x -= aux.x;
	posIni.y -= aux.y;
}