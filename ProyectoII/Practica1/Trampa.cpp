#include "Trampa.h"



Trampa::Trampa(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	nombre.push_back("1");
	nombre.push_back("Trampa");
	receta.push_back("1");
	receta.push_back("TrampaCerrada");
	receta.push_back("1");
	receta.push_back("Cebo");

}


Trampa::~Trampa()
{
}
