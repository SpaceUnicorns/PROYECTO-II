#include "Cuerda.h"



Cuerda::Cuerda(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;
	et = TCuerda;
	rect.w = 50;
	rect.h = 30;
	nombre[0] ="1";
	nombre.push_back( "Cuerda");
	receta.push_back("2");
	receta.push_back("Enredadera");

	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");

}


Cuerda::~Cuerda()
{
}
void Cuerda::draw() {

	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
