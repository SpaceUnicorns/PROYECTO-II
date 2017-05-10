#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"

class Arbol3 :
	public ObjetoPG
{
public:
	Arbol3(juegoPG * juego, int px, int py, int type);
	virtual ~Arbol3();
	virtual void draw(/*Cazador *caz*/); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
private:
	int tipo;
	ColisionBox* pBoxCollider;
};

