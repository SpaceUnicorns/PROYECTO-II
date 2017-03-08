#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Enemigo :
	public ObjetoPG
{
public:
	Enemigo(juegoPG *juego, int px, int py);
	~Enemigo();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
protected:
	int damage;
	int life;
};

