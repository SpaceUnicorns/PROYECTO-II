#include "Nivel2.h"
#include "Nivel3.h"
#include "Cabania.h"
#include "TextCb.h"


Nivel2::Nivel2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool firstT) : Nivel1(jug, map, " ", posRec, posCaz, act,"../sounds/reverb/ReverbBosque.wav", firstT)
{
	level = "Nivel2";
	firsTime = true;
	change = false;
	visible = true;
	
	cargaTriggers();
	cargaObj(objetos);
	rectZonaOscura.h = 2000; rectZonaOscura.w = 0;
	rectZonaOscura.x = 1050; rectZonaOscura.y = 0;

}
void Nivel2::cargaTriggers(){
	vecTriggers.resize(0);
	infoTriggers.resize(0);
	
	Trigger* auxTr;
	auxTr = new Trigger(pJuego, 2323, 2554, pCazador, pRecolector, 1);
	auxTr->setCallback(new changeScene(auxTr, this, false));
	auxTr->setTriggerDim(100, 800);
	vecTriggers.push_back(auxTr);
	TriggerLevel1 = auxTr;
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 3200, 1607, pCazador, pRecolector, 2);
	auxTr->setCallback(new changeScene(auxTr, this, false));
	auxTr->setTriggerDim(100, 100);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 2500, 2394, pCazador, pRecolector, 3);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogoN2-1.txt"));
	auxTr->setTriggerDim(100, 700);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //sigamos

	auxTr = new Trigger(pJuego, 3000, 1300, pCazador, pRecolector, 4);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogoN2-2.txt"));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //pala

	auxTr = new Trigger(pJuego, 4260, 1980, pCazador, pRecolector, 5);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogoN2-3.txt"));
	auxTr->setTriggerDim(300, 100);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //cabaña

	auxTr = new Trigger(pJuego, 3550, 868, pCazador, pRecolector, 6);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogoN2-4.txt"));
	auxTr->setTriggerDim(300, 100);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //lobos

	vecZonasOscuras.resize(0);

}

Nivel2::~Nivel2()
{
}

void Nivel2::update(int delta){
	Nivel1::update(delta);
	if (change){

		if (pCazador->getColisionBox().y > TriggerLevel1->getColisionBox().y - 5 || pRecolector->getColisionBox().y > TriggerLevel1->getColisionBox().y - 5){
			saveFile();
			std::ofstream f;
			f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
			f.close();
			Nivel1::fadeOut(40);
			EstadoJuego* borrar = pJuego->estados.top();
			pJuego->estados.pop();
			Punto caz; caz.x = 3080; caz.y = 1420; Punto rec; rec.x = 3130; rec.y = 1420;
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetosNivel1.txt", rec, caz, "R", "../sounds/reverb/ReverbBosque.wav"));
			delete borrar;
		}
		else {
			saveFile();
			std::ofstream f;
			f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
			f.close();
			Nivel1::fadeOut(40);
			EstadoJuego* borrar = pJuego->estados.top();
			pJuego->estados.pop();
			Punto caz; caz.x = 3456; caz.y = 696; Punto rec; rec.x = 3496; rec.y = 726;
			pJuego->estados.push(new Nivel3(pJuego, "../docs/mapa3.txt", "../docs/objetosNivel3.txt", rec, caz, "R"));
			delete borrar;
		}
	}
}

void Nivel2::callback(bool cabania){
	if (cabania) changeCabania = true;
	else change = true;
	
}

void Nivel2::onKeyUp(char k) {
	switch (k) {
	case '1':
		std::cout << "X: " << pRecolector->getAbsRect().x << ", Y: " << pRecolector->getAbsRect().y << "\n";
		break;
	}

}