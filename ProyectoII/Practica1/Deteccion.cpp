#include "Deteccion.h"


Deteccion::Deteccion(ObjetoJuego* entidad, float radio):Componente(entidad),radio(radio)
{
	enemy = dynamic_cast<Enemigo*>(entidad);
	activo = true;
	detectado = false;
}


Deteccion::~Deteccion()
{
}

void Deteccion::update() {
	//std::cout << "UPDATE LOBO DEPURAR \n";
	float distCaz, distRec;
	cazadorIn(distCaz);
	recolectorIn(distRec);
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
	/*else {
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

bool Deteccion::compruebaRadio(SDL_Rect target, float& distancia) {
		Punto centro; centro.y = target.h / 2 + target.y; centro.x = target.w / 2 + target.x;
		distancia = sqrt(((enemy->getAbsRect().x + enemy->getAbsRect().w / 2) - centro.x) * (enemy->getAbsRect().x + enemy->getAbsRect().w / 2 - centro.x) + (enemy->getAbsRect().y + enemy->getAbsRect().h / 2 - centro.y) * (enemy->getAbsRect().y + enemy->getAbsRect().h / 2 - centro.y));
		return distancia <= radio;
}

bool Deteccion::cazadorIn(float& dist) {
	SDL_Rect rectCaz = enemy->getCazador()->getAbsRect();
	return compruebaRadio(rectCaz, dist);
}

bool Deteccion::recolectorIn(float& dist) {
	SDL_Rect rec = enemy->getRecolector()->getAbsRect();
	return compruebaRadio(rec, dist);
}