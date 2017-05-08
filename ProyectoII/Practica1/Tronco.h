#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"

class Tronco :
	public ObjetoPG
{
public:
	Tronco(juegoPG * juego, int px, int py);
	virtual ~Tronco();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() {
		return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox();
	}
};

