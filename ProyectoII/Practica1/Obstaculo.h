#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Obstaculo :
	public ObjetoPG
{
public:
	Obstaculo(juegoPG * juego, int px, int py, Texturas_t tex, std:: string destruc);
	virtual ~Obstaculo();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

