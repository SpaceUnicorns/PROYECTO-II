#pragma once
#include "ObjetoPG.h"
class MenuPrincipal :
	public ObjetoPG
{
public:
	MenuPrincipal(juegoPG * juego, int px, int py);
	virtual ~MenuPrincipal();
	virtual void update();
	int opcion;
};

