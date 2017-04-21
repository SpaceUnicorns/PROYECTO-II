#include "Cazador.h"
#include "MovimientoP.h"
#include "Huella.h"
#include "AntorchaC.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	nombre.push_back( "Zhenia");
	et = TJugador2;
	rect.w = 45;
	rect.h = 55;
	absRect.w = rect.w;
	absRect.h = rect.h;
	newComponente(new MovimientoP(this),"MovimientoP");
	newComponente(new ColisionBox(this), "ColisionBox");
	newComponente(new Huella(this), "Huella");
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
	static_cast<ColisionBox*>(mapaComponentes.at("Huella"))->draw();
	pJuego->getTextura(et)->draw(pJuego->getRender(),anim, rect, alpha);
	static_cast<AntorchaC*>(mapaComponentes.at("AntorchaC"))->draw();
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
