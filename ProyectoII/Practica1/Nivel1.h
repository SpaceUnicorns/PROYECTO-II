#pragma once
#include "EstadoPG.h"
#include <fstream>
#include <iostream>
#include "Cazador.h"
#include "Recolector.h"
#include "SDL_ttf.h"
#include <string>
#include "GrafoMapa.h"
#include "HuellasCamino.h"

using namespace std;

enum Mode{ Play, Edition };

class Nivel1 :
	public EstadoPG
{
public:
	Nivel1(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act);
	Nivel1(juegoPG*jug): EstadoPG(jug,0){};
	virtual ~Nivel1();
	virtual void draw();
	virtual void awake(){ 
		reproduceFx("AbreMenu1", -100, 0, 0); };
	Cazador* getCazador() { return pCazador; }
	Recolector* getRecolector() { return pRecolector; }
	void getTorch(){ hasTorch = true; }
	void dropTorch(){ hasTorch = false; paraAmb("", false); }
	void setAlpha(int i){ alpha = i; }
	void drawEquipo();

	GrafoMapa* getGrafoMapa() { return mapa; }
	void setMode(int m){ mode = (Mode)m; }
	void fadeOut(int time);
	void fadeIn(int time);
	virtual void callback(){};

	bool visible; 
	void swVisible(){
		visible = !visible;
	}
protected:
	std::string archivoObj;
	std::vector<HuellasCamino*> huellasCamino;
	Mode mode;
	SDL_Rect animNieve1, animNieve2, rectZonaOscura, animEquipo, rectEquipo;
	bool hasTorch;
	bool firsTime;
	Punto centroRel;
	int x, y, alpha;
	Cazador* pCazador;
	Recolector *pRecolector;
	std::string activePlayer;
	void swPlayer();	
	void onKeyUp(char k);
	void cargaObj(std:: string name);

	GrafoMapa* mapa;

	/*//métodos-----------------------------------------------------------------
	int getPuntos(){ return contPuntos; }
	virtual void onClick();
	virtual void update();

	virtual void newBaja(ObjetoJuego* ob);
	virtual void newPuntos(ObjetoJuego* ob);
	virtual void newPremio(ObjetoJuego* ob);
	virtual void reproduce(ObjetoJuego* ob);*/
	
	/*int contGlobos, globosTot, pmx, pmy;
	int numPremios;
	bool gameOver,pause;

	//Métodos ------------------------------------------------------------------------------------------------------------------------------------------

	int tipoGlobo();*/
};

