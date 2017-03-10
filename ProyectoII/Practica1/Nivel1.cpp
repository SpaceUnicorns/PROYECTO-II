#include "Nivel1.h"
#include "PremioPG.h"
#include "SDL_mixer.h"
#include "GameOver.h"
#include "Arbol.h"
#include <algorithm>
#include "Pausa.h"
#include "Piedra.h"
#include "Follow.h"

Nivel1::Nivel1(juegoPG*jug) : EstadoPG(jug, 0){
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
					//Creamos los puntos de los triangulos que forman un sprite. Cada sprite al ser un rombo forma dos rectángulos. 
					//Calculamos los puntos de los dos rectangulos y los añadimos al vector de Bordes
					auxPunto.x = x; auxPunto.y = y + 32; auxBorde.A = auxPunto;
					auxPunto.x = x + 62; auxPunto.y = y; auxBorde.B = auxPunto;
					auxPunto.x = x + 122; auxPunto.y = y + 32; auxBorde.C = auxPunto;
					vectBordes.push_back(auxBorde);
					auxPunto.x = x + 62; auxPunto.y = y + 62; auxBorde.B = auxPunto;
					vectBordes.push_back(auxBorde);
					//Con estas líneas se muestra en pantalla el sprite de los colliders de los bordes del mapa
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
	camara.h = 768; camara.w = 1024;

	vecObj.push_back(new Cazador(pJuego, camara.x + (camara.w/2),camara.y + (camara.h/2)));
	pCazador = static_cast<Cazador*>(vecObj[0]);
	vecObj.push_back(new Recolector(pJuego, camara.x + (camara.w / 2)+70, camara.y-30 + (camara.h / 2)));
	pRecolector = static_cast<Recolector*>(vecObj[1]);

	pRecolector->newComponente(new Follow(pRecolector, pCazador), "Follow");
	pCazador->newComponente(new Follow(pCazador, pRecolector), "Follow");

	vecObj.push_back(new Arbol(pJuego, 180, 60));
	vecObj.push_back(new Arbol(pJuego, 480, 260));
	vecObj.push_back(new Arbol(pJuego, 680, 60));
	vecObj.push_back(new Arbol(pJuego, 750, 365));
	vecObj.push_back(new Arbol(pJuego, 1080, 195));
	vecObj.push_back(new Arbol(pJuego, 480, 60));
	vecObj.push_back(new Piedra(pJuego, 880, 100));
	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxNivel1.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceFx("balloon", -100, 0, 0);
	reproduceMusica("music", false);


	activePlayer = "C";
	
	//pRecolector->swAble();
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
		for (int i = 0; i < vecTile.size(); i++){
			vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
			tile = vecTile[i];
			aux.x = tile.x; aux.y = tile.y; aux.w = 122; aux.h = 83;
			pJuego->getTextura(TTileSet)->draw(pJuego->getRender(), tile.rectTileset, aux);
		}
		for (int i = 0; i < vectBordes.size(); i++){
			vectBordes[i].A.x -= camara.x;
			vectBordes[i].A.y -= camara.y;
			vectBordes[i].B.x -= camara.x;
			vectBordes[i].B.y -= camara.y;
			vectBordes[i].C.x -= camara.x;
			vectBordes[i].C.y -= camara.y;
		}
		std::sort(vecObj.begin(), vecObj.end(), ordena);
		for (ObjetoJuego* ob : vecObj) ob->draw();

	}

	setCamara(0,0); //Se reinicia el offset a 0
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
	for (int i = 0; i < vecTile.size(); i++){
		vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
		tile = vecTile[i];
		aux.x = tile.x; aux.y = tile.y; aux.w = 122; aux.h = 83;
		pJuego->getTextura(TTileSet)->draw(pJuego->getRender(), tile.rectTileset, aux);
	}
		
	for (int i = 0; i < vectBordes.size(); i++){
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
	
	if (activePlayer == "C"){
		pCazador->swAble();
	}
	else{
		pRecolector->swAble();
	}

}
Nivel1::~Nivel1()
{
}
/*PlayPG::PlayPG(juegoPG*jug, int puntos): EstadoPG(jug, puntos)
{
	et = TFondo;
	numPremios = 0;
	globosTot = 10;
	vecObj.resize(globosTot);
	for (unsigned int i = 0; i < vecObj.size(); i++){
		int tipo = tipoGlobo();
		if (tipo <= 50) vecObj[i] = new GlobosPG(pJuego, rand() % (640 - 25), rand() % (480 - 50));
		else vecObj[i] = new GloboA(pJuego, rand() % (640 - 25), rand() % (480 - 50));
	}
	//cargar mariposa.
	vecObj.push_back(new MariposaPG(pJuego, 50, 80));
	vecObj.push_back(new MariposaPG(pJuego, 80, 100));
	vecObj.push_back(new PremioPG(pJuego,50,50));
	vecObj.push_back(new PremioPG(pJuego,50,100));

	gameOver = pause= false;
}
int PlayPG::tipoGlobo(){
	return rand() % 100;
}

void PlayPG::onClick(){
	bool encontrado = false;
	int it = vecObj.size() - 1;
	while (!encontrado && it >= 0){
		encontrado = vecObj[it]->onClick();
		it--;
	}

}
void PlayPG::onKeyUp(char k){
	switch (k)
	{
	case 'p':
		if(!pause) pause = true;
		else pause = false;
		break;
	case 'S':
		pJuego->estados.push(new Pausa(pJuego,contPuntos));
		break;
	default:
		break;
	}
}
void PlayPG::update(){
	if (!pause){
		EstadoPG::update();
		if (globosTot == 0){
			EstadoJuego* borrar = pJuego->estados.top();
			pJuego->estados.pop();
			pJuego->estados.push(new GameOver(pJuego,contPuntos));

			delete borrar;
		}
	}
}

void PlayPG::newBaja(ObjetoJuego* ob){
	if (dynamic_cast<GlobosPG*>(ob))globosTot--;
	else if (typeid(*ob) == typeid(PremioPG)) numPremios--;
}
void PlayPG::newPuntos(ObjetoJuego* ob){
	if (dynamic_cast<GlobosPG*>(ob))
		contPuntos += static_cast<GlobosPG*>(ob)->damePuntos();
	else if (typeid(*ob) == typeid(PremioPG))
		contPuntos += static_cast<PremioPG*>(ob)->damePuntos();
	
}
void PlayPG::newPremio(ObjetoJuego* ob){
	numPremios++;
	if (numPremios == 1) static_cast<PremioPG*>(vecObj[vecObj.size() - 1])->creaPremio();
	else{
		static_cast<PremioPG*>(vecObj[vecObj.size() - 2])->creaPremio();
	}
}
void PlayPG::reproduce(ObjetoJuego* ob){
	//Si otros objetos reprodujeran sonido habría que hacer un casting, tambien haria falta crear un vector de FX de sonido en el juego.
		Mix_PlayChannel(-1, pJuego->getSound()->pFx, 0);
}*/

