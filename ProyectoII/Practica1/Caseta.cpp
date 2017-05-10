#include "Caseta.h"

Caseta::Caseta(juegoPG * juego, int px, int py, int tipo) : ObjetoPG(juego, px, py)
{
	//Sprite a mostrar
	type = tipo;
	if (type = 0) et = TCabaBoot;
	else if (type = 1) et = TCabaDomo;
	else if (type = 2) et = TCabaBoDo;

	//Inicializaciones Normales
	interactuable = true;
	rect.w = 520;
	rect.h = 400;
	nombre[0] = "1";
	nombre.push_back("Caseta");
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


Caseta::~Caseta()
{
}

void Caseta::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}