#pragma once
#include "ObjetoPG.h"
class Cazador :
	public ObjetoPG
{
public:
	Cazador(juegoPG * juego, int px, int py);
	virtual ~Cazador();
	virtual void draw(); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
};

