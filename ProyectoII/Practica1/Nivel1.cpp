#include "Nivel1.h"
#include "PremioPG.h"
#include "SDL_mixer.h"
#include "GameOver.h"
#include "Cazador.h"
#include "Arbol.h"
#include "Pausa.h"

Nivel1::Nivel1(juegoPG*jug) : EstadoPG(jug, 0){
	std:: ifstream f; char aux = 'p';
	int x = 0;
	int y = -31;
	Tile aux2;
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
				case 'X': x += 122;
					break;
				case 'L': y += 31; if (y == 0 || y % 62 == 0) x = 61; else x = 0;
					break;
			}
			
		}
	}
	f.close();
	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxNivel1.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');

	vecObj.push_back(new Cazador(pJuego, 250,550));
	vecObj.push_back(new Arbol(pJuego, 80, 80));
	reproduceFx("balloon", 5, 10, 0);
	reproduceMusica("music", false);
}
void Nivel1::draw(){
	SDL_Rect aux;
	Tile tile;
	for (int i = 0; i < vecTile.size(); i++){
		tile= vecTile[i];
		 aux.x = tile.x; aux.y = tile.y; aux.w = 122; aux.h = 83;
		pJuego->getTextura(TTileSet)->draw(pJuego->getRender(), tile.rectTileset, aux);
	}
	for (ObjetoJuego *c : vecObj) c->draw();
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

