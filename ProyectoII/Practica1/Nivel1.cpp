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
#include "Cabania.h"
#include "ObjetoCabania.h"
#include<stdlib.h>
#include<time.h>

Nivel1::Nivel1(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, std::string reverb, bool firstT) : EstadoPG(jug, 0){

	level = "Nivel1";
	srand(time(NULL));

	changeCabania = false;
	mapa = new GrafoMapa();
	mode = Play;
	visible = true;
	std::vector<char> mapAux;
	cargaMapa(map, mapAux);
	mapa->creaMapa(mapAux);
	
	int numCab = 0;


	archivoObj = objetos;

	if (act == "C"){
		pCazador = new Cazador(pJuego, camara.x + (camara.w / 2), camara.y + (camara.h / 2));
		pCazador->newComponente(new AntorchaC(pCazador, this), "AntorchaC");
		vecObj.push_back(pCazador);
		pCazador->setAbsRect(abs(pCazador->getAbsRect().x - posCaz.x), abs(pCazador->getAbsRect().y - posCaz.y));

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
		pRecolector->setAbsRect(abs(pRecolector->getAbsRect().x - posCaz.x), abs(pRecolector->getAbsRect().y - posCaz.y));
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

	cargaTriggers();
	cargaObj(objetos);

	cargarAudio(reverb);
	cargarAssetsAudio("../docs/fxNivel1.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceMusica("Bosque", false);
	reproduceAmb("Viento",false);


	activePlayer = act;
	if (activePlayer == "R"){
		pCazador->swAble();
		pRecolector->swAble();
	}

	pCazador->newComponente(new Equipo(pCazador, static_cast<Mochila*>(pRecolector->dameComponente("Mochila"))), "Equipo");
	pRecolector->newComponente(new Equipo(pRecolector, static_cast<Mochila*>(pRecolector->dameComponente("Mochila"))), "Equipo");
	pRecolector->newComponente(new follow(pRecolector, pCazador, mapa, true), "follow");
	pCazador->newComponente(new follow(pCazador, pRecolector, mapa, true), "follow");

	rectEquipo.x = 50; rectEquipo.y = 50;
	rectEquipo.h = rectEquipo.w = 50;  animEquipo.h = animEquipo.w = 100;
	animEquipo.y = animEquipo.x = 0;

	rectZonaOscura.h = 2000; rectZonaOscura.w = 1200;
	rectZonaOscura.x = 1050; rectZonaOscura.y = 500;
	hasTorch = false;
	alpha = 255;
	firsTime = !firstT;
	firstDraw = true;
	contadorSw = 0;
	switching = false;
}

void Nivel1::cargaTriggers(){
	Trigger *auxTr;
	
	//dialogos de tutorial
	auxTr = new Trigger(pJuego, 6850, 9000, pCazador, pRecolector, 1); //tabulador
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial1Juntos.txt"));
	auxTr->setTriggerDim(200, 600);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 5164, 7690, pCazador, pRecolector, 2); //escondites
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial2Juntos.txt"));
	auxTr->setTriggerDim(600, 600);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 9800, 3900, pCazador, pRecolector, 3); //cabaña
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial3Juntos.txt"));
	auxTr->setTriggerDim(800, 800);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;


	auxTr = new Trigger(pJuego, 4500, 3600, pCazador, pRecolector, 4); //piedra
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial4Juntos.txt"));
	auxTr->setTriggerDim(400, 400);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	//Random comments
	auxTr = new Trigger(pJuego, 4110, 3397, pCazador, pRecolector, 5); 
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo1.txt"));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 8200, 6000, pCazador, pRecolector, 6);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo2.txt"));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 8276, 1198, pCazador, pRecolector, 7);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo3.txt"));
	auxTr->setTriggerDim(80, 80);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 2977, 1327, pCazador, pRecolector, 8); //nieve
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial5Juntos.txt"));
	auxTr->setTriggerDim(800, 800);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 6900, 8800, pCazador, pRecolector, 9); // sonido amb
	auxTr->setCallback(new SoundTrigger(auxTr));
	auxTr->setTriggerDim(100, 100);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 7900, 6000, pCazador, pRecolector, 10); // sonido amb
	auxTr->setCallback(new SoundTrigger(auxTr));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 4600, 1000, pCazador, pRecolector, 11); // sonido amb
	auxTr->setCallback(new SoundTrigger(auxTr));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

	auxTr = new Trigger(pJuego, 5200, 2200, pCazador, pRecolector, 12); // sonido amb
	auxTr->setCallback(new SoundTrigger(auxTr));
	auxTr->setTriggerDim(500, 500);
	vecTriggers.push_back(auxTr);
	infoTriggers.push_back(0); //Añadir esto cada vez que se cree un trigger;

}
bool ordena(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}
void Nivel1::draw(){

	if (firstDraw){
		firstDraw = false;
		fadeIn(20);
		loadTriggerInfo();
	}
	SDL_Rect aux;
	Tile tile;
	
	if (pJuego->input.sw) switching = true;

	if (switching) swPlayer();
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

		centroRel.x += camara.x; centroRel.y += camara.y;
		rectZonaOscura.x -= camara.x;
		rectZonaOscura.y -= camara.y;

		setCamara(0, 0); //Se reinicia el offset a 0
		EstadoPG::nieve();

		if (hasTorch){
			int aux, aux2; aux2 = rand() % 51; aux = 0;
			if (aux2 >= 45) aux = rand() % 20;

			//Poner aquí todas las zonas oscuras del mapa
			pJuego->getTextura(TZonaOscura)->setBlendMode(pJuego->getRender(), SDL_BLENDMODE_BLEND);
			pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura, 240 + (aux / 2));
			pCazador->lateDraw();
			pRecolector->lateDraw();

		}
		else pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura);

		pJuego->getTextura(TLuz)->draw(pJuego->getRender(), pJuego->getNieblaRect(), camara);

		for (ObjetoJuego* trg : vecTriggers) trg->lateDraw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
		drawEquipo();
	}
	
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
	
	if (contadorSw == 0){
		reproduceFx("CambioPersonaje", 0, 0, 0);
		if (activePlayer == "C"){
			pCazador->swAble();
			fd.x = -1 * (pCazador->getRect().x - pRecolector->getRect().x);
			fd.y = -1 * (pCazador->getRect().y - pRecolector->getRect().y);
			activePlayer = "R";
		}
		else if (activePlayer == "R") {
			pRecolector->swAble();
			fd.x = -1 * (pRecolector->getRect().x - pCazador->getRect().x);
			fd.y = -1 * (pRecolector->getRect().y - pCazador->getRect().y);
			activePlayer = "C";
		}
	}
	if(contadorSw < 28){
		contadorSw++;
		//SDL_RenderClear(pJuego->getRender());
		camara.x = fd.x / 28.0f;
		camara.y = fd.y / 28.0f;

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

		centroRel.x += camara.x; centroRel.y += camara.y;
		rectZonaOscura.x -= camara.x;
		rectZonaOscura.y -= camara.y;

		setCamara(0, 0); //Se reinicia el offset a 0
		EstadoPG::nieve();

		if (hasTorch){
			int aux, aux2; aux2 = rand() % 51; aux = 0;
			if (aux2 >= 45) aux = rand() % 20;

			//Poner aquí todas las zonas oscuras del mapa
			pJuego->getTextura(TZonaOscura)->setBlendMode(pJuego->getRender(), SDL_BLENDMODE_BLEND);
			pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura, 240 + (aux / 2));
			pCazador->lateDraw();
			pRecolector->lateDraw();

		}
		else pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura);

		pJuego->getTextura(TLuz)->draw(pJuego->getRender(), pJuego->getNieblaRect(), camara);

		for (ObjetoJuego* trg : vecTriggers) trg->lateDraw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
		
	}
	if (contadorSw == 27) {
		contadorSw = 0;
		switching = false;
		if (activePlayer == "C") pCazador->swAble();
		else pRecolector->swAble();
		pJuego->input.sw = false;
	}
}
void Nivel1::update(int delta){


	EstadoPG::update(delta);
	if (changeCabania){
		if (activePlayer == "R"){
			int x = pRecolector->getAbsRect().x - pCazador->getAbsRect().x;
			int y = pRecolector->getAbsRect().y - pCazador->getAbsRect().y;
			pCazador->setRect(x + 20, y + 20);
			pCazador->setAbsRect(x + 20, y + 20);
			pCazador->setColRect(x + 20, y + 20);
		}
		else {
			int x = pCazador->getAbsRect().x - pRecolector->getAbsRect().x;
			int y = pCazador->getAbsRect().y - pRecolector->getAbsRect().y;
			pRecolector->setRect(x + 20, y + 20);
			pRecolector->setAbsRect(x + 20, y + 20);
			pRecolector->setColRect(x + 20, y + 20);
		}
		bool visited = false;
		int objCab = cabVisitadas[lastCabVisited].obj;
		if (!cabVisitadas[lastCabVisited].visitadas){
			visited = true;
			cabVisitadas[lastCabVisited].visitadas = true;
		}
		fadeOut(40);
		pJuego->cambiaVida(300);
		saveFile();
		pRecolector->salirEscondite();
		pCazador->salirEscondite();
		Punto rec; rec.x = 1550; rec.y = 700; Punto caz; caz.x = rec.x + 80; caz.y = rec.y;
		pJuego->estados.push(new Cabania(pJuego, "../docs/cabania.txt", "../docs/cabaObj.txt", rec, caz, activePlayer, visited, objCab));
		changeCabania = false;
		rectZonaOscura.h = 2000; rectZonaOscura.w = 2500;
		rectZonaOscura.x = 1050; rectZonaOscura.y = 3600;
	}
}
void escribe(std::string s, int x, int y, std:: string name){
	std::ofstream f;
	f.open("../docs/"+name,  ios::app);
	f << s << " , " << std::to_string(x) << " , " << std::to_string(y) << "\n";
	f.close();
}
void Nivel1::onKeyUp(char k) {

	if (mode == Play){
		switch (k)
		{
		case 'q':
			reproduceFx("AbreMenu", 0, 0, 0);
			pJuego->estados.push(new MCrafteo(pJuego, contPuntos, static_cast<Mochila*>(pRecolector->dameComponente("Mochila")),
			static_cast<Equipo*>(pCazador->dameComponente("Equipo")), static_cast<Equipo*>(pRecolector->dameComponente("Equipo"))));
			break;
		case 's':
			reproduceFx("AbreMenu", 0, 0, 0);
			pJuego->estados.push(new Pausa(pJuego, this, contPuntos));
			break;
		case 't': pJuego->input.sw = true;
			break;
		default:
			break;
		}
	}
	else {
		switch (k) {
		case '1':
			vecObj.push_back(new Arbol(pJuego, pCazador->getRect().x + 20, pCazador->getRect().y - 120));
			escribe("ArbolF", centroRel.x + 20, centroRel.y - 120, archivoObj);
			break;
		case 'q':
			vecObj.push_back(new Arbol(pJuego, pCazador->getRect().x+20  ,pCazador->getRect().y-120, false));
			escribe("Arbol", centroRel.x + 20, centroRel.y - 120,archivoObj);
			break;
		case 'w': //Obstaculo piedra
			vecObj.push_back(new Obstaculo(pJuego, pCazador->getRect().x + 35, pCazador->getRect().y - 20,TObstaculoPiedra,"Pico"));
			escribe("ObsPiedra", centroRel.x + 35, centroRel.y - 20, archivoObj);
			break;
		case 'r': //Obstaculo Nieve
			vecObj.push_back(new Obstaculo(pJuego, pCazador->getRect().x + 35, pCazador->getRect().y - 20, TObstaculoNieve, "Pala"));
			escribe("ObsNieve", centroRel.x + 35, centroRel.y - 20, archivoObj);
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
			vecObj.push_back(new Lobo(pJuego, pCazador, pRecolector, mapa, pCazador->getRect().x + 30, pCazador->getRect().y + 30));
			escribe("Lobo", centroRel.x + 30, centroRel.y + 30, archivoObj);
			break;
		case '2':
			vecObj.push_back(new Valla(pJuego, pCazador->getRect().x +45, pCazador->getRect().y - 20, "A"));
			escribe("Valla", centroRel.x + 45, centroRel.y - 20, archivoObj);
			break;
		case '3':
			vecObj.push_back(new Valla(pJuego, pCazador->getRect().x + 45, pCazador->getRect().y - 20, "D"));
			escribe("Valla2", centroRel.x + 45, centroRel.y - 20, archivoObj);
			break;
		case '4':
			vecObj.push_back(new ObjetoCabania(pJuego, pCazador->getRect().x + 45, pCazador->getRect().y - 20));
			std::cout << "XCabaña: " << centroRel.x + 45 << " YCabaña: " << centroRel.y-20 << "\n";

			Trigger *auxTr;
			auxTr = new Trigger(pJuego, pCazador->getAbsRect().x + 45 + 62, pCazador->getRect().y - 35 + 271, pCazador, pRecolector);
			auxTr->setCallback(new changeScene(auxTr, this));
			auxTr->setTriggerDim(60, 80);
			vecTriggers.push_back(auxTr);	

			TrianguloBorde auxBorde;
			Punto auxPunto;

			auxPunto.x = pCazador->getRect().x + 45 + 78; auxPunto.y = pCazador->getRect().y-20 + 271; auxBorde.A = auxPunto;
			auxPunto.x = pCazador->getRect().x + 45 + 210; auxPunto.y = pCazador->getRect().y -20+ 336; auxBorde.B = auxPunto;
			auxPunto.x = pCazador->getRect().x + 45 + 308; auxPunto.y = pCazador->getRect().y -20 + 272; auxBorde.C = auxPunto;
			vectBordes.push_back(auxBorde);
			escribe("Cabania", centroRel.x + 45, centroRel.y - 20, archivoObj);
			break;
		case 's':
			 mode = Play;
			reproduceFx("AbreMenu", 0, 0, 0);
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
			if (type == "Arbol")vecObj.push_back(new Arbol(pJuego, pos.x, pos.y, false));
			else if (type == "ArbolF") vecObj.push_back(new Arbol(pJuego, pos.x, pos.y));
			else if (type == "ObsPiedra") vecObj.push_back(new Obstaculo(pJuego, pos.x, pos.y, TObstaculoPiedra, "Pico"));
			else if (type == "ObsNieve") vecObj.push_back(new Obstaculo(pJuego, pos.x, pos.y, TObstaculoNieve, "Pala"));
			else if (type == "Escondite") vecObj.push_back(new Escondite(pJuego, pos.x, pos.y));
			else if (type == "Piedra") vecObj.push_back(new Piedra(pJuego, pos.x, pos.y));
			else if (type == "Madera") vecObj.push_back(new Madera(pJuego, pos.x, pos.y));
			else if (type == "Hueso") vecObj.push_back(new Hueso(pJuego, pos.x, pos.y));
			else if (type == "Enredadera") vecObj.push_back(new Enredadera(pJuego, pos.x, pos.y));
			else if (type == "Cebo") vecObj.push_back(new Cebo(pJuego, pos.x, pos.y));
			else if (type == "Yesca") vecObj.push_back(new Yesca(pJuego, pos.x, pos.y));
			else if (type == "TrampaCerrada") vecObj.push_back(new TrampaCerrada(pJuego, pos.x, pos.y));
			else if (type == "Lobo") vecObj.push_back(new Lobo(pJuego, pCazador, pRecolector,mapa, pos.x, pos.y));
			else if (type == "Carroña") vecObj.push_back(new Carroña(pJuego, pos.x, pos.y));
			else if (type == "HS") huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "HS"));
			else if (type == "HI")huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "HI"));
			else if (type == "LS") huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "LS"));
			else if (type == "LI") huellasCamino.push_back(new HuellasCamino(pJuego, pos.x, pos.y, "LI"));
			else if (type == "Valla") vecObj.push_back(new Valla(pJuego, pos.x, pos.y, "A"));
			else if (type == "Valla2")vecObj.push_back(new Valla(pJuego, pos.x, pos.y, "D"));
			else if (type == "Cabania"){
				vecObj.push_back(new ObjetoCabania(pJuego, pos.x, pos.y));
				numCab++;
				Cab cabAux; cabAux.visitadas = false; cabAux.obj = 0;   
				int i = 0;
				i = rand() % 4;
				
				cabVisitadas.push_back(cabAux);
				Trigger *auxTr;
				auxTr = new Trigger(pJuego, pos.x + 67, pos.y + 256, pCazador, pRecolector, numCab, true);
				auxTr->setCallback(new changeScene(auxTr, this));
				auxTr->setTriggerDim(60, 80);
				vecTriggers.push_back(auxTr);

				TrianguloBorde auxBorde;
				Punto auxPunto;

				auxPunto.x = pos.x + 78; auxPunto.y = pos.y + 271 ; auxBorde.A = auxPunto;
				auxPunto.x = pos.x + 210; auxPunto.y = pos.y + 336 ; auxBorde.B = auxPunto;
				auxPunto.x = pos.x + 308; auxPunto.y = pos.y + 272; auxBorde.C = auxPunto;
				vectBordes.push_back(auxBorde);
			}

		}
	}
	f.close();

	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\cabanias.txt", std::ios::in);

	while (!f.eof() && !f.fail()){
		f >> lastCabVisited;
		if (!f.fail()){
			for (int i = 0; i < cabVisitadas.size(); i++){
				f >> cabVisitadas[i].visitadas;
				f.get(stash); f.get(stash); f.get(stash);
				f >> cabVisitadas[i].obj;
			}
		}
	}
	f.close();

	Mochila* m = dynamic_cast<Mochila*>(pRecolector->dameComponente("Mochila"));
	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\mochila.txt", std::ios::in);

	std::string s;
	while (!f.eof() && !f.fail()){
		f >> s;
		if (!f.fail()){
			f.get(stash); f.get(stash); f.get(stash);
			int cant; f >> cant;
			if(cant >0)m->newItem(s, cant);
		}
	}
	f.close();
}
void Nivel1::callback(){
	if (!firsTime){
		changeCabania = true;
		paraMusica("", false);
		paraAmb("", false);
	}
	else firsTime = false;
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
void changeScene::callback(){
	if (!reacciona){
		aux->callback();
	}
	reacciona = true;
}

void SoundTrigger::callback(){
	if (!reacciona){
		std::string fx = "";
		int rnd = rand() % 12 +1;
		if (rnd > 0 && rnd < 4)
			fx = "Buho" + to_string(rnd % 3+1);
		if (rnd > 3 && rnd < 7)
			fx = "Cuervo" + to_string(rnd % 3+1);
		if (rnd > 6 && rnd < 10)
			fx = "Maleza" + to_string(rnd % 3+1);
		if (rnd > 9 && rnd < 13)
			fx = "Aleteo" + to_string(rnd % 3+1);
		std::cout << fx << "\n";
		pObj->getPJuego()->getEstadoActual()->reproduceFx(fx, rand() % 2000 - 1000, rand() % 2000 - 1000, 0);
	}
	reacciona = true;
}

void Nivel1::loadTriggerInfo(){
	std::ifstream f;
	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
	int s;
	int i = 0;
	while (!f.eof() && !f.fail()){
		f >> s;
		if (!f.fail()){
			infoTriggers[i] = s;
		}
		i++;
	}
	f.close();

}
void Nivel1::saveMochila(){
	std::ofstream f;
	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\mochila.txt");

	Mochila* m = dynamic_cast<Mochila*>(pRecolector->dameComponente("Mochila"));
	f << "Cebo" << " , " << std::to_string(m->getCantidad("Cebo")) << "\n";
	f << "Cuerda" << " , " << std::to_string(m->getCantidad("Cuerda")) << "\n";
	f << "Enredadera" << " , " << std::to_string(m->getCantidad("Enredadera")) << "\n";
	f << "Hueso" << " , " << std::to_string(m->getCantidad("Hueso")) << "\n";
	f << "Madera" << " , " << std::to_string(m->getCantidad("Madera")) << "\n";
	f << "Piedra" << " , " << std::to_string(m->getCantidad("Piedra")) << "\n";
	f << "TrampaCerrada" << " , " << std::to_string(m->getCantidad("TrampaCerrada")) << "\n";
	f << "Yesca" << " , " << std::to_string(m->getCantidad("Yesca")) << "\n";
	f << "Hacha" << " , " << std::to_string(m->getCantidad("Hacha")) << "\n";
	f << "Pala" << " , " << std::to_string(m->getCantidad("Pala")) << "\n";
	f << "Pico" << " , " << std::to_string(m->getCantidad("Pico")) << "\n";
	f << "TrampaAbierta" << " , " << std::to_string(m->getCantidad("TrampaAbierta")) << "\n";
	f << "Antorcha" << " , " << std::to_string(m->getCantidad("Antorcha")) << "\n";
	f.close();

	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\cabanias.txt");
	f << lastCabVisited << "\n";
	for (int i = 0; i < cabVisitadas.size(); i++){
		f << cabVisitadas[i].visitadas << " , " << cabVisitadas[i].obj << "\n";
	}
	f.close();
}
void Nivel1::saveFile(){
	std::ofstream f;
	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt");
	ObjetoPG *aux;
	for (int i = 0; i < vecObj.size(); i++){
		aux = dynamic_cast<ObjetoPG*>(vecObj[i]);
	
		if (aux->nombre.size() <= 2)	f << aux->nombre[1] << " , " << std::to_string(aux->getAbsRect().x) << " , " << std::to_string(aux->getAbsRect().y) << "\n";
		else f << "Carroña" << " , " << std::to_string(aux->getAbsRect().x) << " , " << std::to_string(aux->getAbsRect().y) << "\n";
	}
	f.close();

	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\players.txt");
	f << level << "\n";
	f << "Cazador" << " , " << std::to_string(pCazador->getAbsRect().x) <<" , "<< std::to_string(pCazador->getAbsRect().y) << "\n";
	f << "Recolector" << " , " << std::to_string(pRecolector->getAbsRect().x) << " , " << std::to_string(pRecolector->getAbsRect().y) << "\n";
	f << activePlayer << "\n";
	f.close();

	f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
	for (int i = 0; i < infoTriggers.size(); i++){
		f << infoTriggers[i] << "\n";
	}
	f.close();

	saveMochila();
}
