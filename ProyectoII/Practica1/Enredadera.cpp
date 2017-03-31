#include "Enredadera.h"



Enredadera::Enredadera(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;
	et = TEnredadera;
	rect.w = 50;
	rect.h = 30;
	nombre.push_back("2");
	nombre.push_back( "Enredadera");
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


Enredadera::~Enredadera()
{

}
void Enredadera::draw() { 
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
