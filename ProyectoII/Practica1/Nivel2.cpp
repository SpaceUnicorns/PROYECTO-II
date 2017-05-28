#include "Nivel2.h"
#include "Nivel3.h"
#include "Cabania.h"

Nivel2::Nivel2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool firstT) : Nivel1(jug, map, objetos, posRec, posCaz, act,"../sounds/reverb/ReverbBosque.wav", firstT)
{
	level = "Nivel2";
	firsTime = true;
	change = false;
	visible = true;
	
	cargaTriggers();
	//cargaObj(objetos);
	rectZonaOscura.h = 2000; rectZonaOscura.w = 0;
	rectZonaOscura.x = 1050; rectZonaOscura.y = 0;

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

	auxTr = new Trigger(pJuego, 3200, 1607, pCazador, pRecolector, 1);
	auxTr->setCallback(new changeScene(auxTr, this));
	auxTr->setTriggerDim(100, 100);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0);

	auxTr = new Trigger(pJuego, 4907 + 62, 1857 + 256, pCazador, pRecolector, numCab, true);
	auxTr->setCallback(new changeScene(auxTr, this));
	auxTr->setTriggerDim(60, 80);
	TriggerCabania = auxTr;
	vecTriggers.push_back(auxTr);
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
			Punto caz; caz.x = 6950; caz.y = 9150; Punto rec; rec.x = 7010; rec.y = 9130;
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetosNivel1.txt", rec, caz, "R", "../sounds/reverb/ReverbBosque.wav"));
			delete borrar;
		}
		else if (pCazador->getColisionBox().y > TriggerCabania->getColisionBox().y - 5 || pRecolector->getColisionBox().y > TriggerCabania->getColisionBox().y - 5){
			if (changeCabania){
				if (activePlayer == "R"){
					int x = pRecolector->getAbsRect().x - pCazador->getAbsRect().x;
					int y = pRecolector->getAbsRect().y - pCazador->getAbsRect().y;
					pCazador->setRect(x + 20, y + 20);
					pCazador->setAbsRect(x + 20, y + 20);
					pCazador->setColRect(x + 20, y + 20);
				}
				else {
					int x = pCazador->getAbsRect().x - pRecolector->getAbsRect().x;
					int y = pCazador->getAbsRect().y - pRecolector->getAbsRect().y;
					pRecolector->setRect(x + 20, y + 20);
					pRecolector->setAbsRect(x + 20, y + 20);
					pRecolector->setColRect(x + 20, y + 20);
				}
				bool visited = false;
				int objCab = cabVisitadas[lastCabVisited].obj;
				if (!cabVisitadas[lastCabVisited].visitadas){
					visited = true;
					cabVisitadas[lastCabVisited].visitadas = true;
				}
				fadeOut(40);
				pJuego->cambiaVida(300);
				saveFile();
				pRecolector->salirEscondite();
				pCazador->salirEscondite();
				Punto rec; rec.x = 1550; rec.y = 700; Punto caz; caz.x = rec.x + 80; caz.y = rec.y;
				pJuego->estados.push(new Cabania(pJuego, "../docs/cabania.txt", "../docs/cabaObj.txt", rec, caz, activePlayer, visited, objCab));
				changeCabania = false;
			}
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
	changeCabania = true;
}