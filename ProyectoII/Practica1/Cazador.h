#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Cazador :
	public ObjetoPG
{
public:
	Cazador(juegoPG * juego, int px, int py);
	virtual ~Cazador();
	virtual  SDL_Rect getColisionBox(){ return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
	virtual void draw(); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
};

