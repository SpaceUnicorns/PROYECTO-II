#include "MCrafteo.h"
#include "TexturasSDL.h"
#include "Hacha.h"
#include "Cuerda.h"
#include "Pala.h"
#include "Pico.h"
#include "Trampa.h"
#include "Antorcha.h"
#include "ObjetoPG.h"

MCrafteo::MCrafteo(juegoPG*jug, int puntos, Mochila* m) : EstadoPG(jug, puntos), mochila(NULL)
{
	mochila = m;
	crafteo.resize(6);
		crafteo = { "Antorcha", "Cuerda", "Hacha", "Pico", "Pala", "Trampa" };
	
	equipables = { //5 elems
		{ "Antorcha", 902, 77 },{ "Hacha", 746, 76 },  { "Pico", 1054, 76 }, { "Pala", 820, 216 }, { "Trampa", 982, 216 }
	};
	materiales = { //8 elems
		{ "Madera", 725, 431 }, { "Piedra", 838, 430 }, { "Hueso", 956, 430 }, { "Cebo", 1071, 430 },
		{ "Enredadera", 725, 545 }, { "Yesca", 838, 545 }, { "Cuerda", 956, 545 }, { "TrampaCerrada", 1072, 547 }
	};
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

	pag1.w -= 2; //la pag se hace mas pequeña
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

		pag1.w += 2; //la pag se hace mas grande
		sombra.x = pag1.x + pag1.w - 5; //le sigue la sombra

		//
		//
		if (pag1.w < 345) { //hacer que disminuya el tamaño de la sombra cuando esté a la mitad de la hoja
			++aux;
			if (aux == 10) { 
				if (sombra.x + sombra.w < pag1.x + 186)
					--sombra.w;
				else ++sombra.w;
				aux = 0;
			} //la sombra se hace mas pequeña
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
void MCrafteo::craftear(){
	ObjetoPG* kek =nullptr ; //auxiliar para poder acceder al nombre y receta
	if (crafteo[numPag] == "Cuerda"){ //la cuerda lo complica todo :V pensaba que eran solo herramientas
		kek = new Cuerda(pJuego, 0, 0);
	}
	else if (crafteo[numPag] == "Antorcha"){
		kek = new Antorcha(pJuego, 0, 0);
	} //cuando esten las clases de pondria PE:kek = new Antorcha(pJuego, 0, 0);
	else if (crafteo[numPag] == "Hacha"){
		kek = new Hacha(pJuego, 0, 0);
	}
	else if (crafteo[numPag] == "Pico"){
		kek = new Pico(pJuego, 0, 0);
	}
	else if (crafteo[numPag] == "Pala"){
		kek = new Pala(pJuego, 0, 0);
	}
	else if (crafteo[numPag] == "Trampa"){
		kek = new Trampa(pJuego, 0, 0);
	}

	if (kek != nullptr) {
		unsigned int i = 0;
		bool exito = true;
		while (i + 1 < kek->receta.size() && exito) {
			if (!(mochila->findItem(kek->receta[i + 1]) && (mochila->getCantidad(kek->receta[i + 1]) >= atoi(kek->receta[i].c_str()))))
				exito = false;

			i += 2;
		}
		if (exito) {
			for (unsigned int i = 0; i + 1 < kek->receta.size(); i += 2) {
				//std::cout << "Necesitas: " << kek->receta[i + 1] << "\n";
				mochila->removeItem(kek->receta[i + 1], atoi(kek->receta[i].c_str())); //se eliminan los objetos de la mochila
			}
			mochila->newItem(kek->nombre[1], 1); //y se añade lo crafteado

		}
	}

	/*if (kek != nullptr){
		for (unsigned int i = 0; i + 1 < kek->receta.size(); i += 2){ //comprobacion de objetos
			std::cout << "Necesitas: " << kek->receta[i + 1] << "\n";
			if (mochila->findItem(kek->receta[i + 1]))
				if (mochila->getCantidad(kek->receta[i + 1]) >= atoi(kek->receta[i].c_str())){//si está...
					mochila->removeItem(kek->receta[i + 1], atoi(kek->receta[i].c_str())); //se eliminan los objetos de la mochila
					mochila->newItem(kek->nombre[1], 1); //y se añade lo crafteado
				}//aqui hay que cambiarlo mas adelante, por el tema de las 2 mochilas, puta cuerda tt
		}
	}*/
	delete kek;
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
	case 'e':
		craftear(); //PD se craftea con la tecla INTRO
		break;

	default:
		break;
	}
}
