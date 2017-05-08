#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"

class RocaGrande :
	public ObjetoPG
{
public:
	RocaGrande(juegoPG * juego, int px, int py);
	virtual ~RocaGrande();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

