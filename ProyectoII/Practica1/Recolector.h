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
	std::string getEquipo(){ return equipo; };
	void setEquipo(std::string e){ equipo = e; };
	virtual void scaleRect(int x){
		ObjetoPG::scaleRect(x);
		static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->scaleColisionBox();
	}

private:
	bool pintado;
	std::string equipo;
};

