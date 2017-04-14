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
	if (cazadorIn(distCaz)) {//Llamamos al follow del lobo
		detectado = true;
		recolectorIn(distRec);
		if (distCaz > distRec)
			enemy->setTarget(1);
		else enemy->setTarget(0);
		std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
	}
	else if (recolectorIn(distRec)) {
		detectado = true;
		enemy->setTarget(1);//Podria dar problemas xDDDDD
		std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
	}
	else {
		if (detectado)enemy->desactivaFollow();
		std::cout << "ME VOY A CASITA" << "\n";
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
		distancia = pow(enemy->getPosIni().x - centro.x, 2) + pow(enemy->getPosIni().y - centro.y, 2);
		return distancia <= pow(radio, 2);
}

bool Deteccion::cazadorIn(float& dist) {
	SDL_Rect rectCaz = enemy->getCazador()->getRect();
	return compruebaRadio(rectCaz, dist);
}

bool Deteccion::recolectorIn(float& dist) {
	SDL_Rect rec = enemy->getRecolector()->getRect();
	return compruebaRadio(rec, dist);
}