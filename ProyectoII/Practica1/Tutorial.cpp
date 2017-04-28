#include "Tutorial.h"


Tutorial::Tutorial(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz) : Nivel1(jug,map,objetos,posRec, posCaz, "R")
{
	firsTime = true;
}

void Tutorial::onKeyUp(char k){
	if (k != 't') Nivel1::onKeyUp(k);
	else if (k == 't'){
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		Punto caz; caz.x = 6925; caz.y = 8930; Punto rec; rec.x = 6970; rec.y = 8930;
		pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetos.txt", rec,caz, "R"));
		delete borrar;
	}
}
Tutorial::~Tutorial()
{
}
