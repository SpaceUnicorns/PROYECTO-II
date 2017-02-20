#include "Arbol.h"


Arbol::Arbol(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = TArbol;
	rect.w = 100;
	rect.h = 200;
}


Arbol::~Arbol()
{
}
