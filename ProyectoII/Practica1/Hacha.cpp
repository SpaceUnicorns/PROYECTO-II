#include "Hacha.h"



Hacha::Hacha(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	nombre[0] = "1";
	nombre.push_back("Hacha");
	receta.push_back("1");
	receta.push_back("Madera");
	receta.push_back("1");
	receta.push_back("Piedra");
	receta.push_back("1");
	receta.push_back("Cuerda");
}


Hacha::~Hacha()
{
}
