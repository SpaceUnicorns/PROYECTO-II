#include "MCrafteo.h"
#include "TexturasSDL.h"



MCrafteo::MCrafteo(juegoPG*jug, int puntos, Mochila* m) : EstadoPG(jug, puntos), mochila(NULL)
{

	//Rects en funcion de la pantalla
	pag1.h = pag2.h = 500;
	pag1.w = pag2.w = 375;
	pag1.x = pag2.x = pJuego->getScreenWidth() / 2 - pag1.w - 100;
	pag1.y = pag2.y = 50;

	sombra.h = pag1.h;
	sombra.w = 30;
	sombra.x = pag1.x + pag1.w - 20;
	sombra.y = pag1.y;

	rFondo.x = rFondo.y = 0; rFondo.w = pJuego->getScreenWidth(); rFondo.h = pJuego->getScreenHeight(); //rect del fondo (ocupa toda la pantalla)
	niños.x = pag1.x + 50; niños.y = pag1.y + 530; niños.w = niños.h = 120; //rect de los personajes
	recuadros.x = pJuego->getScreenWidth() / 2 + 30; recuadros.y = pag1.y; recuadros.w = 500; recuadros.h = 333; //recuadro

	font.x = font.y = 0; font.w = 20; font.h = 25;
	fuente = { 0,0,0,0 };

	//resto de variables
	mochila = m;

	int Rx = recuadros.x;
	int Ry = recuadros.y;
	equipables = { //5 elems
		{ "Hacha", Rx + 46, Ry + 46 },{ "Antorcha", Rx + 202, Ry + 47 },{ "Pico", Rx + 354, Ry + 46 },
		{ "Pala", Rx + 120, Ry + 186 },{ "TrampaAbierta", Rx + 282, Ry + 186 }
	};
	Ry = pJuego->getScreenHeight() / 2 + 30;
	materiales = { //8 elems
		{ "Madera", Rx + 25, Ry + 18 },{ "Piedra", Rx + 138,  Ry + 17 },{ "Hueso", Rx + 256, Ry + 17 },{ "Cebo", Rx + 371, Ry + 17 },
		{ "Enredadera", Rx + 25, Ry + 132 },{ "Yesca", Rx + 138, Ry + 132 },{ "Cuerda", Rx + 256, Ry + 132 },{ "TrampaCerrada",  Rx + 371, Ry + 134 }
	};

	numPag = aux = acuD = acuI = 0;
	derecha = izquierda = flag = false;

	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), "..//bmps//temporal//screenshot.bmp");
}


MCrafteo::~MCrafteo()
{
	delete fondo;
}

void MCrafteo::draw() {
	//Fondo
	fondo->draw(pJuego->getRender(), rFondo);
	pJuego->getTextura(TGris)->draw(pJuego->getRender(), rFondo);

	//Libro
	if (numPag < 5)	pJuego->getPag(numPag + 1)->draw(pJuego->getRender(), pag2);
	pJuego->getPag(numPag)->draw(pJuego->getRender(), pag1);

	if (derecha && numPag < 5) animacionS(); //A. siguiente pagina
	else if (izquierda) animacionA(); //A. pagina anterior
	else { //default
		derecha = false;
		izquierda = false;
	}

	//Personajes
	pJuego->getTextura(TLyov)->draw(pJuego->getRender(), niños);
	niños.x += pag2.w - niños.w - 100;
	pJuego->getTextura(TZhenia)->draw(pJuego->getRender(), niños);
	niños.x = pag1.x + 50;

	//Equipables
	recuadros.w = 500;
	recuadros.x = pJuego->getScreenWidth() / 2 + 30;
	recuadros.y = pag1.y;
	recuadros.h = 333;
	pJuego->getTextura(TEquipables)->draw(pJuego->getRender(), recuadros);
	comprobar(equipables);

	//Materiales
	recuadros.w = 500;
	recuadros.x = pJuego->getScreenWidth() / 2 + 30;
	recuadros.y = pJuego->getScreenHeight() / 2 + 30;
	recuadros.h = 250;
	pJuego->getTextura(TMateriales)->draw(pJuego->getRender(), recuadros);
	comprobar(materiales);
}

void MCrafteo::animacionS() 
{
	if (acuD < 2) {
		pag1.w -= 2; //la pag se hace mas pequeña
		sombra.x = pag1.x + pag1.w; //le sigue la sombra

		if (pag1.w < 350 && pag1.w >= 0) {
			++aux;
			if (aux == 10) { sombra.w += 2; aux = 0; } //la sombra se hace mas grande
			pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
		}
	}
	
	if (pag1.w <= 0 || acuD >= 2) {
		derecha = false;
		++numPag;
		pag1.w = 375;
		sombra.w = 30;
		acuD = 0;
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
	else if (flag && acuI < 2) {

		pag1.w += 2; //la pag se hace mas grande
		sombra.x = pag1.x + pag1.w - 5; //le sigue la sombra

		if (pag1.w < 332) {
			++aux;
			if (aux == 10) { --sombra.w; aux = 0; } //la sombra se hace mas pequeña
			pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
		}

		else if (pag1.w >= 332 && pag1.w < 375) {
			sombra.w = 380 - pag1.w;
			pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
		}
	}
	else izquierda = false;

	if (pag1.w >= 375 || acuI >= 2) {
		izquierda = false;
		flag = false;
		pag1.w = 375;
		sombra.w = 30;
		acuI = 0;
	}
}

void MCrafteo::comprobar(std::vector<coords> const& v)
{
	for (size_t i = 0; i < v.size(); i++) //recorre el vector de posibles y comprueba si estan en la mochila
	{
		if (!mochila->findItem(v[i].name)) //si no está se pinta el cuadrado
		{ 
			recuadros.x = v[i].x;
			recuadros.y = v[i].y;
			recuadros.w = recuadros.h = 100;
			pJuego->getTextura(TTapa)->draw(pJuego->getRender(), recuadros);
		}
		else //si están se pinta el numero de objetos del tipo v[i].name
		{
			int cantidad = mochila->getCantidad(v[i].name);
			font.x = v[i].x + 10;
			font.y = v[i].y + 75;
			static_cast<EstadoPG*>(pJuego->estados.top())->drawFont(font, std::to_string(cantidad), fuente);
		}
	}
}


void MCrafteo::onKeyUp(char k)
{
	switch (k) {
	case 'q':
		remove("..//bmps//temp//screenshot.bmp");
		pJuego->estados.pop();
		break;

	case 'd':
		derecha = true;
		acuD++;
		break;

	case 'i':
		izquierda = true;
		acuI++;
		break;

	default:
		break;
	}
}
