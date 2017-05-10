#pragma once
#include "ObjetoPG.h"
class Pico :
	public ObjetoPG
{
public:
	Pico(juegoPG * juego, int px, int py);
	virtual ~Pico();
	virtual void draw();
};

