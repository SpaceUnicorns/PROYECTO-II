#include "Cazador.h"
#include "MovimientoP.h"
#include "AtaqueZ.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	nombre = "Zhenia";
	et = TJugador2;
	rect.w = 45;
	rect.h = 55;
	absRect.w = rect.w;
	absRect.h = rect.h;
	newComponente(new MovimientoP(this),"MovimientoP");
	newComponente(new ColisionBox(this), "ColisionBox");
	newComponente(new AtaqueZ(this, juego, rect.x, rect.y), "AttackBox");
	anim.w = anim.h = 32; //cada frame del jugador mide 32x32
	anim.x = anim.y = 0;
	pintado = false;
	activo = true;
	equipo = "Trampa";
}


Cazador::~Cazador()
{

}

void Cazador::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pintado = true;
	if (!activo) {
		aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
		rect.x -= aux.x;
		rect.y -= aux.y;
	}
	pJuego->getTextura(et)->draw(pJuego->getRender(),anim, rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
