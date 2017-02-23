#pragma once
#include "ObjetoPG.h"
#include "Cazador.h"
class Arbol :
	public ObjetoPG
{
public:
	Arbol(juegoPG * juego, int px, int py);
	virtual ~Arbol();
	virtual void draw(/*Cazador *caz*/); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	virtual  SDL_Rect getColisionBox(){ return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

