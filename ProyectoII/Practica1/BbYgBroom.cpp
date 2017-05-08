#include "BbYgBroom.h"



BbYgBroom::BbYgBroom(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = false;
	et = TBroom;
	rect.w = 90;
	rect.h = 30;
	nombre[0] = "1";
	nombre.push_back("Cebo");
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


BbYgBroom::~BbYgBroom()
{
}




void BbYgBroom::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}