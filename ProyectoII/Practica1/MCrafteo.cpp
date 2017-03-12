#include "MCrafteo.h"



MCrafteo::MCrafteo(juegoPG*jug, int puntos) : EstadoPG(jug, puntos)
{
	pag1.h = pag2.h = 500; //poner mas pequeño o en funcion de la pantalla
	pag1.w = pag2.w = 375;
	pag1.x = pag2.x = 100; //la posicion del libro
	pag1.y = pag2.y = 30;

	sombra.h = pag1.h;
	sombra.w = 30;
	sombra.x = pag1.x + pag1.w - 1;
	sombra.y = pag1.y;

	numPag = 0;

	derecha = izquierda = flag = false;
}


MCrafteo::~MCrafteo()
{
}

void MCrafteo::draw() {
	std::cout << "pagina: " << numPag << "tamaño: " << pag1.w << "\n";

	if (numPag < 5)	pJuego->getPag(numPag + 1)->draw(pJuego->getRender(), pag2);
	pJuego->getPag(numPag)->draw(pJuego->getRender(), pag1);


	//////animacion de paso a la siguiente pagina
	if (derecha && numPag < 5) {

		pag1.w -= 1; //la pag se hace mas pequeña

		sombra.x = pag1.x + pag1.w; //le sigue la sombra

		if (pag1.w > 60) {
			sombra.w = 30;
			pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
		}
		else {
			sombra.w = 50;
			pJuego->getTextura(TSombra2)->draw(pJuego->getRender(), sombra);
		}
		
		if (pag1.w <= 0) {
			derecha = false;
			++numPag;

			pag1.w = 375;
			sombra.w = 30;
		}
	}

	//////animacion de paso a la pagina anterior
	else if (izquierda) {

		if (!flag && numPag != 0) {
			pag1.w = 0; //solo una vez
			flag = true;
			--numPag;
			if (numPag == -1) numPag = 0;
		}

		if (flag) {
			pag1.w += 1; //la pag se hace mas grande

			sombra.x = pag1.x + pag1.w; //le sigue la sombra

			if (pag1.w > 60) {
				sombra.w = 30;
				pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
			}
			else {
				sombra.w = 50;
				pJuego->getTextura(TSombra2)->draw(pJuego->getRender(), sombra);
			}

			if (pag1.w >= 375) {
				izquierda = false;
				flag = false;

				pag1.w = 375;
				sombra.w = 30;
			}
		}
		else izquierda = false;
	}

	else { //default
		derecha = false;
		izquierda = false;
	}
}

void MCrafteo::update() {

}

void MCrafteo::onKeyUp(char k) {

	switch (k) {
	case 'e':
		break;

	case 'd':
		derecha = true;
		break;

	case 'i':
		izquierda = true;
		break;

	default:
		break;
	}
}
