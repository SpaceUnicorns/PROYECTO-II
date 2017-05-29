#include "Tutorial.h"
#include "Tutorial2.h"
#include "Enredadera.h"
#include "Equipo.h"
#include "MCrafteo.h"

Tutorial::Tutorial(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz) : Nivel1(jug, map, objetos, posRec, posCaz, "R", "../sounds/reverb/ReverbBosque.wav")
{
	firsTime = true;
	change = false;
	controlsShown = false;
	Trigger *auxTr; 

	auxTr = new Trigger(pJuego, 6810, 10280, pCazador, pRecolector, 1); //como moverse
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial1Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);


	auxTr = new Trigger(pJuego, 7500, 9900, pCazador, pRecolector, 2); //recoger objetos

	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial2Lyov.txt"));
	auxTr->setTriggerDim(300, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);


	auxTr = new Trigger(pJuego, 8000, 10100, pCazador, pRecolector, 3); //sugerencia

	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial3Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 7900, 9800, pCazador, pRecolector, 4); //como craftear
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial4Lyov.txt"));
	auxTr->setTriggerDim(200, 800);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	vecObj.push_back(new Enredadera(pJuego, 7500, 9950));
	vecObj.push_back(new Enredadera(pJuego, 8350, 9900));

	auxTr = new Trigger(pJuego, 6850, 9150, pCazador, pRecolector, 5);
	auxTr->setCallback(new changeScene(auxTr,this));
	auxTr->setTriggerDim(100, 800);
	infoTriggers.push_back(0);
	vecTriggers.push_back(auxTr);

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

	vecZonasOscuras.resize(0);
}

void Tutorial::onKeyUp(char k){
	if (k == 'q'){
		reproduceFx("AbreMenu", 0, 0, 0);
		pJuego->estados.push(new MCrafteo(pJuego, contPuntos, static_cast<Mochila*>(pRecolector->dameComponente("Mochila")),
			static_cast<Equipo*>(pCazador->dameComponente("Equipo")), static_cast<Equipo*>(pRecolector->dameComponente("Equipo")), !controlsShown));
		if (!controlsShown) controlsShown = true;
	}
	else if (k != 't') Nivel1::onKeyUp(k);
}

void Tutorial::update(int delta){
	Nivel1::update(delta);
	if (change){
		saveFile();
		std::ofstream f;
		f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
		f.close();
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		Punto rec; rec.x = 0; rec.y = 0; Punto caz; caz.x = 6925; caz.y = 10260;
		pJuego->estados.push(new Tutorial2(pJuego, "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));
		delete borrar;
	}
}

void Tutorial::callback(){
	change = true;
	
}

Tutorial::~Tutorial() {}
