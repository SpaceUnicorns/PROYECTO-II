#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class TrampaCerrada :
	public ObjetoPG
{
public:
	TrampaCerrada(juegoPG * juego, int px, int py);
	virtual ~TrampaCerrada();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

