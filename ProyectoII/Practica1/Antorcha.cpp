#include "Antorcha.h"



Antorcha::Antorcha(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	nombre.push_back("1");
	nombre.push_back("Antorcha");
	receta.push_back("1");
	receta.push_back("Madera");
	receta.push_back("1");
	receta.push_back("Yesca");
	et = TCebo;//CAMBIAAAAAAAAAAAAAAAAAAR
	rect.w = 50;
	rect.h = 30;
	SDL_Rect colision = { rect.x,rect.y + 10,50,10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");

}


Antorcha::~Antorcha()
{
}
void Antorcha::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}

