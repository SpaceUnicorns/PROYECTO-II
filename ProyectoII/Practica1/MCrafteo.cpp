#include "MCrafteo.h"
#include "TexturasSDL.h"



MCrafteo::MCrafteo(juegoPG*jug, int puntos) : EstadoPG(jug, puntos)
{
	pag1.h = pag2.h = 500; //poner mas pequeño o en funcion de la pantalla
	pag1.w = pag2.w = 375;
	pag1.x = pag2.x = 100; //la posicion del libro
	pag1.y = pag2.y = 30;

	sombra.h = pag1.h;
	sombra.w = 30;
	sombra.x = pag1.x + pag1.w - 20;
	sombra.y = pag1.y;

	numPag = 0;
	derecha = izquierda = flag = false;
	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), "..//bmps//temp//screenshot.bmp");
	
	rekt.x = rekt.y = 0; rekt.w = 1024; rekt.h = 768;
	
}


MCrafteo::~MCrafteo()
{
	delete fondo;
}

void MCrafteo::draw() {
	//Fondo
	fondo->draw(pJuego->getRender(), rekt);
	
	//Libro
	pJuego->getTextura(TGris)->draw(pJuego->getRender(), rekt);
	if (numPag < 5)	pJuego->getPag(numPag + 1)->draw(pJuego->getRender(), pag2);
	pJuego->getPag(numPag)->draw(pJuego->getRender(), pag1);

	if (derecha && numPag < 5) animacionS(); //A. siguiente pagina
	else if (izquierda) animacionA(); //A. pagina anterior
	else { //default
		derecha = false;
		izquierda = false;
	}


}

void MCrafteo::animacionS() {

	--pag1.w; //la pag se hace mas pequeña
	sombra.x = pag1.x + pag1.w; //le sigue la sombra

	if (pag1.w < 350 && pag1.w >= 0) {
		++aux;
		if (aux == 10) { ++sombra.w; aux = 0; } //la sombra se hace mas grande
		pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
	}

	else if (pag1.w <= 0) {
		derecha = false;
		++numPag;

		pag1.w = 375;
		sombra.w = 30;
	}

}

void MCrafteo::animacionA() {

	if (!flag && numPag != 0) { //solo una vez
		pag1.w = 0;
		flag = true;
		aux = 0;
		sombra.w = 65;

		--numPag;
		if (numPag == -1) numPag = 0;
	}

	else if (flag) {

		++pag1.w; //la pag se hace mas grande
		sombra.x = pag1.x + pag1.w; //le sigue la sombra

		if (pag1.w < 350) {
			++aux;
			if (aux == 10) { --sombra.w; aux = 0; } //la sombra se hace mas pequeña
			pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
		}

		else if (pag1.w >= 375) {
			izquierda = false;
			flag = false;

			pag1.w = 375;
			sombra.w = 30;
		}
	}
	else izquierda = false;
}

void MCrafteo::update() {

}

void MCrafteo::onKeyUp(char k) {

	switch (k) {
	case 'q':
		remove("..//bmps//temp//screenshot.bmp");
		pJuego->estados.pop();
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
