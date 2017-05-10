#pragma once
#include "ObjetoPG.h"
class Hacha :
	public ObjetoPG
{
public:
	Hacha(juegoPG * juego, int px, int py);
	virtual ~Hacha();
	virtual void draw();
};

