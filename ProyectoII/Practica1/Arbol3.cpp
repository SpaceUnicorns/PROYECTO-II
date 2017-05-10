#include "Arbol3.h"
#include "ColisionBox.h"
#include "Nivel1.h"
#include <SDL.h>


Arbol3::Arbol3(juegoPG * juego, int px, int py, int type) : ObjetoPG(juego, px, py)
{
	tipo = type;
	if (tipo == 0) {
		et = TArbol3A;			//Con Enredaderas
		interactuable = true;	//De este arbol se recogen enredaderas
	}
	else if (tipo == 1) {
		et = TArbol3B;			//Sin Enredaderas
		interactuable = false;	
	}
	nombre.push_back("1");
	nombre.push_back("Arbol3");

	
	rect.w = 100;
	rect.h = 200;
	absRect.w = rect.w;
	absRect.h = rect.h;
	SDL_Rect aux; aux.x = rect.x + 20; aux.y = rect.y + 180; aux.w = 60; aux.h = 20,
		newComponente(new ColisionBox(this, aux, false), "ColisionBox");
	pBoxCollider = static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"));
}


Arbol3::~Arbol3()
{

}

void Arbol3::draw() { //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	pBoxCollider->draw();

}