#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Cuerda :
	public ObjetoPG
{
public:
	Cuerda(juegoPG * juego, int px, int py);
	virtual ~Cuerda();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

