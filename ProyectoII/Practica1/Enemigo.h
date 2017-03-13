#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
#include "Cazador.h"
#include "Recolector.h"
struct Pos { float x, y; };
class Enemigo :
	public ObjetoPG
{
public:
	Enemigo(juegoPG *juego, Cazador* hunter, Recolector* collector , int px, int py);
	~Enemigo();
	
	virtual SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
	virtual void draw();
	Cazador* getCazador() { return cazador; }
	Recolector* getRecolector() { return recolector; }
	ObjetoPG* getTarget(){ return objetivo; }
	void setTarget(/*ObjetoPG* target*/int chachiPiruli) { 
		if (chachiPiruli == 0)objetivo = cazador; 
		else objetivo = recolector; 
	}
	void activaFollow() { std::cout << "ACTIVOOOOOOO" <<"  TARGET  "<< objetivo->nombre <<std::endl;}
	void desactivaFollow() { std::cout << "DESACTIVA FOLLOW" << std::endl; };
	Pos getPosIni() { return posIni; }
	int damage;
	int life;

protected:
	Pos posIni;
	Cazador* cazador;
	Recolector* recolector;
	ObjetoPG* objetivo;
};

