#include "Nivel2.h"


Nivel2::Nivel2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std:: string act) : Nivel1(jug, map, objetos, posRec, posCaz, act)
{

	firsTime = true;
	change = false;
	visible = true;
	
	/*vecTriggers.clear();
	cargaTriggers();
	cargaObj(objetos);*/
}
void Nivel2::cargaTriggers(){
	vecTriggers.resize(0);
}

Nivel2::~Nivel2()
{
}

void Nivel2::update(){
	Nivel1::update();
	if (change){
		saveFile();
		std::ofstream f;
		f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
		f.close();
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		Punto rec; rec.x = 0; rec.y = 0; Punto caz; caz.x = 6925; caz.y = 10260;
		//CAMBIAR AL NIVEL SIGUIENTE
		//pJuego->estados.push(new Tutorial2(pJuego, "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));
		delete borrar;
	}
}

void Nivel2::callback(){
	change = true;

}