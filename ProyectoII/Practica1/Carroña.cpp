#include "Carroña.h"


Carroña::Carroña(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = TCarroña;
	rect.w = 100;
	rect.h = 70;
	interactuable = true;
	desaparece = true;
	nombre[0] = "1";
	nombre.push_back("Hueso");
	nombre.push_back("1");
	nombre.push_back("Cebo");
	SDL_Rect colision = { rect.x, rect.y+5, 100, 70 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}

Carroña::~Carroña()
{
}
void Carroña::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
