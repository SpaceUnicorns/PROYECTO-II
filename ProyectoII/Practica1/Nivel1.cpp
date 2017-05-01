#include "Nivel1.h"
#include "PremioPG.h"
#include "SDL_mixer.h"
#include "GameOver.h"
#include "Arbol.h"
#include <algorithm>
#include "Pausa.h"
#include "Cebo.h"
#include "Cuerda.h"
#include "Enredadera.h"
#include "Hueso.h"
#include "Madera.h"
#include "Piedra.h"
#include "TextCb.h"
#include "Trigger.h"
#include "TrampaCerrada.h"
#include "Yesca.h"
#include "MCrafteo.h"
#include "Lobo.h"
#include "AntorchaC.h"
#include "follow.h""
#include "TrampaAbierta.h"
#include "Equipo.h"
#include "Escondite.h"
#include "Obstaculo.h"
#include "Carroña.h"
#include "Valla.h"

Nivel1::Nivel1(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std:: string act) : EstadoPG(jug, 0){
	mapa = new GrafoMapa();
	mode = Play;

	std::vector<char> mapAux;
	cargaMapa(map, mapAux);
	mapa->creaMapa(mapAux);
	camara.x = camara.y = 0;
	camara.h = pJuego->getScreenHeight(); camara.w = pJuego->getScreenWidth();
	animNieve1.h = animNieve2.h = camara.h+1000; animNieve1.w = animNieve2.w = camara.w+1000;
	animNieve1.x = animNieve2.x = camara.w;
	animNieve1.y = animNieve2.y = camara.h;

	archivoObj = objetos;

	if (act == "C"){
		pCazador = new Cazador(pJuego, camara.x + (camara.w / 2), camara.y + (camara.h / 2));
		pCazador->newComponente(new AntorchaC(pCazador, this), "AntorchaC");
		vecObj.push_back(pCazador);

		pRecolector = new Recolector(pJuego, posRec.x, posRec.y);
		pRecolector->newComponente(new AntorchaC(pRecolector, this), "AntorchaC");
		vecObj.push_back(pRecolector);
	}
	else {
		pCazador = new Cazador(pJuego, posCaz.x,posCaz.y);
		pCazador->newComponente(new AntorchaC(pCazador, this), "AntorchaC");
		vecObj.push_back(pCazador);
		pRecolector = new Recolector(pJuego, camara.x + (camara.w / 2), camara.y + (camara.h / 2));
		pRecolector->newComponente(new AntorchaC(pRecolector, this), "AntorchaC");
		vecObj.push_back(pRecolector);
	}

	centroRel.x = camara.x + (camara.w / 2);
	centroRel.y = camara.y + (camara.h / 2);
	if (act == "C"){
		camara.x = (posCaz.x - (camara.w / 2));
		camara.y = (posCaz.y - (camara.h / 2));
	}
	else {
		camara.x = (posRec.x - (camara.w / 2));
		camara.y = (posRec.y - (camara.h / 2));
	}


	Trigger *auxTr; auxTr = new Trigger (pJuego, 1662, 1284, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo1.txt"));
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 1662, 1084, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo2.txt"));
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 865, 1070, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo3.txt"));
	auxTr->setTriggerDim(80, 80);
	vecTriggers.push_back(auxTr);

	cargaObj(objetos);

	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxNivel1.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceFx("balloon", -100, 0, 0);
	reproduceMusica("Galiakberova", false);


	activePlayer = act;
	if (activePlayer == "R"){
		pCazador->swAble();
		pRecolector->swAble();
	}

	
	pCazador->newComponente(new Equipo(pCazador, static_cast<Mochila*>(pRecolector->dameComponente("Mochila"))), "Equipo");
	pRecolector->newComponente(new Equipo(pRecolector, static_cast<Mochila*>(pRecolector->dameComponente("Mochila"))), "Equipo");
	pRecolector->newComponente(new follow(pRecolector, pCazador, mapa, true), "follow");

	rectEquipo.x = 50; rectEquipo.y = 50;
	rectEquipo.h = rectEquipo.w = 50;  animEquipo.h = animEquipo.w = 100;
	animEquipo.y = animEquipo.x = 0;

	rectZonaOscura.h = 1400; rectZonaOscura.w = 1200;
	rectZonaOscura.x = -100; rectZonaOscura.y = 500;
	hasTorch = false;
	alpha = 255;
	firsTime = true;
}
bool ordena(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}
void Nivel1::draw(){

	if (firsTime){
		firsTime = false;
		fadeIn(20);
	}
	SDL_Rect aux;
	Tile tile;
	
	if (pJuego->input.sw) swPlayer();
	else{
		for (unsigned int i = 0; i < vecTile.size(); i++){
			vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
			tile = vecTile[i];
			aux.x = tile.x; aux.y = tile.y; aux.w = 122; aux.h = 83;
			if (aux.x > -200 && aux.x < pJuego->getScreenWidth() && aux.y > -200 && aux.y < pJuego->getScreenHeight())
			pJuego->getTextura(TTileSet)->draw(pJuego->getRender(), tile.rectTileset, aux);
		}
		for (unsigned int i = 0; i < vectBordes.size(); i++){
			vectBordes[i].A.x -= camara.x;
			vectBordes[i].A.y -= camara.y;
			vectBordes[i].B.x -= camara.x;
			vectBordes[i].B.y -= camara.y;
			vectBordes[i].C.x -= camara.x;
			vectBordes[i].C.y -= camara.y;
		}
		std::sort(vecObj.begin(), vecObj.end(), ordena);
	
		for (HuellasCamino* ob : huellasCamino) ob->draw((activePlayer == "R" || mode == Edition));
		for (ObjetoJuego* ob : vecObj) ob->draw();
		for (ObjetoJuego* trg : vecTriggers) trg->draw();
	}
	centroRel.x += camara.x; centroRel.y += camara.y;
	rectZonaOscura.x -= camara.x;
	rectZonaOscura.y -= camara.y;
	
	setCamara(0, 0); //Se reinicia el offset a 0
	int x = rand() % 100;
	if (x >= 60){
		animNieve1.x--;
		animNieve1.y--;
	}
	if (animNieve1.x <= 0) 
		animNieve1.x = camara.w;
	if (animNieve1.y <= 0) 
		animNieve1.y = camara.h;
	
	if (x >= 70){
		animNieve2.x--;
		animNieve2.y--;
	}
	if (animNieve2.x <= 0) 
		animNieve2.x = camara.w;
	if (animNieve2.y <= 0) 
		animNieve2.y = camara.h;

	pJuego->getTextura(TNieve1)->draw(pJuego->getRender(), animNieve1, camara);
	pJuego->getTextura(TNieve2)->draw(pJuego->getRender(), animNieve2, camara);

	if (hasTorch){
		int aux, aux2; aux2 = rand() % 51; aux = 0;
		if (aux2 >= 45) aux = rand() % 20;

		//Poner aquí todas las zonas oscuras del mapa
		pJuego->getTextura(TZonaOscura)->setBlendMode(pJuego->getRender(), SDL_BLENDMODE_BLEND);
		pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura, 240 + (aux/2));
		pCazador->lateDraw();
		pRecolector->lateDraw();
		
	}
	else pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura);
	
	pJuego->getTextura(TLuz)->draw(pJuego->getRender(),pJuego->getNieblaRect() ,camara);

	for (ObjetoJuego* trg : vecTriggers) trg->lateDraw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
	drawEquipo();
	
}
void Nivel1::drawEquipo(){

	int auxiliar;
	if (activePlayer == "C") auxiliar = static_cast<Equipo*>(pCazador->dameComponente("Equipo"))->getEquipo();
	else  auxiliar = static_cast<Equipo*>(pRecolector->dameComponente("Equipo"))->getEquipo();

	//Nada, Trampa, Antorcha, Hacha
	bool dibuja = true;
	switch (auxiliar)
	{
	case 0: dibuja = false; 
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

	if (dibuja) pJuego->getTextura(TObjetoEquipo)->draw(pJuego->getRender(), animEquipo, rectEquipo);
}
void Nivel1::swPlayer(){
	SDL_Rect aux;
	Tile tile;
	reproduceFx("CambioPersonaje", -100, 0, 0);
	if (activePlayer == "C"){
		pCazador->swAble();
		camara.x = -1*(pCazador->getRect().x - pRecolector->getRect().x);
		camara.y = -1*(pCazador->getRect().y - pRecolector->getRect().y);
		activePlayer = "R";
	}
	else if (activePlayer == "R") {
		pRecolector->swAble();
		camara.x = -1*(pRecolector->getRect().x - pCazador->getRect().x);
		camara.y = -1*(pRecolector->getRect().y - pCazador->getRect().y);
		activePlayer = "C";
	}
	for (unsigned int i = 0; i < vecTile.size(); i++){
		vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
		tile = vecTile[i];
		aux.x = tile.x; aux.y = tile.y; aux.w = 122; aux.h = 83;
		pJuego->getTextura(TTileSet)->draw(pJuego->getRender(), tile.rectTileset, aux);
	}
		
	for (unsigned int i = 0; i < vectBordes.size(); i++){
		vectBordes[i].A.x -= camara.x;
		vectBordes[i].A.y -= camara.y;
		vectBordes[i].B.x -= camara.x;
		vectBordes[i].B.y -= camara.y;
		vectBordes[i].C.x -= camara.x;
		vectBordes[i].C.y -= camara.y;
	}
	for (HuellasCamino* ob : huellasCamino) ob->draw((activePlayer == "R" || mode == Edition));
	std::sort(vecObj.begin(), vecObj.end(), ordena);
	for (ObjetoJuego* ob : vecObj){
		ob->draw();
	}
	for (ObjetoJuego* ob : vecTriggers){ //TIENE QUE SER LO ULTIMO EN DIBUJARSE
		ob->draw();
	}
	
	if (activePlayer == "C") pCazador->swAble();
	else pRecolector->swAble();
	pJuego->input.sw = false;
}
void escribe(std::string s, int x, int y, std:: string name){
	std::ofstream f;
	f.open("../docs/"+name+".txt",  ios::app);
	f << s << " , " << std::to_string(x) << " , " << std::to_string(y) << "\n";
	f.close();
}
void Nivel1::onKeyUp(char k) {

	if (mode == Play){
		switch (k)
		{
		case 'q':
			reproduceFx("AbreMenu", -100, 0, 0);
			pJuego->estados.push(new MCrafteo(pJuego, contPuntos, static_cast<Mochila*>(pRecolector->dameComponente("Mochila")),
			static_cast<Equipo*>(pCazador->dameComponente("Equipo")), static_cast<Equipo*>(pRecolector->dameComponente("Equipo"))));
			break;
		case 's':
			reproduceFx("AbreMenu", -100, 0, 0);
			pJuego->estados.push(new Pausa(pJuego, this, contPuntos));

			break;
		case 't': pJuego->input.sw = true;
			break;
		case 'l': fadeOut(40); fadeIn(40);
			break;
		default:
			break;
		}
	}
	else {
		switch (k) {
		case 'q':
			vecObj.push_back(new Arbol(pJuego, pCazador->getRect().x+20  ,pCazador->getRect().y-120));
			escribe("Arbol", centroRel.x + 20, centroRel.y - 120,archivoObj);
			break;
		case 'w': //Obstaculo piedra
			vecObj.push_back(new Obstaculo(pJuego, pCazador->getRect().x + 35, pCazador->getRect().y - 20,TObstaculoPiedra,"Pico"));
			escribe("ObsPiedra", centroRel.x + 35, centroRel.y - 20, archivoObj);
			break;
		case 'r': //Obstaculo Nieve
			
			break;
		case 'y': //Escondite
			vecObj.push_back(new Escondite(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y +45));
			escribe("Escondite", centroRel.x + 20, centroRel.y + 45, archivoObj);
			break;
		case 'u': //Piedra
			vecObj.push_back(new Piedra(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50));
			escribe("Piedra", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'z': //Madera
			vecObj.push_back(new Madera(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50));
			escribe("Madera", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'o': //Hueso
			vecObj.push_back(new Hueso(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50));
			escribe("Hueso", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'p': //Enredadera
			vecObj.push_back(new Enredadera(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50));
			escribe("Enredadera", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'c': //Cebo
			vecObj.push_back(new Cebo(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50));
			escribe("Cebo", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'x': //Yesca
			vecObj.push_back(new Yesca(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50));
			escribe("Yesca", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'n': //Carroña
			vecObj.push_back(new Carroña(pJuego, pCazador->getRect().x + 40, pCazador->getRect().y +20));
			escribe("Carroña", centroRel.x + 40, centroRel.y + 20, archivoObj);
			break;
		case 'g': //Trampa Cerrada
			vecObj.push_back(new TrampaCerrada(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50));
			escribe("TrampaCerrada", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'h': //Huella Arriba Hombre
			huellasCamino.push_back(new HuellasCamino(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50, "HS"));
			escribe("HS", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'j': //Huella Abajo Hombre
			huellasCamino.push_back(new HuellasCamino(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50, "HI"));
			escribe("HI", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'k': //Huella Arriba Lobo
			huellasCamino.push_back(new HuellasCamino(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50, "LS"));
			escribe("LS", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'l': //Huella Abajo Lobo
			huellasCamino.push_back(new HuellasCamino(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y + 50, "LI"));
			escribe("LI", centroRel.x + 20, centroRel.y + 50, archivoObj);
			break;
		case 'v': //Lobo
			vecObj.push_back(new Lobo(pJuego, pCazador,pRecolector, pCazador->getRect().x + 30, pCazador->getRect().y + 30));
			escribe("Lobo", centroRel.x + 30, centroRel.y + 30, archivoObj);
			break;
		case '1':
			vecObj.push_back(new Valla(pJuego, pCazador->getRect().x +45, pCazador->getRect().y - 20, "A"));
			escribe("Valla", centroRel.x + 45, centroRel.y - 20, archivoObj);
			break;
		case '2':
			vecObj.push_back(new Valla(pJuego, pCazador->getRect().x + 45, pCazador->getRect().y - 20, "D"));
			escribe("Valla2", centroRel.x + 45, centroRel.y - 20, archivoObj);
			break;
		case 's':
			 mode = Play;
			reproduceFx("AbreMenu", -100, 0, 0);
			pJuego->estados.push(new Pausa(pJuego, this, contPuntos));

			break;
		case 't': pJuego->input.sw = true;
			break;
		default:
			break;
		}
	}
}

void Nivel1::cargaObj(std:: string name){
	std::ifstream f; 
	
	f.open(name, std::ios::in);
	ObjetoJuego *aux;
	std::string type;
	Punto pos;
	char stash;
	while (!f.eof() && !f.fail()){
		f >> type;
		f.get(stash); f.get(stash); f.get(stash);
		f >> pos.x;
		f.get(stash); f.get(stash); f.get(stash);
		f >> pos.y;
		if (!f.fail()){
			if (type == "Arbol")vecObj.push_back(new Arbol(pJuego, pos.x, pos.y));
			else if (type == "ObsPiedra") vecObj.push_back(new Obstaculo(pJuego, pos.x, pos.y, TObstaculoPiedra, "Pico"));
			else if (type == "Escondite") vecObj.push_back(new Escondite(pJuego, pos.x, pos.y));
			else if (type == "Piedra") vecObj.push_back(new Piedra(pJuego, pos.x, pos.y));
			else if (type == "Madera") vecObj.push_back(new Madera(pJuego, pos.x, pos.y));
			else if (type == "Hueso") vecObj.push_back(new Hueso(pJuego, pos.x, pos.y));
			else if (type == "Enredadera") vecObj.push_back(new Enredadera(pJuego, pos.x, pos.y));
			else if (type == "Cebo") vecObj.push_back(new Cebo(pJuego, pos.x, pos.y));
			else if (type == "Yesca") vecObj.push_back(new Yesca(pJuego, pos.x, pos.y));
			else if (type == "TrampaCerrada") vecObj.push_back(new TrampaCerrada(pJuego, pos.x, pos.y));
			else if (type == "Lobo") vecObj.push_back(new Lobo(pJuego, pCazador, pRecolector, pos.x, pos.y));
			else if (type == "Carroña") vecObj.push_back(new Carroña(pJuego, pos.x, pos.y));
			else if (type == "HS") huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "HS"));
			else if (type == "HI")huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "HI"));
			else if (type == "LS") huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "LS"));
			else if (type == "LI") huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "LI"));
			else if (type == "Valla") vecObj.push_back(new Valla(pJuego, pos.x, pos.y, "A"));
			else if (type == "Valla2")vecObj.push_back(new Valla(pJuego, pos.x, pos.y, "D"));

		}
	}
	f.close();
}
void Nivel1::fadeOut(int time){
	for (int i = 0; i < 200; i+=2){
		pJuego->getTextura(TTapa)->draw(pJuego->getRender(), i);
		SDL_RenderPresent(pJuego->getRender());
		SDL_Delay(time);
	}
}
void Nivel1::fadeIn(int time){
	for (int i = 255; i > 6; i-= 4){
		draw();
		pJuego->getTextura(TTapa)->draw(pJuego->getRender(), i);
		SDL_RenderPresent(pJuego->getRender());
		SDL_Delay(time);
	}
}
Nivel1::~Nivel1()
{
	for (HuellasCamino* it : huellasCamino){
		delete it;
	}
}

