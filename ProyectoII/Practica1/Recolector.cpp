#include "Recolector.h"
#include "MovimientoP.h"
#include "Mochila.h"
#include "Huella.h"


Recolector::Recolector(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	nombre.push_back( "Liov");
	et = TJugador;
	rect.w = 45;
	rect.h = 45;
	absRect.w = rect.w;
	absRect.h = rect.h;
	newComponente(new MovimientoP(this), "MovimientoP");
	newComponente(new ColisionBox(this), "ColisionBox");
	newComponente(new Mochila(this), "Mochila");
	newComponente(new Huella(this), "Huella");
	anim.w = anim.h = 32; //cada frame del jugador mide 32x32
	anim.x = anim.y = 0;
	pintado = false;
	activo = false;
}


Recolector::~Recolector()
{

}
void Recolector::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (!activo) {
		aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
		rect.x -= aux.x;
		rect.y -= aux.y;
	}
	static_cast<ColisionBox*>(mapaComponentes.at("Huella"))->draw();
	pJuego->getTextura(et)->draw(pJuego->getRender(), anim, rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
