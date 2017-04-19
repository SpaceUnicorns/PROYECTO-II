#pragma once
#include "ObjetoPG.h"
class CabañaObj :
	public ObjetoPG
{
public:
	CabañaObj(juegoPG * juego, int px, int py);
	~CabañaObj();

	virtual void update();
	virtual void draw(); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	bool compruebaRadio(SDL_Rect target);
	bool cazadorIn();
	bool recolectorIn();

private:
	bool saved;
};

