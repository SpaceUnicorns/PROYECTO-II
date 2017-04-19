#include "Trucos.h"
#include "Mochila.h"

Trucos::Trucos(juegoPG*jug, Nivel1* pNivel) : EstadoPG(jug, 0)
{
	rFondo.x = rFondo.y = 0; rFondo.w = pJuego->getScreenWidth(); rFondo.h = pJuego->getScreenHeight(); //rect del fondo (ocupa toda la pantalla)
	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), "..//bmps//temporal//screenshot.bmp");
	firstTime = true;
	font.x = pJuego->getScreenWidth() / 2-80; font.y = pJuego->getScreenHeight()/2-30; font.w = 80; font.h = 100;
	fuente = { 255, 255, 255, 255 };
	renderCodigo = " ";
	codigo = "";
	pRecolector = pNivel->getRecolector();
	level = pNivel;
}


Trucos::~Trucos()
{
	delete fondo;
}
void Trucos::draw() {
	if (renderCodigo.size() > 6) {
		renderCodigo = " "; codigo = "";
		font.x = pJuego->getScreenWidth() / 2 - 80; font.y = pJuego->getScreenHeight() / 2 - 30; font.w = 80; font.h = 100;
	}
	fondo->draw(pJuego->getRender(), rFondo);
	pJuego->getTextura(TPantallaTrucos)->draw(pJuego->getRender());
	drawFont(font, renderCodigo, fuente);
}

void Trucos::onKeyUp(char t){
	switch (t)
	{
	case '1': codigo += '1'; renderCodigo += '*'; font.h += 2; font.w += font.h; font.x -= 60;
		break;
	case '2':codigo += '2'; renderCodigo += '*'; font.h += 2; font.w += font.h; font.x -= 60;
		break;
	case 'a':codigo += 'a'; renderCodigo += '*'; font.h += 2; font.w += font.h; font.x -= 60;
		break;
	case 'b':codigo += 'b'; renderCodigo += '*'; font.h += 2; font.w += font.h; font.x -= 60;
		break;
	case 'c':codigo += 'c'; renderCodigo += '*'; font.h += 2; font.w += font.h; font.x -= 60;
		break;
	case 'e': if (!firstTime) desbloquea(); //Enter 
			  else firstTime = false;
		break;
	case 's': volver();
		break;
	default: codigo += 'o'; renderCodigo += '*'; font.h+=2; font.w += font.h; font.x -= 60; //Other
		break;
	}

}
void Trucos::volver(){
	EstadoJuego* borrar = pJuego->estados.top();
	pJuego->estados.pop();
	delete borrar;
}
void Trucos::desbloquea(){
	if (codigo == "12abc"){
		std::cout << "CORRECTO!\n";
		codigo = "";
		renderCodigo = " ";
		font.x = pJuego->getScreenWidth() / 2 - 80; font.y = pJuego->getScreenHeight() / 2 - 30; font.w = 80; font.h = 100;
		Mochila* aux = static_cast<Mochila*>(pRecolector->dameComponente("Mochila"));
		aux->newItem("Piedra",200);
		aux->newItem("Madera", 200);
		aux->newItem("Cebo", 200);
		aux->newItem("Cuerda", 200);
		aux->newItem("Hueso", 200);
		aux->newItem("TrampaCerrada", 200);
		aux->newItem("Yesca", 200);
		aux->newItem("Enredadera", 200);
	}
	else if (codigo == "abc12"){
		std::cout << "CORRECTO!\n";
		codigo = "";
		renderCodigo = " ";
		font.x = pJuego->getScreenWidth() / 2 - 80; font.y = pJuego->getScreenHeight() / 2 - 30; font.w = 80; font.h = 100;
		level->paraMusica(" ", true);
	}
	else {
		std::cout << "INCORRECTO!\n";
		codigo = "";
		renderCodigo = " ";
		font.x = pJuego->getScreenWidth() / 2 - 80; font.y = pJuego->getScreenHeight() / 2 - 30; font.w = 80; font.h = 100;
	}
}
