#include "Trigger.h"
#include "Nivel1.h"

Trigger::Trigger(juegoPG * juego, int px, int py, Cazador* tgC, Recolector* tgR) : ObjetoPG(juego, px, py)
{
	et = TCColision;
	rect.w = 50;
	rect.h = 50;
	tgCazador = tgC;
	tgRecolector = tgR;
	triggered = reacciona = false;

}


Trigger::~Trigger()
{
}
void Trigger::update(){

	if (tgCazador->getColisionBox().x > rect.x && tgCazador->getColisionBox().x < (rect.x + rect.w) 
		&& tgCazador->getColisionBox().y > rect.y && tgCazador->getColisionBox().y < (rect.y + rect.h)){
			if(!reacciona) cb->callback();
			reacciona = true;
			triggered = true;
	}
	else if (tgRecolector->getColisionBox().x > rect.x && tgRecolector->getColisionBox().x < (rect.x + rect.w) 
		&& tgRecolector->getColisionBox().y > rect.y && tgRecolector->getColisionBox().y < (rect.y + rect.h)){
			if(!reacciona) cb->callback();
			triggered = true;
			reacciona = true;
	}
	else triggered = false;
	cb->update();
}
void Trigger::draw(){ 
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	if (dynamic_cast<Nivel1*>(pJuego->estados.top())->visible)pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
}
void Trigger::lateDraw(){
	
	cb->draw();
}