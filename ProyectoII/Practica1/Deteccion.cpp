#include "Deteccion.h"


Deteccion::Deteccion(ObjetoJuego* entidad, float radio):Componente(entidad),radio(radio)
{
	enemy = dynamic_cast<Enemigo*>(entidad);
	activo = true;
	detectado = false;
	contador = 0;
}


Deteccion::~Deteccion()
{
}

void Deteccion::update() {
	//std::cout << "UPDATE LOBO DEPURAR \n";
	float distCaz, distRec;
	if (cazadorIn() && !recolectorIn()){
		enemy->setTarget(0);//0 cazador 1 recolector
		detectado = true;
		enemy->activaFollow();
	}
	else if (!cazadorIn() && recolectorIn()){
		enemy->setTarget(1);//0 cazador 1 recolector
		if (!detectado || contador % 40 == 0){
			enemy->activaFollow();
			detectado = true;
			contador = 1; std::cout << "TE SIGO JOPUTA" << "\n";
		}
	}
	else if (cazadorIn() && recolectorIn()) //Los dos dentro.
	{
		if (enemy->getPosIni().compruebaRadio(enemy->getCazador()->getAbsRect(), radio) <=
			enemy->getPosIni().compruebaRadio(enemy->getRecolector()->getAbsRect(), radio)){
			enemy->setTarget(0);//0 cazador 1 recolector
		}
		else
			enemy->setTarget(1);//0 cazador 1 recolector
		if (!detectado || contador % 40 == 0){
			enemy->activaFollow();
			detectado = true;
			contador = 1; std::cout << "TE SIGO JOPUTA" << "\n";
		}

	}
	else{
		if (detectado)enemy->desactivaFollow();
		detectado = false;
	}
	contador++;
	/*
	if (distCaz <  distRec && distCaz < radio) {//Llamamos al follow del lobo
		detectado = true;
		enemy->setTarget(0);
		std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
	}
	if (distCaz >=  distRec && distRec< radio) {//Llamamos al follow del lobo
		detectado = true;
		enemy->setTarget(1);
		std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
	}
	else {
		if (detectado)enemy->desactivaFollow();
		detectado = false;
	}
	/*
	//DEPURACION
	std::cout << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().y << "\n";
	std::cout << static_cast<Enemigo*>(pEntidad)->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getRect().y << "\n";
	std::cout << static_cast<Enemigo*>(pEntidad)->getPosIni().x << "     " << static_cast<Enemigo*>(pEntidad)->getPosIni().y;
	//*/
}

bool Deteccion::compruebaRadio(SDL_Rect target) {
		Punto centro; centro.y = target.h / 2 + target.y; centro.x = target.w / 2 + target.x;
		std::cout << "CENTRO X:" << centro.x << " Y:" << centro.y << "\nENEMIGO POS INI X:" << enemy->getPosIni().x <<" "<< enemy->getPosIni().y<< "\n";
		return pow(enemy->getPosIni().x - centro.x, 2) + pow(enemy->getPosIni().y - centro.y, 2)
			<= pow(radio, 2);
}

bool Deteccion::cazadorIn() {
	SDL_Rect rectCaz = enemy->getCazador()->getAbsRect();
	return compruebaRadio(rectCaz);
}

bool Deteccion::recolectorIn() {
	SDL_Rect rec = enemy->getRecolector()->getAbsRect();
	return compruebaRadio(rec);
}