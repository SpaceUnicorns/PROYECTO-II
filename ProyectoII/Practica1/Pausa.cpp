#include "Pausa.h"
#include "MenuPG.h"


Pausa::Pausa(juegoPG*jug, int puntos) :EstadoPG(jug, puntos)
{
	rFondo.x = rFondo.y = 0; rFondo.w = pJuego->getScreenWidth(); rFondo.h = pJuego->getScreenHeight(); //rect del fondo (ocupa toda la pantalla)
	boton.w = 344; 
	boton.h = 42; 
	boton.x = pJuego->getScreenWidth() / 2 - boton.w / 2; 
	boton.y = pJuego->getScreenHeight() / 2 + boton.h / 2;
	rect.x = boton.x - 10; rect.y = boton.y - 107; rect.w = 364; rect.h = 55;

	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), "..//bmps//temporal//screenshot.bmp");

	estado = Resume;
	temp = 0;
	aux = pJuego->getScreenHeight() / 2 + boton.h / 2;

}

Pausa::~Pausa(){
	delete fondo;
}

void Pausa::draw() {

	fondo->draw(pJuego->getRender(), rFondo);
	pJuego->getTextura(TGris)->draw(pJuego->getRender(), rFondo);

	//pintar recuadro antes que los botones
	pJuego->getTextura(TMenuResaltado)->draw(pJuego->getRender(), rect);
	
	boton.y = aux - 100;
	pJuego->getTextura(TContinuar)->draw(pJuego->getRender(), boton);
	boton.y = aux;
	pJuego->getTextura(TOpciones)->draw(pJuego->getRender(), boton);
	boton.y = aux + 100;
	pJuego->getTextura(TGoToMenu)->draw(pJuego->getRender(), boton);

}

void Pausa::update() 
{
	temp++;
	bool enter = pJuego->input.enter;

	if (temp >= 8) 
	{
		switch (estado) 
		{
		case (Resume) :
			if (pJuego->input.arriba) {
				rect.y = aux + 93;
				estado = Menu; //cambiar de estado
			}
			else if (pJuego->input.abajo) {
				rect.y = aux - 7;
				estado = Opciones;
			}
			else if (enter) {
				pJuego->input.enter = false;
				pJuego->estados.pop();
			}
			break;

		case (Opciones) :
			if (pJuego->input.arriba) {
				rect.y = aux - 107;
				estado = Resume;
			}
			else if (pJuego->input.abajo) {
				rect.y = aux + 93;
				estado = Menu;
			}
			else if (enter) {
				//push estado nuevo --> Opciones
				pJuego->input.enter = false;
				std::cout << "me voy a opciones --- en proceso de creacion ---\n";
			}
			break;

		case (Menu) :
			if (pJuego->input.arriba) {
				rect.y = aux - 7;
				estado = Opciones;
			}
			else if (pJuego->input.abajo) {
				rect.y = aux - 107;
				estado = Resume;
			}
			else if (enter) {
				pJuego->input.enter = false;
				EstadoJuego* borrar = pJuego->estados.top();
				pJuego->estados.pop();
				pJuego->estados.push(new MenuPG(pJuego, 0));
				delete borrar;
			}
			break;
		}
		temp = 0;
	}
}


