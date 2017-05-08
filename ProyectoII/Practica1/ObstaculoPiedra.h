#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"

class ObstaculoPiedra :
	public ObjetoPG
{
public:
	ObstaculoPiedra(juegoPG * juego, int px, int py, Texturas_t tex, std::string destruc); //TObs2
	virtual ~ObstaculoPiedra();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

