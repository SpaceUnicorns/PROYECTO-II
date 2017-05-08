#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"

class Arbol2 :
	public ObjetoPG
{
public:
	Arbol2(juegoPG * juego, int px, int py);
	virtual ~Arbol2();
	virtual void draw(/*Cazador *caz*/); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
private:
	ColisionBox* pBoxCollider;
};

