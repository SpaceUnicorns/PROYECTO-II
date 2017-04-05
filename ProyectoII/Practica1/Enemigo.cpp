#include "Enemigo.h"


Enemigo::Enemigo(juegoPG * juego, Cazador* hunter, Recolector* collector, int px, int py) : ObjetoPG (juego,px,py),
cazador(hunter), recolector(collector), estado(EstadoEnemigo::Quieto)
{
	activo = true;
	//newComponente(new ColisionBox(this), "ColisionBox");
	posIni.x = px;
	posIni.y = py;
	objetivo = nullptr;
}


Enemigo::~Enemigo()
{
}

void Enemigo::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	posIni.x -= aux.x;
	posIni.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
}