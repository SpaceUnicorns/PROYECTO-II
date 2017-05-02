#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Carroña :
	public ObjetoPG
{
public:
	Carroña(juegoPG * juego, int px, int py);
	virtual ~Carroña();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

