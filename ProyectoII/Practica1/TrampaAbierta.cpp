#include "TrampaAbierta.h"


TrampaAbierta::TrampaAbierta(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;
	et = TCColision;
	rect.w = 50;
	rect.h = 30;
	activo = true;
	nombre[0] = "TrampAbierta";
	SDL_Rect colision = { rect.x, rect.y + 10, 50, 10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
	newComponente(new TrampaComponente(this), "TrampaComponente");

}

TrampaAbierta::~TrampaAbierta()
{
}
void TrampaAbierta::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}