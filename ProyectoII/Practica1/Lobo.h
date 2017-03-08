#pragma once
#include "Enemigo.h"
class Lobo :
	public Enemigo
{
public:
	Lobo(juegoPG *juego, int px, int py);
	virtual ~Lobo();
};

