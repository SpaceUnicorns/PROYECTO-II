#include "Madera.h"



Madera::Madera(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;
	et = TMadera;
	rect.w = 50;
	rect.h = 30;
	nombre.push_back("1");
	nombre.push_back( "Madera");
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


Madera::~Madera()
{
}
void Madera::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();

}
