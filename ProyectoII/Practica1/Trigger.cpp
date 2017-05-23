#include "Trigger.h"
#include "Nivel1.h"

Trigger::Trigger(juegoPG * juego, int px, int py, Cazador* tgC, Recolector* tgR, int indice_, bool isCab) : ObjetoPG(juego, px, py)
{
	et = TCColision;
	rect.w = 50;
	rect.h = 50;
	tgCazador = tgC;
	tgRecolector = tgR;
	triggered = reacciona = false;
	isCabania = false;
	if (indice_ != 0){
		indice = indice_ - 1;
		isCabania = isCab;
	}
	firsTime = firstDraw = true;
	
}


Trigger::~Trigger()
{
}
void Trigger::update(int delta){

	if (level->getActivePlayer() == "C"){
		if (tgCazador->getColisionBox().x > rect.x && tgCazador->getColisionBox().x < (rect.x + rect.w)
			&& tgCazador->getColisionBox().y > rect.y && tgCazador->getColisionBox().y < (rect.y + rect.h)){
			if (!reacciona){
				if (firsTime && isCabania){
					firsTime = false;
					level->visitaCab(indice);
				}
				cb->callback();
			}
			reacciona = true;
			triggered = true;
		}
		else triggered = false;
		cb->update(delta);
	}
	else{
		if (tgRecolector->getColisionBox().x > rect.x && tgRecolector->getColisionBox().x < (rect.x + rect.w)
			&& tgRecolector->getColisionBox().y > rect.y && tgRecolector->getColisionBox().y < (rect.y + rect.h)){
			if (!reacciona){
				if (firsTime && isCabania){
					firsTime = false;
					level->visitaCab(indice);
				}
				cb->callback();
			}
			triggered = true;
			reacciona = true;
		}
		else triggered = false;
		cb->update(delta);
	}
}
void Trigger::draw(){ 
	if (firstDraw) {
		firstDraw = false;
		level = static_cast<Nivel1*>(pJuego->estados.top());
	}

	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	if (level->visible)pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
}
void Trigger::lateDraw(){
	if (cb)
		cb->draw();
}