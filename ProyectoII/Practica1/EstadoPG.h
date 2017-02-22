#pragma once
#include "EstadoJuego.h"
#include "juegoPG.h"
#include "ObjetoJuego.h"
#include <vector>
#include <map>
#include "fmod.hpp"
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
	virtual void drawFont();
	void reproduceFx(std::string fx, int x, int y, float wet);
	void reproduceMusica(std::string music, bool fade);
	void paraMusica(std::string music, bool fade);
	void reproduceAmb(std::string amb, bool fade);
	void paraAmb(std::string amb, bool fade);
	virtual void onKeyUp(char k){};
	virtual void onKeyDown(char k){};

protected: 
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
	FMOD::ChannelGroup* reverbGroup;
	FMOD::ChannelGroup* mainGroup;
	FMOD::DSP* reverbUnit;
	FMOD::DSP* channelHead;
	FMOD::DSPConnection* reverbConnectionfx1, *reverbConnectionfx2, *reverbConnectionfx3, *reverbConnectionfx4, *reverbConnectionamb1, *reverbConnectionamb2;

	int cMusic;
	int cAmb;
	FMOD::Channel   *cfx1 = 0, *cfx2 = 0, *cfx3 = 0, *cfx4 = 0, *camb1 = 0, *camb2 = 0, *cmusic1 = 0, *cmusic2 = 0;
std::vector <Tile> vecTile;     //Vector de tiles para dibujar el mapa
	std:: vector <Colision> vecCol;  //Vector de colisiones
	juegoPG* pJuego;
	Texturas_t et;
	SDL_Rect fondo;
	SDL_Color colorFuente;
	int contPuntos;
	std::vector<ObjetoJuego*> vecObj;
	std::map<std::string, FMOD::Sound*> vfx;
	std::map<std::string, FMOD::Sound*> vmusic;

};

