#include "Controles.h"


Controles::Controles(juegoPG*jug) : EstadoPG(jug, 0)
{
	pag.w = 700;
	pag.h = 500;
	pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2;
	pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2;

	rFondo.x = rFondo.y = 0; 
	rFondo.w = pJuego->getScreenWidth();
	rFondo.h = pJuego->getScreenHeight();

	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\temp\\screenshot.bmp");
}

Controles::~Controles() {
	delete fondo;
}

void Controles::draw(){
	fondo->draw(pJuego->getRender(), rFondo);
	pJuego->getTextura(TControl)->draw(pJuego->getRender(), pag);
}

void Controles::onKeyUp(char t){
	switch (t)
	{
	case 's':
		volver();
		break;
	default:
		break;
	}
}

void Controles::volver(){
	EstadoJuego* borrar = pJuego->estados.top();
	pJuego->estados.pop();
	delete borrar;
}
