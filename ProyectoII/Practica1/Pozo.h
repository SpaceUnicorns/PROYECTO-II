#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"

class Pozo :
	public ObjetoPG
{
public:
	Pozo(juegoPG * juego, int px, int py, int type);
	int tipo;
	virtual ~Pozo();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

