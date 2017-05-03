#include "Cazador.h"
#include "MovimientoP.h"
#include "Huella.h"
#include "AntorchaC.h"
#include "AtaqueCazador.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	velocity.x = 2; velocity.y = 1;
	nombre.push_back( "Zhenia");
	et = TJugador2;
	rect.w = 45;
	rect.h = 80;
	absRect.w = rect.w;
	absRect.h = rect.h;
	newComponente(new ColisionBox(this), "ColisionBox"); //Meter primero este componente
	newComponente(new MovimientoP(this),"MovimientoP");
	newComponente(new AtaqueCazador(this), "AtaqueCazador");
	newComponente(new Huella(this,35,80), "Huella");
	anim.w = 283.5;
	anim.h = 609.5; 

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
