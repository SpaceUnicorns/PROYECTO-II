#include "Cazador.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	et = TCazador;
	rect.w = 20;
	rect.h = 70;
}


Cazador::~Cazador()
{
}
