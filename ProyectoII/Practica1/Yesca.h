#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Yesca :
	public ObjetoPG
{
public:
	Yesca(juegoPG * juego, int px, int py);
	virtual ~Yesca();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

