#include "Nivel2.h"
#include "Nivel3.h"

Nivel2::Nivel2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool firstT) : Nivel1(jug, map, objetos, posRec, posCaz, act,"../sounds/reverb/ReverbBosque.wav", firstT)
{
	level = "Nivel2";
	firsTime = true;
	change = false;
	visible = true;
	
	cargaTriggers();
	cargaObj(objetos);

}
void Nivel2::cargaTriggers(){
	vecTriggers.resize(0);
	infoTriggers.resize(0);
	
	Trigger* auxTr;
	auxTr = new Trigger(pJuego, 2323, 2554, pCazador, pRecolector, 1);
	auxTr->setCallback(new changeScene(auxTr, this));
	auxTr->setTriggerDim(100, 800);
	vecTriggers.push_back(auxTr);
	TriggerLevel1 = auxTr;
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 5231, 887, pCazador, pRecolector, 1);
	auxTr->setCallback(new changeScene(auxTr, this));
	auxTr->setTriggerDim(100, 100);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);
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

void Nivel2::callback(){
	change = true;

}