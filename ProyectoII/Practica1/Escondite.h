#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Escondite :
	public ObjetoPG
{
public:
	Escondite(juegoPG * juego, int px, int py);
	virtual ~Escondite();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
private:
	SDL_Rect anim;
};

