#include "Pozo.h"



Pozo::Pozo(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;	//Con cuerda
	et = TPozoA;		//TPozoA = sin cuerda, TPozoB = con Cuerda
	rect.w = 50;
	rect.h = 55;
	nombre[0] = "1";
	nombre.push_back("Pozo");
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


Pozo::~Pozo()
{
}

void Pozo::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}