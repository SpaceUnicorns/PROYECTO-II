#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class ObjetoCabania :
	public ObjetoPG
{
public:
	ObjetoCabania(juegoPG * juego, int px, int py);
	virtual ~ObjetoCabania();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

