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
	bool compruebaRadio(SDL_Rect target, int radio){
		Punto centro; centro.y = target.h / 2 + target.y; centro.x = target.w / 2 + target.x;
		return pow(x - centro.x, 2) + pow(y - centro.y, 2) <= pow(radio, 2);
	}

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

	virtual void update(int delta);
	virtual void lateUpdate(int delta);

	virtual void nieve();
	virtual void setAutoSnow() { autoSnow = true; };

	virtual void onClick();
	virtual void onOver();
	virtual void cargaMapa(std::string txt, std::vector<char>& mapa);
	virtual void awake(){}; //Se llama al volver de otro estado superpuesto
	virtual void drawFont(SDL_Rect rect, std::string const & s, SDL_Color color = {34,245,55,1});// , int g = 245, int b = 55, int a = 1);
	virtual void reproduceFx(std::string fx, float x, float y, float wet);
	virtual void reproduceMusica(std::string music, bool fade);
	virtual void paraMusica(std::string music, bool fade);
	virtual void reproduceAmb(std::string amb, bool fade);
	virtual void paraAmb(std::string amb, bool fade);
	virtual void onKeyUp(char k){};
	virtual void onKeyDown(char k){};
	virtual void borrarObj(ObjetoJuego* o){ vecBorrar.push_back(o); };
	virtual void updateBorrarObj();
	virtual std::vector <TrianguloBorde> & getVectBordes() {
		return vectBordes;
	}
	virtual std::vector <ObjetoJuego*> & getVectObj() {
		return vecObj;
	}
	virtual std::vector <ObjetoJuego*> & getVecTriggers() {
		return vecTriggers;
	}
	virtual void eraseVectObj(ObjetoJuego* pnt) {
		std::vector<ObjetoJuego*>::iterator it;
		for (it = vecObj.begin(); it != vecObj.end(); it++)
			if ((*it) == pnt) {
				delete * it;
				it = vecObj.erase(it);
			}
	}

	// Audio
	void cargarAssetsAudio(std::string txt, char tipo);
	void cargarAudio(std::string irPath);

	virtual SDL_Rect getCamara()const{ return camara; }
	virtual void setCamara(int x, int y){
		camara.x = x; camara.y = y; }

	struct Tile {
		int x, y;
		int capa;
		SDL_Rect rectTileset;     //Contiene el rectangulo del Tileset que se quiere dibujar.
	};

private:
	SDL_Rect title;
	bool autoSnow;

protected: 
	SDL_Rect animNieve1, animNieve2;
	SDL_Rect camara;
	struct Colision
	{
		SDL_Rect collider;
		int capa;
	};



	std::vector <Tile> vecTile;     //Vector de tiles para dibujar el mapa
	std::vector<TrianguloBorde> vectBordes;

	std:: vector <Colision> vecCol;  //Vector de colisiones
	juegoPG* pJuego;
	Texturas_t et;
	SDL_Rect fondo;
	int contPuntos;
	// Necesario para la gestion de la reverb y el audio
	FMOD::ChannelGroup* reverbGroup;
	FMOD::ChannelGroup* mainGroup;
	FMOD::DSP* reverbUnit;
	FMOD::DSP* channelHead;
	FMOD::DSPConnection* reverbConnectionfx1, *reverbConnectionfx2, *reverbConnectionfx3, *reverbConnectionfx4, *reverbConnectionamb1, *reverbConnectionamb2;
	int cMusic;
	int cAmb;
	std::vector<FMOD::Channel*> cfx;
	std::vector<FMOD::DSPConnection*> reverbConnectionfx;
	FMOD::Channel   *cfx1 = 0, *cfx2 = 0, *cfx3 = 0, *cfx4 = 0, *camb1 = 0, *camb2 = 0, *cmusic1 = 0, *cmusic2 = 0;
	std::vector<ObjetoJuego*> vecObj;
	std::vector<ObjetoJuego*> vecBorrar;
	std::vector<ObjetoJuego*>vecTriggers;
	std::map<std::string, FMOD::Sound*> vfx;
	std::map<std::string, FMOD::Sound*> vmusic;

};

