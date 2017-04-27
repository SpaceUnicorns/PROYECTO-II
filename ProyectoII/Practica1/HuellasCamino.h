#pragma once
#include "ObjetoPG.h"
class HuellasCamino :
	public ObjetoPG
{
public:
	HuellasCamino(juegoPG * juego, int px, int py, std:: string s);
	virtual ~HuellasCamino();
	virtual void draw(bool dibuja);
	int cont;
};

