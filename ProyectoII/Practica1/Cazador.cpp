#include "Cazador.h"
#include "MovimientoP.h"
#include "ColisionBox.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	et = TCazador;
	rect.w = 20;
	rect.h = 70;
	newComponente(new MovimientoP(this),"MovimientoP");
	newComponente(new ColisionBox(this), "ColisionBox");
}


Cazador::~Cazador()
{
}
