#include "Lobo.h"



Lobo::Lobo(juegoPG *juego, int px, int py):Enemigo(juego,px,py)
{
	et = TLobo;//Añadir TLobo al array de texturas
	rect.w = ;
	rect.h = ;//Rellenar con el ancho y alto del sprite del lobete
	activo = true;
}


Lobo::~Lobo()
{
}
