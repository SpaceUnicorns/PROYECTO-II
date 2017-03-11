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
	//virtual void update();
	virtual void draw();
	Cazador* getCazador() { return cazador; }
	Recolector* getRecolector() { return recolector; }
	void setTarget(/*ObjetoPG* target*/int chachiPiruli) { if (chachiPiruli == 0)objetivo = cazador; else objetivo = recolector; }
	void activaFollow() { std::cout << "ACTIVOOOOOOO" << std::endl; }
	Pos getPosIni() { return posIni; }

protected:
	int damage;
	int life;
	Pos posIni;
	Cazador* cazador;
	Recolector* recolector;
	ObjetoPG* objetivo;
};

