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
#include "follow.h"
#include "Antorcha.h"


Nivel1::Nivel1(juegoPG*jug) : EstadoPG(jug, 0){
	mapa = new GrafoMapa();
	std:: ifstream f; char aux = 'p';
	int x = 0;
	int y = -31;
	Tile aux2;
	TrianguloBorde auxBorde; 
	Punto auxPunto;
	SDL_Rect rectAux; rectAux.x = rectAux.y = -1; rectAux.w = 122; rectAux.h = 83;
	f.open("../docs/mapa.txt", std::ios::in);
	while (!f.eof()){
		//f >> x;
		f.get(aux);
		if (!f.fail()){
			//std::cout << x << "\n";
			mapa->creaMapa(aux);
			switch (aux){
				case 's':  rectAux.x = 0; aux2.rectTileset = rectAux;
						   aux2.x = x; aux2.y = y; aux2.capa = 1;
						   x += 122;
					       vecTile.push_back(aux2);
					      break;
				case 't': rectAux.x = 122; aux2.rectTileset = rectAux;
					      aux2.x = x; aux2.y = y; aux2.capa = 1;
						  x += 122;
					      vecTile.push_back(aux2);
					      break;
				case 'X': 
					//Creamos los puntos de los triangulos que forman un sprite. Cada sprite al ser un rombo forma dos rect�ngulos. 
					//Calculamos los puntos de los dos rectangulos y los a�adimos al vector de Bordes
					auxPunto.x = x; auxPunto.y = y + 32; auxBorde.A = auxPunto;
					auxPunto.x = x + 62; auxPunto.y = y; auxBorde.B = auxPunto;
					auxPunto.x = x + 122; auxPunto.y = y + 32; auxBorde.C = auxPunto;
					vectBordes.push_back(auxBorde);
					auxPunto.x = x + 62; auxPunto.y = y + 62; auxBorde.B = auxPunto;
					vectBordes.push_back(auxBorde);
					//Con estas l�neas se muestra en pantalla el sprite de los colliders de los bordes del mapa
					/*rectAux.x = 244; aux2.rectTileset = rectAux; 
					aux2.x = x; aux2.y = y; aux2.capa = 1;
					vecTile.push_back(aux2); */
					x += 122;
					break;
				case 'L': y += 31; if (y == 0 || y % 62 == 0) x = 61; else x = 0;
					break;
			}
			
		}
	}
	f.close();

	camara.x = camara.y = 0;
	camara.h = pJuego->getScreenHeight(); camara.w = pJuego->getScreenWidth();
	animNieve1.h = animNieve2.h = camara.h+1000; animNieve1.w = animNieve2.w = camara.w+1000;
	animNieve1.x = animNieve2.x = camara.w;
	animNieve1.y = animNieve2.y = camara.h;

	pCazador = new Cazador(pJuego, camara.x + (camara.w / 2), camara.y + (camara.h / 2));
	pCazador->newComponente(new Antorcha(pCazador, this), "Antorcha");
	vecObj.push_back(pCazador);
	pRecolector = new Recolector(pJuego, camara.x + (camara.w / 2) - 300, camara.y + (camara.h / 2));
	vecObj.push_back(pRecolector);

	Trigger *auxTr; auxTr = new Trigger (pJuego, 562, 384, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo1.txt"));
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 662, 384, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo2.txt"));
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 865, 70, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo3.txt"));
	auxTr->setTriggerDim(80, 80);
	vecTriggers.push_back(auxTr);


	vecObj.push_back(new Arbol(pJuego, 180, 60));
	vecObj.push_back(new Arbol(pJuego, 480, 260));
	vecObj.push_back(new Arbol(pJuego, 680, 60));
	vecObj.push_back(new Arbol(pJuego, 750, 365));
	vecObj.push_back(new Arbol(pJuego, 1080, 195));
	vecObj.push_back(new Arbol(pJuego, 480, 60));

	vecObj.push_back(new Cebo(pJuego, 780, 100));
	vecObj.push_back(new Cuerda(pJuego, 880, 100));
	vecObj.push_back(new Enredadera(pJuego, 980, 100));
	vecObj.push_back(new Hueso(pJuego, 880, 200));
	vecObj.push_back(new Madera(pJuego, 880, 300));
	vecObj.push_back(new Piedra(pJuego, 980, 200));
	vecObj.push_back(new TrampaCerrada(pJuego, 980, 300));
	vecObj.push_back(new Yesca(pJuego, 1080, 100));

	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxNivel1.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceFx("balloon", -100, 0, 0);
	//reproduceMusica("music", false);

	activePlayer = "C";

	vecObj.push_back(new Lobo(pJuego, pCazador ,pRecolector, 250, 200));
	pRecolector->newComponente(new follow(pRecolector, pCazador, mapa, true), "follow");

	rectZonaOscura.h = 600; rectZonaOscura.w = 600;
	rectZonaOscura.x = 1000; rectZonaOscura.y = 0;
	hasTorch = false;
	alpha = 255;

	mFogOfWar = SDL_CreateRGBSurface(0, rectZonaOscura.w, rectZonaOscura.h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_Rect screenRect = { 0, 0, rectZonaOscura.w, rectZonaOscura.h};
	SDL_FillRect(mFogOfWar, &screenRect, 0xFF202020);
	pTextMFogOfWar = SDL_CreateTextureFromSurface(pJuego->getRender(), mFogOfWar);

	punch = SDL_CreateRGBSurface(0, 32, 32, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);
	//SDL_Rect screenRect = { 0, 0, pJuego->getScreenWidth(), pJuego->getScreenHeight() };
	//SDL_FillRect(punch, &screenRect, 0xFF202020);

}
bool ordena(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}
void Nivel1::draw(){
	SDL_Rect aux;
	Tile tile;
	//No se si esto iria mejor en el update (??????????????????)
	if (pJuego->input.sw) swPlayer();
	else{
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
		std::sort(vecObj.begin(), vecObj.end(), ordena);
		for (ObjetoJuego* ob : vecObj) ob->draw();
		for (ObjetoJuego* trg : vecTriggers) trg->draw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
	}
	rectZonaOscura.x -= camara.x;
	rectZonaOscura.y -= camara.y;
	
	if (hasTorch){
		DrawSurface(pTextMFogOfWar);
		RemoveFogOfWar(500 + 16, 250 + 16);
		//pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura);
		//pJuego->getTextura(TAntorcha)->draw(pJuego->getRender(), camara, camara, 255-alpha);
	}
	else pJuego->getTextura(TZonaOscura)->draw(pJuego->getRender(), rectZonaOscura);
	setCamara(0,0); //Se reinicia el offset a 0
	int x = rand() % 100;
	if (x >= 60){
		animNieve1.x--;
		animNieve1.y--;
	}
	if (animNieve1.x <= 0) animNieve1.x = camara.w;
	if (animNieve1.y <= 0) animNieve1.y = camara.h;
	if (x >= 70){
		animNieve2.x--;
		animNieve2.y--;
	}
	if (animNieve2.x <= 0) animNieve2.x = camara.w*2;
	if (animNieve2.y <= 0) animNieve2.y = camara.h*2;
	pJuego->getTextura(TNieve1)->draw(pJuego->getRender(), animNieve1,camara);
	pJuego->getTextura(TNieve2)->draw(pJuego->getRender(), animNieve2, camara);

	
	pJuego->getTextura(TLuz)->draw(pJuego->getRender(),pJuego->getNieblaRect() ,camara);
	
}
void Nivel1::DrawSurface(SDL_Texture* in_Text){
	rectZonaOscura.x - camara.x;
	rectZonaOscura.y - camara.y;
	SDL_RenderCopy(pJuego->getRender(), in_Text, NULL, &rectZonaOscura); //const SDL_Rect* srcrect,	const SDL_Rect* dstrect);
}
void Nivel1::swPlayer(){
	SDL_Rect aux;
	Tile tile;
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
	std::sort(vecObj.begin(), vecObj.end(), ordena);
	for (ObjetoJuego* ob : vecObj){
		ob->draw();
	}
	for (ObjetoJuego* ob : vecTriggers){ //TIENE QUE SER LO ULTIMO EN DIBUJARSE
		ob->draw();
	}
	
	if (activePlayer == "C") pCazador->swAble();
	else pRecolector->swAble();

}

void Nivel1::onKeyUp(char k) {
	switch (k) {
	case 'q':
		pJuego->estados.push(new MCrafteo(pJuego, contPuntos));
		break;

		/*case 'p':
		if(!pause) pause = true;
		else pause = false;
		break;
		case 'S':
		pJuego->estados.push(new Pausa(pJuego,contPuntos));
		break;*/
	default:
		break;
	}
}
void Nivel1::RemoveFogOfWar(int in_X, int in_Y){
	const int halfWidth = punch->w/ 2;
	const int halfHeight = punch->h / 2;

	SDL_Rect sourceRect = { 0, 0, punch->w, punch->h };
	SDL_Rect destRect = { in_X - halfWidth, in_Y - halfHeight, punch->w, punch->h };

	// Make sure our rects stays within bounds
	if (destRect.x < 0)
	{
		sourceRect.x -= destRect.x; // remove the pixels outside of the surface
		sourceRect.w -= sourceRect.x; // shrink to the surface, not to offset fog
		destRect.x = 0;
		destRect.w -= sourceRect.x; // shrink the width to stay within bounds
	}
	if (destRect.y < 0)
	{
		sourceRect.y -= destRect.y; // remove the pixels outside
		sourceRect.h -= sourceRect.y; // shrink to the surface, not to offset fog
		destRect.y = 0;
		destRect.h -= sourceRect.y; // shrink the height to stay within bounds
	}

	int xDistanceFromEdge = (destRect.x + destRect.w) - mFogOfWar->w;
	if (xDistanceFromEdge > 0) // we're busting
	{
		sourceRect.w -= xDistanceFromEdge;
		destRect.w -= xDistanceFromEdge;
	}
	int yDistanceFromEdge = (destRect.y + destRect.h) - mFogOfWar->h;
	if (yDistanceFromEdge > 0) // we're busting
	{
		sourceRect.h -= yDistanceFromEdge;
		destRect.h -= yDistanceFromEdge;
	}

	SDL_LockSurface(mFogOfWar);

	Uint32* destPixels = (Uint32*)mFogOfWar->pixels;
	Uint32* srcPixels = (Uint32*)punch->pixels;

	static bool keepFogRemoved = true;

	for (int x = 0; x < destRect.w; ++x)
	{
		for (int y = 0; y < destRect.h; ++y)
		{
			Uint32* destPixel = destPixels + (y + destRect.y) * mFogOfWar->w + destRect.x + x;
			Uint32* srcPixel = srcPixels + (y + sourceRect.y) * punch->w + sourceRect.x + x;

			unsigned char* destAlpha = (unsigned char*)destPixel + 3; // fetch alpha channel
			unsigned char* srcAlpha = (unsigned char*)srcPixel + 3; // fetch alpha channel
			if (keepFogRemoved == true && *srcAlpha > 0)
			{
				continue; // skip this pixel
			}

			*destAlpha = *srcAlpha;
		}
	}

	SDL_UnlockSurface(mFogOfWar);
	pTextMFogOfWar = SDL_CreateTextureFromSurface(pJuego->getRender(), mFogOfWar);
}
Nivel1::~Nivel1()
{
}

