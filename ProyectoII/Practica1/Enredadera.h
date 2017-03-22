#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Enredadera: public ObjetoPG
{
public:
	Enredadera(juegoPG * juego, int px, int py);
	virtual ~Enredadera();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

