#include "Deteccion.h"
#include "Enemigo.h"


Deteccion::Deteccion(ObjetoJuego* entidad, float radio):Componente(entidad),radio(radio)
{
	SDL_Rect aux = static_cast<Enemigo*>(entidad)->getColisionBox();
	//posIni.x = aux.x + aux.w / 2;
	//posIni.y = aux.y;
	detectado = false;
	activo = true;
}


Deteccion::~Deteccion()
{
}

void Deteccion::update() {
	std::cout << "UPDATEEER \n";
	float distCaz, distRec;
	if (cazadorIn(distCaz)/* || recolectorIn(distRec)*/) {//Llamamos al follow del lobo
		recolectorIn(distRec);
		if (distCaz > distRec)
			static_cast<Enemigo*>(pEntidad)->setTarget(1);
		else static_cast<Enemigo*>(pEntidad)->setTarget(0);
		static_cast<Enemigo*>(pEntidad)->activaFollow();
	}
	else if (recolectorIn(distRec)) {
			static_cast<Enemigo*>(pEntidad)->setTarget(1);//Podria dar problemas xDDDDD
			static_cast<Enemigo*>(pEntidad)->activaFollow();
	}
	std::cout << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().y << "\n";
	std::cout << static_cast<Enemigo*>(pEntidad)->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getRect().y << "\n";
	std::cout << static_cast<Enemigo*>(pEntidad)->getPosIni().x << "     " << static_cast<Enemigo*>(pEntidad)->getPosIni().y;
}

bool Deteccion::compruebaRadio(SDL_Rect target, float& distancia) {
		Pos centro; centro.y = target.h / 2 + target.y; centro.x = target.w / 2 + target.x;
		distancia = pow(static_cast<Enemigo*>(pEntidad)->getPosIni().x - centro.x, 2) + pow(static_cast<Enemigo*>(pEntidad)->getPosIni().y - centro.y, 2);
		return distancia <= pow(radio, 2);
}

bool Deteccion::cazadorIn(float& dist) {
	SDL_Rect rectCaz = static_cast<Enemigo*>(pEntidad)->getCazador()->getRect();
	return compruebaRadio(rectCaz, dist);
}

bool Deteccion::recolectorIn(float& dist) {
	SDL_Rect rec = static_cast<Enemigo*>(pEntidad)->getRecolector()->getRect();
	return compruebaRadio(rec, dist);
}