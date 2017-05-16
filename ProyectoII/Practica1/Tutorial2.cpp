#include "Tutorial2.h"
#include "Mochila.h"

Tutorial2::Tutorial2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz) : Nivel1(jug, map, objetos, posRec, posCaz, "C")
{
	firsTime = true;
	change = false;
	Trigger *auxTr; 

	auxTr = new Trigger(pJuego, 6810, 10280, pCazador, pRecolector); //sugerencia, busca a lyov
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial1Zhenya.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 7500, 9900, pCazador, pRecolector); //tengo un hacha
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial2Zhenia.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 8000, 9750, pCazador, pRecolector); //Cómo pegar
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial3Zhenya.txt"));
	auxTr->setTriggerDim(100, 900);
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 6850, 9150, pCazador, pRecolector);
	auxTr->setCallback(new changeScene(auxTr, this));
	auxTr->setTriggerDim(100, 800);
	vecTriggers.push_back(auxTr);
}

void Tutorial2::onKeyUp(char k){
	if (k != 't') Nivel1::onKeyUp(k);
}

void Tutorial2::update(){
	Nivel1::update();
	if (change){

		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		Punto caz; caz.x = 7180; caz.y = 9250; Punto rec; rec.x = 7200; rec.y = 9000;
		pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetosNivel1.txt", rec, caz, "R"));
		delete borrar;
	}

	if (firsTime && !change) {
		static_cast<Mochila*> (static_cast<Nivel1*>(pJuego->getEstadoActual())->getRecolector()->dameComponente("Mochila"))->newItem("Hacha", 1);
		firsTime = false;
	}
}

void Tutorial2::callback(){
	change = true;
}

Tutorial2::~Tutorial2() {}
