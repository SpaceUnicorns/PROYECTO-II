#include "Cabania.h"
#include <algorithm>
Cabania::Cabania(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act) : Nivel1(jug, map, objetos, posRec, posCaz, act)
{
	firsTime = true;
	change = false;
	rectZonaOscura.w = 0; rectZonaOscura.h = 0;
	
	
}
bool ordenation(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}

void Cabania::update(){
	Nivel1::update();
	if (change){
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		delete borrar;
	}
}

void Cabania::callback(){
	change = true;

}
Cabania::~Cabania()
{
}
