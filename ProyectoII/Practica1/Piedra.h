#pragma once
#include "ObjetoPG.h"
#include "Cazador.h"
class Piedra :
	public ObjetoPG
{
public:
	Piedra(juegoPG * juego, int px, int py);
	virtual ~Piedra();
	virtual void draw(/*Cazador *caz*/); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	virtual  SDL_Rect getColisionBox(){ return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

