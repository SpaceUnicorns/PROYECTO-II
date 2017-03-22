#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Hueso :
	public ObjetoPG
{
public:
	Hueso(juegoPG * juego, int px, int py);
	virtual ~Hueso();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

