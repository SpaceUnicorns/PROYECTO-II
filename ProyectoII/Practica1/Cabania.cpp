#include "Cabania.h"
#include <algorithm>
#include "Huella.h"
#include "Hacha.h"
#include "Pico.h"
#include "Pala.h"
#include "TrampaCerrada.h"
Cabania::Cabania(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool visited, int obj) : Nivel1(jug, map, objetos, posRec, posCaz, act, "../sounds/reverb/ReverbCabana2.wav")
{
	firsTime = true;
	change = false;
	rectZonaOscura.w = 0; rectZonaOscura.h = 0;
	firsTime = true;
	pCazador->scaleRect(2); pRecolector->scaleRect(2);

	font.x = (pJuego->getScreenWidth()/2)-(15*20);
	font.y = 90;
	font.w = 20*29;
	font.h =20;
	color.r = 255; color.g = 255; color.b = 255;

	static_cast<Huella*>(pCazador->dameComponente("Huella"))->swAble();
	static_cast<Huella*>(pRecolector->dameComponente("Huella"))->swAble();
	
	huellasCamino.resize(0);
	for (ObjetoJuego* tr : vecTriggers) delete tr;
	vecTriggers.resize(0);



	if (visited){
		
		switch (obj)
		{
		case 0:vecObj.push_back(new Hacha(pJuego, posRec.x, posRec.y + 50));
			break;
		case 1:vecObj.push_back(new Pala(pJuego, posRec.x - 50, posRec.y + 50));
			break;
		case 2: vecObj.push_back(new Pico(pJuego, posRec.x - 60, posRec.y + 50));
			break;
		case 3: vecObj.push_back(new TrampaCerrada(pJuego, posRec.x - 60, posRec.y + 50));
			break;
		default:
			break;
		}
		
	}
	
}
bool ordenation(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}

void Cabania::update(int delta){
	Nivel1::update(delta);
	if (change){
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		delete borrar;
	}
}
bool ordenaAux(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}
void Cabania::draw(){
	if (firsTime){
		firsTime = false;
		for (unsigned int i = 0; i < vecTile.size(); i++){
			vecTile[i].x *= 2; vecTile[i].y *= 2;
		}
		TrianguloBorde auxBorde;
		Punto auxPunto;

		auxPunto.x = 1310; auxPunto.y = 800; auxBorde.A = auxPunto;
		auxPunto.x = 1670; auxPunto.y = 430; auxBorde.B = auxPunto;
		auxPunto.x = 1560; auxPunto.y = 660; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);

		auxPunto.x = 1670; auxPunto.y = 430; auxBorde.A = auxPunto;
		auxPunto.x = 1560; auxPunto.y = 660; auxBorde.B = auxPunto;
		auxPunto.x = 1810; auxPunto.y = 800; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);

		auxPunto.x = 1810; auxPunto.y = 800; auxBorde.A = auxPunto;
		auxPunto.x = 1860; auxPunto.y = 940; auxBorde.B = auxPunto;
		auxPunto.x = 1555; auxPunto.y = 880; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);

		auxPunto.x = 1310; auxPunto.y = 800; auxBorde.A = auxPunto;
		auxPunto.x = 1555; auxPunto.y = 880; auxBorde.B = auxPunto;
		auxPunto.x = 1380; auxPunto.y = 940; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		paraMusica("", true);
		paraAmb("", false);
		reproduceMusica("Cabana", false);
		reproduceAmb("VientoDentroCabana", false);
		fadeIn(20);
		pCazador->setTerreno(1);
		pRecolector->setTerreno(1);
	}
	SDL_Rect aux;
	Tile tile;

	if (pJuego->input.sw) swPlayer();
	else{
		for (unsigned int i = 0; i < vecTile.size(); i++){
			vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
			tile = vecTile[i];
			aux.x = tile.x; aux.y = tile.y; aux.w = 244; aux.h = 166;
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
		std::sort(vecObj.begin(), vecObj.end(), ordenaAux);

		for (HuellasCamino* ob : huellasCamino) ob->draw((activePlayer == "R" || mode == Edition));
		for (ObjetoJuego* ob : vecObj) ob->draw();
		for (ObjetoJuego* trg : vecTriggers) trg->draw();

		centroRel.x += camara.x; centroRel.y += camara.y;
		rectZonaOscura.x -= camara.x;
		rectZonaOscura.y -= camara.y;

		setCamara(0, 0); //Se reinicia el offset a 0
	/*	int x = rand() % 100;
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
			animNieve2.y = camara.h;*/

	//	pJuego->getTextura(TNieve1)->draw(pJuego->getRender(), animNieve1, camara);
	//	pJuego->getTextura(TNieve2)->draw(pJuego->getRender(), animNieve2, camara);

		pJuego->getTextura(TLuz)->draw(pJuego->getRender(), pJuego->getNieblaRect(), camara);

		for (ObjetoJuego* trg : vecTriggers) trg->lateDraw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
	}

	drawFont(font, "Pulsa la tecla \"S\" para salir", color);
}
void Cabania::swPlayer(){
		SDL_Rect aux;
		Tile tile;
		struct feedback{
			float x; float y;
		};
		reproduceFx("CambioPersonaje", 0, 0, 0);
		if (activePlayer == "C"){
			pCazador->swAble();
			camara.x = -1 * (pCazador->getRect().x - pRecolector->getRect().x);
			camara.y = -1 * (pCazador->getRect().y - pRecolector->getRect().y);
			activePlayer = "R";
		}
		else if (activePlayer == "R") {
			pRecolector->swAble();
			camara.x = -1 * (pRecolector->getRect().x - pCazador->getRect().x);
			camara.y = -1 * (pRecolector->getRect().y - pCazador->getRect().y);
			activePlayer = "C";
		}


			for (unsigned int i = 0; i < vecTile.size(); i++){
				vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
				tile = vecTile[i];
				aux.x = tile.x; aux.y = tile.y; aux.w = 244; aux.h = 166;
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
			std::sort(vecObj.begin(), vecObj.end(), ordenaAux);
			for (ObjetoJuego* ob : vecObj){
				ob->draw();
			}
			for (ObjetoJuego* ob : vecTriggers){ //TIENE QUE SER LO ULTIMO EN DIBUJARSE
				ob->draw();
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

			pJuego->getTextura(TLuz)->draw(pJuego->getRender(), pJuego->getNieblaRect(), camara);

			for (ObjetoJuego* trg : vecTriggers) trg->lateDraw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
		
		if (activePlayer == "C") pCazador->swAble();
		else pRecolector->swAble();
		pJuego->input.sw = false;
	}
void Cabania::onKeyUp(char k){
	if (k == 'S'){
		Nivel1::fadeOut(40);
		bool recogido = true;

		if (vecObj.size() != 2) recogido = false;
		else saveMochila();
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		dynamic_cast<Nivel1*>(pJuego->estados.top())->resumeCabania(activePlayer, recogido);
		delete borrar;
	}
	else Nivel1::onKeyUp(k);
}
void Cabania::callback(){
	change = true;

}
Cabania::~Cabania()
{
}
