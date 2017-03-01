#include "Cazador.h"
#include "MovimientoP.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	et = TJugador;
	rect.w = 45;
	rect.h = 45;
	newComponente(new MovimientoP(this),"MovimientoP");
	newComponente(new ColisionBox(this), "ColisionBox");
	anim.w = anim.h = 32; //cada frame del jugador mide 32x32
	anim.x = anim.y = 0;
	pintado = false;
	activo = true;
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
