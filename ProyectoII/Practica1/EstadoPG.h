#pragma once
#include "EstadoJuego.h"
#include "juegoPG.h"
#include "ObjetoJuego.h"
#include <vector>
#include <map>
#include "fmod.hpp"
#include <fstream>
#include <iostream>


 struct Punto{
	int x, y;
};
 struct TrianguloBorde{
	Punto A, B, C;
};

class EstadoPG :
	public EstadoJuego
{
public:
	EstadoPG(juegoPG* jug,int puntos);
	virtual ~EstadoPG();
	virtual void draw();

	virtual void update();
	virtual void onClick();
	virtual void onOver();
	virtual void drawFont(SDL_Rect rect, std::string const & s, SDL_Color color = {34,245,55,1});// , int g = 245, int b = 55, int a = 1);
	virtual void reproduceFx(std::string fx, float x, float y, float wet);
	virtual void reproduceMusica(std::string music, bool fade);
	virtual void paraMusica(std::string music, bool fade);
	virtual void reproduceAmb(std::string amb, bool fade);
	virtual void paraAmb(std::string amb, bool fade);
	virtual void onKeyUp(char k){};
	virtual void onKeyDown(char k){};
	virtual std::vector <TrianguloBorde> & getVectBordes(int layer = 1) {
		if (layer == 1)return vectBordes;
		else if (layer == 2) return vectBordes2;
	}
	virtual std::vector <ObjetoJuego*> & getVectObj(int i = 1) {
		if (i == 1) return vecObj;
		else if (i == 2) return vecObjOverL;
	}
	virtual std::vector <ObjetoJuego*> & getVecTriggers() {
		return vecTriggers;
	}
	// Audio
	void cargarAssetsAudio(std::string txt, char tipo);
	void cargarAudio(std::string irPath);

	virtual SDL_Rect getCamara()const{ return camara; }
	virtual void setCamara(int x, int y){ camara.x = x; camara.y = y; }
	void setLayerCaz(int i){
		layerCaz = i;
	}
	void setLayerRec(int i){
		layerRec = i;
	}
	int getLayer(){ return activeLayer; }
protected: 
	SDL_Rect camara;
	struct Tile {
		int x, y;
		int capa;
		SDL_Rect rectTileset;     //Contiene el rectangulo del Tileset que se quiere dibujar.
	};
	
	struct Colision
	{
		SDL_Rect collider;
		int capa;
	};



	std::vector <Tile> vecTile, vecTile2;     //Vector de tiles para dibujar el mapa
	std::vector<TrianguloBorde> vectBordes, vectBordes2;

	std:: vector <Colision> vecCol;  //Vector de colisiones
	juegoPG* pJuego;
	Texturas_t et;
	SDL_Rect fondo;
	int contPuntos;
	int layerCaz, layerRec, activeLayer;
	// Necesario para la gestion de la reverb y el audio
	FMOD::ChannelGroup* reverbGroup;
	FMOD::ChannelGroup* mainGroup;
	FMOD::DSP* reverbUnit;
	FMOD::DSP* channelHead;
	FMOD::DSPConnection* reverbConnectionfx1, *reverbConnectionfx2, *reverbConnectionfx3, *reverbConnectionfx4, *reverbConnectionamb1, *reverbConnectionamb2;
	int cMusic;
	int cAmb;
	FMOD::Channel   *cfx1 = 0, *cfx2 = 0, *cfx3 = 0, *cfx4 = 0, *camb1 = 0, *camb2 = 0, *cmusic1 = 0, *cmusic2 = 0;
	std::vector<ObjetoJuego*> vecObj, vecObjOverL;
	std::vector<ObjetoJuego*>vecTriggers;
	std::map<std::string, FMOD::Sound*> vfx;
	std::map<std::string, FMOD::Sound*> vmusic;

};

