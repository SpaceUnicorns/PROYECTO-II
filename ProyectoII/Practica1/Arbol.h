#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Arbol :
	public ObjetoPG
{
public:
	Arbol(juegoPG * juego, int px, int py, bool fantasma = true);
	virtual ~Arbol();
	virtual void draw(/*Cazador *caz*/); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	virtual  SDL_Rect getColisionBox(){ return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
private:
	int cont;
	bool esFantasma;
	ColisionBox* pBoxCollider;
	virtual void move();
};

