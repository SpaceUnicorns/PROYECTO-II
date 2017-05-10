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
#include "Componente.h"
#include "Trigger.h"

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
	virtual void update();
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
	virtual void callback();

	bool visible; 
	void swVisible(){
		visible = !visible;
	}
	void resumeCabania(std:: string act){
		if (activePlayer == "R"){
			int x = pRecolector->getAbsRect().x - pCazador->getAbsRect().x;
			int y = pRecolector->getAbsRect().y - pCazador->getAbsRect().y;
			pCazador->setRect(x + 20, y + 20);
			pCazador->setColRect(x + 20, y + 20);
			pCazador->setAbsRect(x + 20, y + 20);
		}
		else {
			int x = pCazador->getAbsRect().x - pRecolector->getAbsRect().x;
			int y = pCazador->getAbsRect().y - pRecolector->getAbsRect().y;
			pRecolector->setRect(x + 20, y + 20);
			pRecolector->setColRect(x + 20, y + 20);
			pRecolector->setAbsRect(x + 20, y + 20);
		}
		if (activePlayer != act) swPlayer();
	}
protected:
	std::string archivoObj;
	std::vector<HuellasCamino*> huellasCamino;
	Mode mode;
	SDL_Rect animNieve1, animNieve2, rectZonaOscura, animEquipo, rectEquipo;
	bool hasTorch;
	bool firsTime;
	bool changeCabania;
	Punto centroRel;
	int x, y, alpha;
	Cazador* pCazador;
	Recolector *pRecolector;
	std::string activePlayer;
	virtual void swPlayer();	
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

class changeScene :
	public Componente
{
public:
	changeScene(ObjetoJuego* ent, Nivel1* aux) : Componente(ent){
		reacciona = false;
		pObj = dynamic_cast<Trigger*>(ent);
		this->aux = aux;
	};
	virtual ~changeScene(){};
	virtual void callback();
	virtual void update(){
		if (reacciona && !pObj->isTriggering()){
			reacciona = false;
			pObj->setReacciona(false);
		}
	};
	virtual void draw(){};

private:
	bool reacciona;
	Trigger* pObj;
	Nivel1* aux;
};