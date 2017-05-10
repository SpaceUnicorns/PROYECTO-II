#include "ObstaculoPiedra.h"



ObstaculoPiedra::ObstaculoPiedra(juegoPG * juego, int px, int py, Texturas_t tex, std::string destruc) : ObjetoPG(juego, px, py)
{
	// OJO PROBABLEMENTE CLASE INNECESARIA, LLAMADOS Y CREADOS USANDO CLASE OBSTACULO
	obstaculo = true;
	et = tex;		//TObs2
	rect.w = 200;
	rect.h = 100;
	nombre[0] = "1";
	nombre.push_back("ObstaculoPiedra");
	destructor = destruc;
	SDL_Rect colision = { rect.x, rect.y + rect.h / 2, rect.w, rect.h / 2 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");
}


ObstaculoPiedra::~ObstaculoPiedra()
{
}

void ObstaculoPiedra::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect, alpha);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}