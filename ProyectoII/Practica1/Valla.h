#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Valla :
	public ObjetoPG
{
public:
	Valla(juegoPG * juego, int px, int py, std::string dir);
	virtual ~Valla();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

