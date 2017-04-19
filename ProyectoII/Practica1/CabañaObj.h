#pragma once
#include "ObjetoPG.h"
class CabañaObj :
	public ObjetoPG
{
public:
	CabañaObj(juegoPG * juego, int px, int py);
	~CabañaObj();

	virtual void update();
	bool compruebaRadio(SDL_Rect target);
	bool cazadorIn();
	bool recolectorIn();



private:
	bool saved;
};

