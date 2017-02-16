#include "Boton.h"


Boton::Boton(juegoPG * juego, int px, int py, Texturas_t textura, CallBack_t* callback) : ObjetoPG(juego,px, py)
{
	et = textura;
	rect.w = anim.w= 256;
	rect.h = anim.h =80;
	anim.x = anim.y = 0;
	cb = callback;
}


Boton::~Boton()
{
}
bool Boton::onClick(){
	if (ObjetoPG::onClick()){
		cb(pJuego);
		return true;
	}
	return false;
}
bool Boton::onOver(){
	if (ObjetoPG::onOver()){
		anim.y = 80;
		return true;
	}
	anim.y = 0;
	return false;
}
void Boton::draw(){
	pJuego->getTextura(et)->draw(pJuego->getRender(), anim, rect);
}
