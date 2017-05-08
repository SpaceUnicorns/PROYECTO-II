#include "RocaGrande.h"



RocaGrande::RocaGrande(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = false;
	et = TObstaculoPiedra;
	rect.w = 200;
	rect.h = 100;
	nombre[0] = "1";
	nombre.push_back("RocaGrande");
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


RocaGrande::~RocaGrande()
{
}

void RocaGrande::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}