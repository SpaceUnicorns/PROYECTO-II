#include "Enemigo.h"


Enemigo::Enemigo(juegoPG * juego, int px, int py) : ObjetoPG (juego,px,py)
{
	newComponente(new ColisionBox(this), "ColisionBox");
}


Enemigo::~Enemigo()
{
}