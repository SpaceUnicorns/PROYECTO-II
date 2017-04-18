#pragma once
#include "ObjetoPG.h"
class Trampa :
	public ObjetoPG
{
public:
	Trampa(juegoPG * juego, int px, int py);
	virtual ~Trampa();
};

