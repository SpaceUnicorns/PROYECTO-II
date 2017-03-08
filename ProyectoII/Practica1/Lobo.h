#pragma once
#include "Enemigo.h"
class Lobo :
	public Enemigo
{
public:
	Lobo(juegoPG *juego, int px, int py);
	virtual ~Lobo();
	virtual void draw();
	virtual void setColisionBox(int w, int h) { static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->setDimBox(w, h); }

};

