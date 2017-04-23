#include "Pico.h"



Pico::Pico(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	nombre[0] = "1";
	nombre.push_back("Pico");
	receta.push_back("1");
	receta.push_back("Madera");
	receta.push_back("1");
	receta.push_back("Hueso");
	receta.push_back("1");
	receta.push_back("Cuerda");

}


Pico::~Pico()
{
}
