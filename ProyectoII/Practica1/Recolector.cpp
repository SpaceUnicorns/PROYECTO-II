#include "Recolector.h"
#include "MovimientoP.h"
#include "Mochila.h"
#include "Huella.h"
#include "AntorchaC.h"


Recolector::Recolector(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	nombre.push_back( "Liov");
	et = TJugador;
	rect.w = 40;
	rect.h = 70;
	absRect.w = rect.w;
	absRect.h = rect.h;
	newComponente(new ColisionBox(this), "ColisionBox");//Meter primero este componente
	newComponente(new MovimientoP(this), "MovimientoP");
	newComponente(new Mochila(this), "Mochila");
	newComponente(new Huella(this,40,70), "Huella");
	anim.w = 283.5;
	anim.h = 609.5; 
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
	pJuego->getTextura(et)->draw(pJuego->getRender(), anim, rect, alpha);
	static_cast<AntorchaC*>(mapaComponentes.at("AntorchaC"))->draw();
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
