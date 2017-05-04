#include "Cabania.h"
#include <algorithm>
Cabania::Cabania(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act) : Nivel1(jug, map, objetos, posRec, posCaz, act)
{
	firsTime = true;
	change = false;
	rectZonaOscura.w = 0; rectZonaOscura.h = 0;
	firsTime = true;

	pCazador->scaleRect(2); pRecolector->scaleRect(2);
}
bool ordenation(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}

void Cabania::update(){
	Nivel1::update();
	if (change){
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		delete borrar;
	}
}

void Cabania::draw(){
	if (firsTime){
		firsTime = false;
		for (unsigned int i = 0; i < vecTile.size(); i++){
			vecTile[i].x *= 2; vecTile[i].y *= 2;
		}
		for (unsigned int i = 0; i < vectBordes.size(); i++){
			vectBordes[i].A.x *= 2;
			vectBordes[i].A.y *= 2;
			vectBordes[i].B.x *= 2;
			vectBordes[i].B.y *= 2;
			vectBordes[i].C.x *= 2;
			vectBordes[i].C.y *= 2;
		}
		fadeIn(20);
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
		//std::sort(vecObj.begin(), vecObj.end(), ordena);

		for (HuellasCamino* ob : huellasCamino) ob->draw((activePlayer == "R" || mode == Edition));
		for (ObjetoJuego* ob : vecObj) ob->draw();
		for (ObjetoJuego* trg : vecTriggers) trg->draw();

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
			pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura, 240 + (aux / 2));
			pCazador->lateDraw();
			pRecolector->lateDraw();

		}
		else pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura);

		pJuego->getTextura(TLuz)->draw(pJuego->getRender(), pJuego->getNieblaRect(), camara);

		for (ObjetoJuego* trg : vecTriggers) trg->lateDraw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
	}
}
void Cabania::callback(){
	change = true;

}
Cabania::~Cabania()
{
}
