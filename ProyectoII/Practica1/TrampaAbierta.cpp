#include "TrampaAbierta.h"


TrampaAbierta::TrampaAbierta(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;
	et = TTrampaAbierta;
	rect.w = 40;
	rect.h = 40;
	activo = true;
	nombre[0] = "1";
	nombre.push_back("Trampa");
	SDL_Rect colision = { rect.x-15, rect.y-5, 60, 60 };
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