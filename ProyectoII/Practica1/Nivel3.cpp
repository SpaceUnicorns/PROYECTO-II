#include "Nivel3.h"
#include "Huella.h"
#include "MenuPG.h"

Nivel3::Nivel3(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool firstT) : Nivel1(jug, map, objetos, posRec, posCaz, act,"../sounds/reverb/ReverbCueva.wav", firstT)
{
	level = "Nivel3";
	firsTime = true;
	change = false;
	visible = true;

	cargaTriggers();
	cargaObj(objetos);
	static_cast<Huella*>(pCazador->dameComponente("Huella"))->swAble();
	static_cast<Huella*>(pRecolector->dameComponente("Huella"))->swAble();

	huellasCamino.resize(0);
	animNieve1.w = animNieve1.h = animNieve2.w = animNieve2.h = 0;

	vecZonasOscuras.resize(0);

	rectZonaOscura.h = 1940; rectZonaOscura.w = 1600;
	rectZonaOscura.x = 3022; rectZonaOscura.y = 520;
	vecZonasOscuras.push_back(rectZonaOscura);

	rectZonaOscura.h = 1940; rectZonaOscura.w = 1900;
	rectZonaOscura.x = 3808; rectZonaOscura.y = 2114;
	vecZonasOscuras.push_back(rectZonaOscura);
	/*Arbol , 1767 , 853
	Arbol , 4951 , 1963*/
	rectZonaOscura.h = 2340; rectZonaOscura.w = 1500;
	rectZonaOscura.x = 1000; rectZonaOscura.y = 53;
	vecZonasOscuras.push_back(rectZonaOscura);

	rectZonaOscura.h = 2340; rectZonaOscura.w = 900;
	rectZonaOscura.x = 4951; rectZonaOscura.y = 983;
	vecZonasOscuras.push_back(rectZonaOscura);
	
	rectZonaOscura.h = 1600; rectZonaOscura.w = 1000;
	rectZonaOscura.x = 4287; rectZonaOscura.y = 96;
	vecZonasOscuras.push_back(rectZonaOscura);

	rectZonaOscura.h = 1000; rectZonaOscura.w = 1600;
	rectZonaOscura.x = 5503; rectZonaOscura.y = 1716;
	vecZonasOscuras.push_back(rectZonaOscura);
	
}

void Nivel3::cargaTriggers(){
	vecTriggers.resize(0);
	//Madera , 6303 , 2916
	Trigger* auxTr;
	auxTr = new Trigger(pJuego, 6323, 2956, pCazador, pRecolector, 1);
	auxTr->setCallback(new changeScene(auxTr, this, false));
	auxTr->setTriggerDim(100, 400);
	vecTriggers.push_back(auxTr);
	
}

Nivel3::~Nivel3()
{
}
void Nivel3::update(int delta){
	Nivel1::update(delta);
	if (change){
		
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		pJuego->estados.push(new MenuPG(pJuego, 0));
		delete borrar;
	}
}
void Nivel3::callback(bool cabania){
	change = true;

}