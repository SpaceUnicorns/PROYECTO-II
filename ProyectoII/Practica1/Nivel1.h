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
#include "Mochila.h"
#include "ChangeTerreno.h"

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
	std::string getActivePlayer()const{ return activePlayer; }
	void setAlpha(int i){ alpha = i; }
	void drawEquipo();

	GrafoMapa* getGrafoMapa() { return mapa; }
	void setMode(int m){ mode = (Mode)m; }
	void fadeOut(int time);
	void fadeIn(int time);
	virtual void callback();
	virtual void saveFile();
	virtual void saveMochila();

	bool visible; 
	void swVisible(){
		visible = !visible;
	}
	void resumeCabania(std:: string act, bool recogido){
		std::ifstream f;
		Mochila* m = dynamic_cast<Mochila*>(pRecolector->dameComponente("Mochila"));
		m->vaciaMochila();
		f.open("../docs/partidaGuardada/mochila.txt", std::ios::in);
		std::string s; char stash;
		while (!f.eof() && !f.fail()){
			f >> s;
			if (!f.fail()){
				f.get(stash); f.get(stash); f.get(stash);
				int cant; f >> cant;
				if (cant >0)m->newItem(s, cant);
			}
		}
		f.close();
		if (!recogido){
			cabVisitadas[lastCabVisited].visitadas = false;

		}
		if (activePlayer != act) swPlayer();
		saveMochila();
		reproduceMusica("Bosque", false);
		reproduceAmb("Viento", false);
	}
	void visitaCab(int i){
		lastCabVisited = i;
	}
	void setVectCab(int i, bool x){ cabVisitadas[i].visitadas = x; }
	int getLastcabVisited(){ return lastCabVisited; }
	void loadTriggerInfo();
	std::vector<int>& getTriggerInfo() { return infoTriggers; }
protected:
	
	struct Cab{
		bool visitadas;
		int obj;
	};
	int lastCabVisited;
	int numCab;
	std::vector<Cab> cabVisitadas;
	std::vector<int> infoTriggers;
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


class SoundTrigger :
	public Componente
{
public:
	SoundTrigger(ObjetoJuego* ent) : Componente(ent){
		reacciona = false;
		pObj = dynamic_cast<Trigger*>(ent);
	};
	virtual ~SoundTrigger(){};
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
};
