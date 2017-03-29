#include "MCrafteo.h"
#include "TexturasSDL.h"



MCrafteo::MCrafteo(juegoPG*jug, int puntos, Mochila* m) : EstadoPG(jug, puntos), mochila(NULL)
{
	mochila = m;

	pag1.h = pag2.h = 500; //poner mas pequeño o en funcion de la pantalla
	pag1.w = pag2.w = 375;
	pag1.x = pag2.x = 180; //la posicion del libro
	pag1.y = pag2.y = 30;

	sombra.h = pag1.h;
	sombra.w = 30;
	sombra.x = pag1.x + pag1.w - 20;
	sombra.y = pag1.y;

	numPag = 0;
	derecha = izquierda = flag = false;

	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(), "..//bmps//temporal//screenshot.bmp");

	rFondo.x = rFondo.y = 0; rFondo.w = pJuego->getScreenWidth(); rFondo.h = pJuego->getScreenHeight(); //rect del fondo (ocupa toda la pantalla)
	niños.x = 230; niños.y = 560; niños.w = niños.h = 120; //rect de los personajes
	recuadros.x = 700; recuadros.y = 30; recuadros.w = 500; recuadros.h = 333; //recuadro

	font.x = font.y = 0; font.w = 20; font.h = 25;
	fuente = { 0,0,0,0 };
}


MCrafteo::~MCrafteo()
{
	delete fondo;
}

void MCrafteo::draw() {
	//Fondo
	fondo->draw(pJuego->getRender(), rFondo);
	
	//Libro
	pJuego->getTextura(TGris)->draw(pJuego->getRender(), rFondo);
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
	niños.x = 230;

	//Equipables
	recuadros.w = 500;
	recuadros.x = 700;
	recuadros.y = 30;
	recuadros.h = 333;
	pJuego->getTextura(TEquipables)->draw(pJuego->getRender(), recuadros);
	comprobar(equipables);

	//Materiales
	recuadros.w = 500;
	recuadros.x = 700;
	recuadros.y = 413;
	recuadros.h = 250;
	pJuego->getTextura(TMateriales)->draw(pJuego->getRender(), recuadros);
	comprobar(materiales);
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
