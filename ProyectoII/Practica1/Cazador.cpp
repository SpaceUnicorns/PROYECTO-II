#include "Cazador.h"
#include "MovimientoP.h"
#include "ColisionBox.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	et = TJugador;
	rect.w = 45;
	rect.h = 45;
	newComponente(new MovimientoP(this),"MovimientoP");
	newComponente(new ColisionBox(this), "ColisionBox");
	anim.w = anim.h = 32; //cada frame del jugador mide 32x32
	anim.x = anim.y = 0;
}


Cazador::~Cazador()
{
}
void Cazador::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pJuego->getTextura(et)->draw(pJuego->getRender(),anim, rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
