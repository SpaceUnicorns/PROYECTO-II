#include "Trigger.h"


Trigger::Trigger(juegoPG * juego, int px, int py, Cazador* tgC, Recolector* tgR) : ObjetoPG(juego, px, py)
{
	et = TCColision;
	rect.w = 50;
	rect.h = 50;
	tgCazador = tgC;
	tgRecolector = tgR;
	triggered = false;
}


Trigger::~Trigger()
{
}
void Trigger::update(){
	if (!triggered && tgCazador->getColisionBox().x > rect.x && tgCazador->getColisionBox().x < (rect.x + rect.w)){
		if(tgCazador->getColisionBox().y > rect.y && tgCazador->getColisionBox().y < (rect.y + rect.h)) {
			cb->callback();
			triggered = true;
		}
	}
	else if (!triggered && tgRecolector->getColisionBox().x > rect.x && tgRecolector->getColisionBox().x < (rect.x + rect.w)){
		if (tgRecolector->getColisionBox().y > rect.y && tgRecolector->getColisionBox().y < (rect.y + rect.h)) {
			cb->callback();
			triggered = true;
		}
	}
	cb->update();
	//triggered = false;
}
void Trigger::draw(){ 
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	cb->draw();
}