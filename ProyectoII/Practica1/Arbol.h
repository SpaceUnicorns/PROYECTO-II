#pragma once
#include "ObjetoPG.h"
class Arbol :
	public ObjetoPG
{
public:
	Arbol(juegoPG * juego, int px, int py);
	virtual ~Arbol();
};

