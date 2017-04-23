#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Antorcha :
	public ObjetoPG
{
public:
	Antorcha(juegoPG * juego, int px, int py);
	virtual ~Antorcha();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

