#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Madera :
	public ObjetoPG
{
public:
	Madera(juegoPG * juego, int px, int py);
	virtual ~Madera();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

