#include "Obstaculo.h"


Obstaculo::Obstaculo(juegoPG * juego, int px, int py, Texturas_t tex, std:: string destruc) : ObjetoPG(juego, px, py)
{
	obstaculo = true;
	et = tex;
	rect.w = 200;
	rect.h = 100;
	nombre[0] = "1";
	if (tex == TObstaculoPiedra) nombre.push_back("ObsPiedra");
	else nombre.push_back("ObsNieve");
	destructor = destruc;
	SDL_Rect colision = { rect.x, rect.y + rect.h / 2, rect.w, rect.h / 2 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


Obstaculo::~Obstaculo()
{
}

void Obstaculo::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect, alpha);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}