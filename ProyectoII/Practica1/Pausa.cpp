#include "Pausa.h"
#include "MenuPG.h"
#include "Trucos.h"
#include "Controles.h"


Pausa::Pausa(juegoPG*jug, Nivel1* pNivel, int puntos) :EstadoPG(jug, puntos)
{
	rFondo.x = rFondo.y = 0; rFondo.w = pJuego->getScreenWidth(); rFondo.h = pJuego->getScreenHeight(); //rect del fondo (ocupa toda la pantalla)
	boton.w = 344; 
	boton.h = 42; 
	boton.x = pJuego->getScreenWidth() / 2 - boton.w / 2; 
	boton.y = pJuego->getScreenHeight() / 2 + boton.h / 2;
	aux = pJuego->getScreenHeight() / 2 + boton.h / 2;
	rect.x = boton.x - 10; rect.y = rect.y = aux - 166; rect.w = 364; rect.h = 55;

	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\temp\\screenshot.bmp");

	cargarAssetsAudio("../docs/fxMPausa.txt", 'f');

	estado = Resume;
	temp = 0;
	
	level = pNivel;
	arriba = abajo = enter = false;
}

Pausa::~Pausa(){
	delete fondo;
}

void Pausa::draw() {

	fondo->draw(pJuego->getRender(), rFondo);
	pJuego->getTextura(TGris)->draw(pJuego->getRender(), rFondo);

	//pintar recuadro antes que los botones
	pJuego->getTextura(TMenuResaltado)->draw(pJuego->getRender(), rect);
	
	boton.y = aux - 159;
	pJuego->getTextura(TContinuar)->draw(pJuego->getRender(), boton);
	boton.y = aux - 67;
	pJuego->getTextura(TOpciones)->draw(pJuego->getRender(), boton);
	boton.y = aux + 25;
	pJuego->getTextura(TBControl)->draw(pJuego->getRender(), boton);
	boton.y = aux + 117;
	pJuego->getTextura(TGoToMenu)->draw(pJuego->getRender(), boton);

}

void Pausa::onKeyUp(char k){
	switch (k)
	{
	case 'a': arriba = true;
		break;
	case 'b': abajo = true;
		break;
	case 'e': enter = true;
		break;
	default:
		break;
	}
}
void Pausa::update() 
{
	switch (estado) 
	{
	case (Resume) :
		if (arriba) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux + 110;
			estado = Menu; //cambiar de estado
		}
		else if (abajo) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux - 74;
			estado = Opciones;
		}
		else if (enter) {
			reproduceFx("OpcionMenuNormal", 0, 0, 0);
			pJuego->input.enter = false;
			pJuego->estados.pop();
		}
		break;
	case (Opciones) :
		if (arriba) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux - 166;
			estado = Resume;
		}
		else if (abajo) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux + 18;
			estado = Control;
		}
		else if (enter) {
			reproduceFx("OpcionMenuNormal", 0, 0, 0);
			//push estado nuevo --> Opciones
			pJuego->input.enter = false;
			std::cout << "me voy a opciones --- en proceso de creacion ---\n";
			pJuego->estados.push(new Trucos(pJuego, level));
		}
		break;

	case (Control) :
		if (arriba) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux - 74;
			estado = Opciones;
		}
		else if (abajo) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux + 110;
			estado = Menu;
		}
		else if (enter) {
			reproduceFx("OpcionMenuNormal", 0, 0, 0);
			//push estado nuevo --> Opciones
			pJuego->input.enter = false;
			std::cout << "me voy a controles --- en proceso de creacion ---\n";
			pJuego->estados.push(new Controles(pJuego));
		}
		break;

	case (Menu) :
		if (arriba) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux + 18;
			estado = Control;
		}
		else if (abajo) {
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			rect.y = aux - 166;
			estado = Resume;
		}
		else if (enter) {
			reproduceFx("OpcionMenuNormal", 0, 0, 0);
			pJuego->input.enter = false;
			EstadoJuego* borrar = pJuego->estados.top();
			pJuego->cambiaVida(300);
			while (!pJuego->estados.empty()) { pJuego->getEstadoActual()->paraMusica("", false);  pJuego->estados.pop(); }
			pJuego->estados.push(new MenuPG(pJuego, 0));
			delete borrar;
		}
		break;
	}
	arriba = abajo = enter = false;
}


