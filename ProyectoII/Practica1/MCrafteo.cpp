#include "MCrafteo.h"
#include "TexturasSDL.h"
#include "Hacha.h"
#include "Cuerda.h"
#include "Pala.h"
#include "Pico.h"
#include "Trampa.h"
#include "Antorcha.h"
#include "ObjetoPG.h"
#include "Controles.h"

MCrafteo::MCrafteo(juegoPG*jug, int puntos, Mochila* m, Equipo* equipCaz, Equipo* equipRec, bool controles) : EstadoPG(jug, puntos), mochila(NULL)
{
	//Gestion de los submenus
	showControls = controles;
	controlsShown = false;
	menuState = Crafteo;
	equipar = 0;
	objeto = 0;
	nivelObj = 0;
	seleccion.x = pJuego->getScreenWidth() / 2 - 375 - 105;
	seleccion.y = 25;
	seleccion.h = 550;
	seleccion.w = 385;
	

	cargarAssetsAudio("../docs/fxMCrafteo.txt", 'f');
	////////////////////////////////////////////


	cazador = equipCaz;
	recolector = equipRec;
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
		{ "Pala", Rx + 120, Ry + 186 },{ "Trampa", Rx + 282, Ry + 186 }
	};
	Ry = pJuego->getScreenHeight() / 2 + 30;
	materiales = { //8 elems
		{ "Madera", Rx + 25, Ry + 18 },{ "Piedra", Rx + 138,  Ry + 17 },{ "Hueso", Rx + 256, Ry + 17 },{ "Cebo", Rx + 371, Ry + 17 },
		{ "Enredadera", Rx + 25, Ry + 132 },{ "Yesca", Rx + 138, Ry + 132 },{ "Cuerda", Rx + 256, Ry + 132 },{ "TrampaCerrada",  Rx + 371, Ry + 134 }
	};

	numPag = aux = acuD = acuI = 0;
	derecha = izquierda = flag = false;

	fondo = new TexturasSDL;
	fondo->load(pJuego->getRender(),pJuego->getPath()+"\\Galiakberova\\partidaGuardada\\temp\\screenshot.bmp");


	rectEquipoCaz.x = niños.x+ (niños.w -51) + 157; rectEquipoCaz.y = niños.y + (niños.h-51); 
	rectEquipoCaz.h = 50, rectEquipoCaz.w = 50; animEquipoCaz.h = animEquipoCaz.w = 100;
	setObjEquipo(animEquipoCaz, cazador->getEquipo());

	rectEquipoRec.x = niños.x + (niños.w - 51); rectEquipoRec.y = niños.y + (niños.h - 50); 
	rectEquipoRec.h = 50, rectEquipoRec.w = 50; animEquipoRec.h = animEquipoRec.w = 100;
	setObjEquipo(animEquipoRec, recolector->getEquipo());

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

	//Objeto equipado 
	pJuego->getTextura(TObjetoEquipo2)->draw(pJuego->getRender(), animEquipoRec, rectEquipoRec);
	pJuego->getTextura(TObjetoEquipo2)->draw(pJuego->getRender(), animEquipoCaz, rectEquipoCaz);

	//Equipables
	recuadros.w = 500;
	recuadros.x = pJuego->getScreenWidth() / 2 + 30;
	recuadros.y = pag1.y;
	recuadros.h = 333;
	SDL_Rect cartel; cartel.x = recuadros.x + recuadros.w;
	cartel.y = recuadros.y + 50;
	cartel.h = 200; cartel.w = 100;
	pJuego->getTextura(TCartelHerr)->draw(pJuego->getRender(), cartel);
	pJuego->getTextura(TEquipables)->draw(pJuego->getRender(), recuadros);
	comprobar(equipables);

	//Materiales
	recuadros.w = 500;
	recuadros.x = pJuego->getScreenWidth() / 2 + 30;
	recuadros.y = pJuego->getScreenHeight() / 2 + 30;
	recuadros.h = 250;
	cartel; cartel.x = recuadros.x + recuadros.w;
	cartel.y = recuadros.y + 25;
	cartel.h = 200; cartel.w = 100;
	pJuego->getTextura(TCartelObj)->draw(pJuego->getRender(), cartel);
	pJuego->getTextura(TMateriales)->draw(pJuego->getRender(), recuadros);
	comprobar(materiales);
	pJuego->getTextura(TMenuResaltado)->draw(pJuego->getRender(), seleccion);
	

	if (showControls && !controlsShown){

		SDL_Surface *sshot = SDL_CreateRGBSurface(0, pJuego->getScreenWidth(), pJuego->getScreenHeight(), 32, 0, 0, 0, 0);
		SDL_RenderReadPixels(pJuego->getRender(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
		std::string auxiliar = pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\temp\\screenshot.bmp";
		const char *  path1 = auxiliar.c_str();
		SDL_SaveBMP(sshot, path1);
		SDL_FreeSurface(sshot);

		SDL_RenderPresent(pJuego->getRender());
		SDL_Delay(600);
		controlsShown = true;
		reproduceFx("OpcionMenuNormal", 0, 0, 0);
		//push estado nuevo --> Opciones
		pJuego->input.enter = false;
		pJuego->estados.push(new Controles(pJuego));
		std::cout << "TODO CHACHI\n";
	}

}

void MCrafteo::update(int delta){}
void MCrafteo::animacionS() 
{
	if (acuD < 2) {

		pag1.w -= 6; //la pag se hace mas pequeña
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
		pag1.w += 6; //la pag se hace mas grande
		sombra.x = pag1.x + pag1.w - 5; //le sigue la sombra

		if (pag1.w < 332) {
			++aux;
			if (aux == 10) { sombra.w+=2; aux = 0; } //la sombra se hace mas pequeña
			pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
			
		}

		else if (pag1.w >= 332 && pag1.w < 375) {
			sombra.w = 380 - pag1.w;
			pJuego->getTextura(TSombra1)->draw(pJuego->getRender(), sombra);
/*		else if (pag1.w >= 375) {
			
			izquierda = false;
			flag = false;

			pag1.w = 375;
			sombra.w = 30;
>>>>>>> MHerramientas+Crafteo*/
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
			pJuego->getTextura(TTapa)->draw(pJuego->getRender(), recuadros,235);
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
			reproduceFx("OpcionMenuCrafteo", 0, 0, 0);
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


void MCrafteo::onKeyUp(char k)
{
	switch (k) {
	case 'q':
			
		if (menuState == Crafteo || menuState == Personaje){

			std:: string auxiliar = pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\temp\\screenshot.bmp";
			const char *  path = auxiliar.c_str();
			remove(path);
			reproduceFx("Cancelar", 0, 0, 0);
			pJuego->estados.pop();
			pJuego->estados.top()->awake();
		}
		else {
			reproduceFx("Cancelar", 0, 0, 0);
			menuState = Personaje;
			equipar = 0;
			seleccion.x = niños.x;
			seleccion.y = 575;
			seleccion.h = 125;
			seleccion.w = 117;
		}
		break;
	case 'a':
		reproduceFx("SelOpcionNormal1", 0, 0, 0);
		if (menuState == Crafteo){
			menuState = Personaje;
			equipar = 0;
			seleccion.x = niños.x;
			seleccion.y = 575;
			seleccion.h = 125;
			seleccion.w = 117;
		}
		else if (menuState == Personaje)
		{
			menuState = Crafteo;
			seleccion.x = pJuego->getScreenWidth() / 2 - 375 - 105;
			seleccion.y = 25;
			seleccion.h = 550;
			seleccion.w = 385;
		}
		else if (menuState == Objeto){
			if (objeto <= 4) objeto -= 3;
			else objeto += 3;
			if (objeto >= 5) objeto = 4;
			else if (objeto < 0) objeto = 0;
			seleccion.x = equipables[objeto].x - 5;
			seleccion.y = equipables[objeto].y - 5;
		}
		break;
	case 'b':
		reproduceFx("SelOpcionNormal1", 0, 0, 0);
		if (menuState == Crafteo){
			menuState = Personaje;
			equipar = 0;
			seleccion.x = niños.x;
			seleccion.y = 575;
			seleccion.h = 125;
			seleccion.w = 117;
		}
		else if (menuState == Personaje)
		{
			menuState = Crafteo;
			seleccion.x = pJuego->getScreenWidth() / 2 - 375 - 105;
			seleccion.y = 25;
			seleccion.h = 550;
			seleccion.w = 385;
		}
		else if (menuState == Objeto){
			if (objeto <= 4) objeto += 3;
			else objeto -= 3;
			if (objeto >= 5) objeto = 4;
			else if (objeto < 0) objeto = 0;
			seleccion.x = equipables[objeto].x - 5;
			seleccion.y = equipables[objeto].y - 5;
		}
		break;
	case 'd':
		
		if (menuState == Crafteo){
			std::string acu = std::to_string(rand() % 4);
			std::string s = "SelOpcionCrafteo" + acu;
			if (numPag < 5) reproduceFx(s, 0, 0, 0);
			derecha = true;
			acuD++;
		}
		else if (menuState == Personaje)
		{
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			if (equipar == 0){
				equipar = 1;
				seleccion.x += 157;
			}
			else{
				equipar = 0;
				seleccion.x -= 157;
			}
		}
		else if (menuState == Objeto){
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			if (objeto < 4 ) objeto += 1;
			else objeto = 0;
			seleccion.x = equipables[objeto].x - 5;
			seleccion.y = equipables[objeto].y - 5;
		}
		break;

	case 'i':
		
		if (menuState == Crafteo){
			std::string acu = std::to_string(rand() % 4);
			std::string s = "SelOpcionCrafteo" + acu;
			if (numPag != 0) reproduceFx(s, 0, 0, 0);
			izquierda = true;
			acuI++;
		}
		else if (menuState == Personaje)
		{
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			if (equipar == 0){
				equipar = 1; 
				seleccion.x += 157;
			}
			else{ 
				equipar = 0; 
				seleccion.x -= 157;
			}
		}
		else if (menuState == Objeto){
			reproduceFx("SelOpcionNormal1", 0, 0, 0);
			if (objeto > 0) objeto -= 1;
			else objeto = 4;
			seleccion.x = equipables[objeto].x - 5;
			seleccion.y = equipables[objeto].y - 5;
		}
		break;
	case 'e':
		if (menuState == Crafteo){
			craftear(); //PD se craftea con la tecla INTRO
		}
		else if (menuState == Personaje){
			reproduceFx("OpcionMenuNormal", 0, 0, 0);
			menuState = Objeto;
			objeto = 0;
			seleccion.x = equipables[objeto].x-5;
			seleccion.y = equipables[objeto].y - 5;
			seleccion.h = 105;
			seleccion.w = 105;
		}
		else if (menuState == Objeto)
		{
			if (mochila->findItem(equipables[objeto].name)){
				reproduceFx("RecogeItem1", 0, 0, 0);
				if (equipar == 1){
					
					if (mochila->getCantidad(equipables[objeto].name) <= 1 && recolector->tieneEquipo(equipables[objeto].name)) recolector->setEquipo("Nada", 0);
					if (objeto == 1) cazador->setEquipo(equipables[objeto].name, 1); else cazador->setEquipo(equipables[objeto].name, mochila->getCantidad(equipables[objeto].name));
					setObjEquipo(animEquipoCaz, cazador->getEquipo());
					setObjEquipo(animEquipoRec, recolector->getEquipo());
					seleccion.x = niños.x + 157;
				}
				else {
					if (mochila->getCantidad(equipables[objeto].name) <= 1 && cazador->tieneEquipo(equipables[objeto].name)) cazador->setEquipo("Nada", 0);
					if (objeto == 1) recolector->setEquipo(equipables[objeto].name, 1); else recolector->setEquipo(equipables[objeto].name, mochila->getCantidad(equipables[objeto].name));
					setObjEquipo(animEquipoRec, recolector->getEquipo());
					setObjEquipo(animEquipoCaz, cazador->getEquipo());
					seleccion.x = niños.x;
					
				}
				menuState = Personaje;
				seleccion.y = 575;
				seleccion.h = 125;
				seleccion.w = 117;
				
			}
			else reproduceFx("NoDisponible", 0, 0, 0);
		}
		break;

	default:
		break;
	}
}

void MCrafteo::setObjEquipo(SDL_Rect & animEquipo, int aux){
	switch (aux)
	{
	case 0: animEquipo.x = 500; //Nada
		break;
	case 1: animEquipo.x = 400; //Trampa
		break;
	case 2: animEquipo.x = 0; //Antorcha
		break;
	case 3: animEquipo.x = 100; //Hacha
		break;
	case 4: animEquipo.x = 200; //Pala
		break;
	case 5: animEquipo.x = 300; //Pico
		break;
	default:
		break;
	}
}
