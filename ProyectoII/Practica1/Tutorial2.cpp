#include "Tutorial2.h"
#include "Mochila.h"

Tutorial2::Tutorial2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz) : Nivel1(jug, map, objetos, posRec, posCaz, "C")
{
	firsTime = true;
	change = false;
	Trigger *auxTr; 

	auxTr = new Trigger(pJuego, 6810, 10280, pCazador, pRecolector, 1); //nono1

	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial1Zhenya.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);


	auxTr = new Trigger(pJuego, 7500, 9900, pCazador, pRecolector,2); //como equiparlo

	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial2Zhenia.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 8000, 10000, pCazador, pRecolector,3); //Cómo pegar
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial3Zhenya.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 8125, 9500, pCazador, pRecolector,4); //menu de pausa
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial4Zhenia.txt"));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 6850, 9150, pCazador, pRecolector,5);
	auxTr->setCallback(new changeScene(auxTr, this));
	auxTr->setTriggerDim(100, 800);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new ChangeTerreno(pJuego, 8150, 9900, pCazador, pRecolector, 0, 6); //cambio de superficie
	auxTr->setTriggerDim(100, 900);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new ChangeTerreno(pJuego, 8150, 10000, pCazador, pRecolector, 3, 7); //cambio de superficie
	auxTr->setTriggerDim(100, 950);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);


	pCazador->setTerreno(3);
	pRecolector->setTerreno(3);

}

void Tutorial2::onKeyUp(char k){
	if (k != 't') Nivel1::onKeyUp(k);
}

void Tutorial2::update(){
	Nivel1::update();
	if (change){
		saveFile();
		std::ofstream f;
		f.open(pJuego->getPath()+"\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
		f.close();
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
