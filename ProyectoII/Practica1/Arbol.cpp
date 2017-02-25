#include "Arbol.h"
#include "ColisionBox.h"
#include "Nivel1.h"
#include <SDL.h>


Arbol::Arbol(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = TArbol;
	rect.w = 100;
	rect.h = 200;
	SDL_Rect aux; aux.x = rect.x + 33; aux.y = rect.y + 175; aux.w = 33; aux.h = 25,
		newComponente(new ColisionBox(this, aux, false), "ColisionBox");
}


Arbol::~Arbol()
{
}
void Arbol::draw(/*Cazador *caz*/){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*int y = caz->getColisionBox().y;
	int x = caz->getColisionBox().x;
	if (y < getColisionBox().y) caz->draw();*/
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
