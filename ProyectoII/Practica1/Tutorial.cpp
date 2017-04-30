#include "Tutorial.h"
#include "Tutorial2.h"

Tutorial::Tutorial(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz) : Nivel1(jug,map,objetos,posRec, posCaz, "R")
{
	firsTime = true;
	change = false;
	Trigger *auxTr; auxTr = new Trigger(pJuego, 8730, 10050, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial2Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 6810, 10280, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial1Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 6950, 9202, pCazador, pRecolector);
	auxTr->setCallback(new changeScene(auxTr,this));
	auxTr->setTriggerDim(100, 800);
	vecTriggers.push_back(auxTr);
}

void Tutorial::onKeyUp(char k){
	if (k != 't') Nivel1::onKeyUp(k);
}
void Tutorial::update(){
	Nivel1::update();
	if (change){
		
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		Punto rec; rec.x = 0; rec.y = 0; Punto caz; caz.x = 6912; caz.y = 10286;
		pJuego->estados.push(new Tutorial2(pJuego, "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));
		delete borrar;
	}
}
void Tutorial::callback(){
	change = true;
	
}
Tutorial::~Tutorial()
{
}
