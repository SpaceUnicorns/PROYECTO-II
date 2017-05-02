#include "Escondite.h"


Escondite::Escondite(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	escondite = true;
	et = TEscondite;
	rect.w = 90;
	rect.h = 100;
	anim.x = anim.y = 0;
	anim.h = 161; anim.w = 180;
	nombre[0] = "1";
	nombre.push_back("Escondite");
	SDL_Rect colision = { rect.x+10, rect.y+10, 65, 80 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


Escondite::~Escondite()
{
}
void Escondite::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(),rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}