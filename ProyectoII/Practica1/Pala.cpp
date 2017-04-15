#include "Pala.h"



Pala::Pala(juegoPG * juego, int px, int py):ObjetoPG(juego, px, py)
{
	nombre.push_back("1");
	nombre.push_back("Pala");
	receta.push_back("1");
	receta.push_back("Madera");
	receta.push_back("2");
	receta.push_back("Piedra");
	receta.push_back("1");
	receta.push_back("Cuerda");
}


Pala::~Pala()
{
}
