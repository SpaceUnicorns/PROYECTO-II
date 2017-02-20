#pragma once
#include "ObjetoPG.h"
class Arbol :
	public ObjetoPG
{
public:
	Arbol(juegoPG * juego, int px, int py);
	virtual ~Arbol();
	virtual void draw(); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};

