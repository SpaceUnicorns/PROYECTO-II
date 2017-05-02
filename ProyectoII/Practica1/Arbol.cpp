#include "Arbol.h"
#include "ColisionBox.h"
#include "Nivel1.h"
#include <SDL.h>


Arbol::Arbol(juegoPG * juego, int px, int py, bool fantasma) : ObjetoPG(juego, px, py)
{
	nombre.push_back("1");
	nombre.push_back("Arbol");

	et = TArbol;
	interactuable = false;
	rect.w = 100;
	rect.h = 200;
	absRect.w = rect.w;
	absRect.h = rect.h;
	SDL_Rect aux; aux.x = rect.x+20 ; aux.y = rect.y + 180; aux.w = 60; aux.h = 20,
		newComponente(new ColisionBox(this, aux, false), "ColisionBox");
	pBoxCollider = static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"));
	cont = 400;
	esFantasma = fantasma;
}


Arbol::~Arbol()
{
}
void Arbol::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (esFantasma){
		if (cont <= 0) move();
		else cont--;
	}
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	pBoxCollider->draw();

}
void Arbol::move(){
	if (!(pBoxCollider->getRectBox().x > -200 && pBoxCollider->getRectBox().x < pJuego->getScreenWidth() && rect.y > -200 && rect.y < pJuego->getScreenHeight())){
		cont = 400;
		Punto pAux;
		ObjetoPG *info = nullptr;
		int rX = (rand() % 40 - 20);
		int rY = (rand() % 40 -20);
		pAux.x = rX;
		pAux.y = rY;
		if (pBoxCollider->isColiding(pAux, info) != 1){
			rect.x += rX;
			rect.y += rY;
			pBoxCollider->setRectBox(pBoxCollider->getRectBox().x + pAux.x, pBoxCollider->getRectBox().y + pAux.y);
		}
	}
}
