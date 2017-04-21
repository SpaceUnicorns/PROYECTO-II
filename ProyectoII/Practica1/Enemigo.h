#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
#include "Cazador.h"
#include "Recolector.h"
#include "follow.h"

enum EstadoEnemigo
{
	Quieto, Moviendo, Volviendo, Atacando, Atrapado, PostAtaque, Herido, Muerto
};
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
	void followThis(ObjetoPG* target);
	void setEstado(EstadoEnemigo est){ estado = est; }
	EstadoEnemigo getEstado(){ return estado; }
	void activaFollow();
	void desactivaFollow();
	Punto getPosIni() { return posIni; }
	int damage;
	int life;
	int getDir(){ return followEnem->getDirection(); }

protected:
	void dameUnHogar();
	EstadoEnemigo estado;
	Punto posIni;
	Cazador* cazador;
	Recolector* recolector;
	ObjetoPG* objetivo;
	ObjetoPG* casita;
	follow* followEnem;
	
};

