#include "Valla.h"

Valla::Valla(juegoPG * juego, int px, int py, std:: string dir) : ObjetoPG(juego, px, py)
{
	et = TValla;
	rect.w = 250;
	rect.h = 150;
	nombre[0] = "1";
	nombre.push_back("Vaya");
	if (dir == "A")anim.x = 0;
	else anim.x = 188;
	anim.y = 0;
	anim.h = 128; anim.w = 188;
	SDL_Rect colision = { rect.x, rect.y + 10, 800, 150 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}

Valla::~Valla() {}

void Valla::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), anim, rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}