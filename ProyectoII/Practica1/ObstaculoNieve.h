#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"

class ObstaculoNieve :
	public ObjetoPG
{
public:
	ObstaculoNieve(juegoPG * juego, int px, int py, Texturas_t tex, std::string destruc); //TObs1
	virtual ~ObstaculoNieve();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

