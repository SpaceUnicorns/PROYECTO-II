#pragma once
#include "ObjetoPG.h"
class ObjetosOverLayer :
	public ObjetoPG
{
public:

	ObjetosOverLayer(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
	{
	}

	virtual ~ObjetosOverLayer()
	{
	}
};
class CopaArbol : public ObjetosOverLayer
{
public:
	CopaArbol(juegoPG * juego, int px, int py, Texturas_t tx) : ObjetosOverLayer(juego, px, py){
		et = tx;
		rect.h = juego->getTextura(tx)->getH();
		rect.w = juego->getTextura(tx)->getW();
	}
	virtual ~CopaArbol()
	{
	}
};

