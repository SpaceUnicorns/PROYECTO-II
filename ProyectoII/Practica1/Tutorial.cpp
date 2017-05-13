#include "Tutorial.h"
#include "Tutorial2.h"
#include "Enredadera.h"

Tutorial::Tutorial(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz) : Nivel1(jug,map,objetos,posRec, posCaz, "R")
{
	firsTime = true;
	change = false;
	Trigger *auxTr; 

	auxTr = new Trigger(pJuego, 6810, 10280, pCazador, pRecolector,1); //como moverse
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial1Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 7500, 9900, pCazador, pRecolector,2); //recoger objetos
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial2Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 8000, 10100, pCazador, pRecolector,3); //sugerencia
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial3Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 8000, 9200, pCazador, pRecolector,4); //como craftear
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial4Lyov.txt"));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	vecObj.push_back(new Enredadera(pJuego, 7500, 9950));
	vecObj.push_back(new Enredadera(pJuego, 8350, 9900));

	auxTr = new Trigger(pJuego, 6850, 9150, pCazador, pRecolector,5);
	auxTr->setCallback(new changeScene(auxTr,this));
	auxTr->setTriggerDim(100, 800);
	infoTriggers.push_back(0);
	vecTriggers.push_back(auxTr);

	auxTr = new ChangeTerreno(pJuego, 8150, 9900, pCazador, pRecolector, 0, 6); //cambio de superficie
	auxTr->setTriggerDim(100, 900);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new ChangeTerreno(pJuego, 8150, 10000, pCazador, pRecolector, 3, 6); //cambio de superficie
	auxTr->setTriggerDim(100, 950);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	pCazador->setTerreno(3);
	pRecolector->setTerreno(3);
}

void Tutorial::onKeyUp(char k){
	if (k != 't') Nivel1::onKeyUp(k);
	else if (k == 'l');
}
void Tutorial::update(){
	Nivel1::update();
	if (change){
		saveFile();
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
