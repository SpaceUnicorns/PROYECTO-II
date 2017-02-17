#pragma once
#include "EstadoJuego.h"
#include "juegoPG.h"
#include "ObjetoJuego.h"
#include <vector>

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

std::vector <Tile> vecTile;     //Vector de tiles para dibujar el mapa
	std:: vector <Colision> vecCol;  //Vector de colisiones
	juegoPG* pJuego;
	Texturas_t et;
	SDL_Rect fondo;
	SDL_Color colorFuente;
	int contPuntos;
	std::vector<ObjetoJuego*> vecObj;

};

