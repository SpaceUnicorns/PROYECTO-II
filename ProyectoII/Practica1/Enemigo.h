#pragma once
#include "ObjetoPG.h"
class Enemigo :
	public ObjetoPG
{
public:
	Enemigo(juegoPG *juego, int px, int py);
	~Enemigo();
};

