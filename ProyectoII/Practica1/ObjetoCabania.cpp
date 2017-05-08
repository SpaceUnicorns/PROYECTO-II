#include "ObjetoCabania.h"


ObjetoCabania::ObjetoCabania(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = TCabania;
	rect.w = 324;
	rect.h = 336;
	nombre[0] = "1";
	nombre.push_back("Cabania");
	SDL_Rect colision = { rect.x+20, rect.y + 230, 290, 40 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}

void ObjetoCabania::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
ObjetoCabania::~ObjetoCabania()
{
}
