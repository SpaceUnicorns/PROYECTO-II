#include "ChangeTerreno.h"


ChangeTerreno::ChangeTerreno(juegoPG * juego, int px, int py, Cazador* tgC, Recolector* tgR, int terreno, int indice_) : Trigger(juego, px, py, tgC, tgR, indice_)
{
	this->terreno = terreno;
}

void ChangeTerreno::update(){
	if (tgCazador->getColisionBox().x > rect.x && tgCazador->getColisionBox().x < (rect.x + rect.w)
		&& tgCazador->getColisionBox().y > rect.y && tgCazador->getColisionBox().y < (rect.y + rect.h)){
		if (!reacciona && !triggered) { 
			tgCazador->setTerreno(terreno);
		}
		reacciona = true;
		triggered = true;
	}
	else if (tgRecolector->getColisionBox().x > rect.x && tgRecolector->getColisionBox().x < (rect.x + rect.w)
		&& tgRecolector->getColisionBox().y > rect.y && tgRecolector->getColisionBox().y < (rect.y + rect.h)){
		if (!reacciona && !triggered){
			tgRecolector->setTerreno(terreno);
		}
		triggered = true;
		reacciona = true;
	}
	else triggered = false;
	reacciona = false;
}

ChangeTerreno::~ChangeTerreno()
{
}
