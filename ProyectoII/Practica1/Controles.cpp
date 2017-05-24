#include "Controles.h"


Controles::Controles(juegoPG*jug) : EstadoPG(jug, 0)
{
	cargarAssetsAudio("../docs/fxMCrafteo.txt", 'f');
	/////////////////////////////////////////////////

	pag.w = 700;
	pag.h = 500;
	pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2;
	pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2;

	rFondo.x = rFondo.y = 0; 
	rFondo.w = pJuego->getScreenWidth();
	rFondo.h = pJuego->getScreenHeight();

	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\temp\\screenshot.bmp");

	gamepad = false;
}

Controles::~Controles() {
	delete fondo;
}

void Controles::draw(){
	fondo->draw(pJuego->getRender(), rFondo);
	if (gamepad) {
		pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2 + 50;
		pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2 - 50;
		pJuego->getTextura(TControlK)->draw(pJuego->getRender(), pag);
		pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2 + 50;
		pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2 - 10;
		pag.h -= 40;
		pag.w -= 40;
		pJuego->getTextura(TGris)->draw(pJuego->getRender(), pag);
		pag.h += 40;
		pag.w += 40;
		pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2;
		pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2;
		pJuego->getTextura(TControlG)->draw(pJuego->getRender(), pag);
	}
	else {
		pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2 + 50;
		pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2 - 50;
		pJuego->getTextura(TControlG)->draw(pJuego->getRender(), pag);
		pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2 + 50;
		pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2 - 10;
		pag.h -= 40;
		pag.w -= 40;
		pJuego->getTextura(TGris)->draw(pJuego->getRender(), pag);
		pag.h += 40;
		pag.w += 40;
		pag.x = pJuego->getScreenWidth() / 2 - pag.w / 2;
		pag.y = pJuego->getScreenHeight() / 2 - pag.h / 2;
		pJuego->getTextura(TControlK)->draw(pJuego->getRender(), pag);
	}
}

void Controles::onKeyUp(char t){
	std::string acu = std::to_string(rand() % 4), s = "SelOpcionCrafteo" + acu;;
	switch (t)
	{
	case 's':
		volver();
		break;
	case 'i':
		reproduceFx(s, 0, 0, 0);
		if (gamepad) gamepad = false;
		else gamepad = true;
		break;
	case 'd':
		reproduceFx(s, 0, 0, 0);
		if (gamepad) gamepad = false;
		else gamepad = true;
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
