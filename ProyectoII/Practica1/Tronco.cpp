#include "Tronco.h"

Tronco::Tronco(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = false;
	et = TTronco;
	rect.w = 180;
	rect.h = 90;
	nombre[0] = "1";
	nombre.push_back("Tronco");
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


Tronco::~Tronco()
{
}


void Tronco::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}