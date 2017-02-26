#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Recolector :
	public ObjetoPG
{
public:
	Recolector(juegoPG * juego, int px, int py);
	virtual ~Recolector();
	virtual  SDL_Rect getColisionBox(){ return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
	virtual void draw(); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	virtual bool estapintado(){ return pintado; }
private:
	bool pintado;
};

