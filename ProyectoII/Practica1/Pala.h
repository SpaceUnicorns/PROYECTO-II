#pragma once
#include "ObjetoPG.h"
class Pala :
	public ObjetoPG
{
public:
	Pala(juegoPG * juego, int px, int py);
	virtual ~Pala();
	virtual void draw();
};

