#pragma once
#include "Trigger.h"
class ChangeTerreno :
	public Trigger
{
public:
	ChangeTerreno(juegoPG * juego, int px, int py, Cazador* tgC, Recolector* tgR, int terreno, int indice_ = 0);
	virtual void update();
	virtual ~ChangeTerreno();
private:
	int terreno;
};

