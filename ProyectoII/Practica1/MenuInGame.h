#pragma once
#include "ObjetoPG.h"
class MenuInGame :
	public ObjetoPG
{
public:
	MenuInGame(juegoPG * juego, int px, int py);
	virtual ~MenuInGame();
};

