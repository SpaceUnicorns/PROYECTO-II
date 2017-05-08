#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Caseta :
	public ObjetoPG
{
public:
	Caseta(juegoPG * juego, int px, int py, int tipo);
	int type;
	virtual ~Caseta();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

