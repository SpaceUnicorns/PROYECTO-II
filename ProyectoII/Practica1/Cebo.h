#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Cebo :
	public ObjetoPG
{
public:
	Cebo(juegoPG * juego, int px, int py);
	virtual ~Cebo();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

