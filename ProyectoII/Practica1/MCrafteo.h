#pragma once
#include "EstadoPG.h"
#include "Mochila.h"
#include "Equipo.h"

enum MenuState {Crafteo, Personaje, Objeto};

class MCrafteo: public EstadoPG
{
	struct coords {
		std::string name; int x; int y;
	};
public:
	MCrafteo(juegoPG*jug, int puntos, Mochila* m, Equipo* equipCaz, Equipo* equipRec);
	virtual ~MCrafteo();

	void draw();
	void update(int delta) {};
	void onKeyUp(char k);

	void animacionS();
	void animacionA();

	void comprobar(std::vector<coords> const& v);
	void craftear();
private:
	SDL_Rect pag1, pag2, sombra, rFondo, niños, recuadros, font, animEquipoCaz, animEquipoRec, rectEquipoCaz, rectEquipoRec;
	void setObjEquipo(SDL_Rect & animEquipo, int aux);
	TexturasSDL * fondo;
	SDL_Color fuente;
	int  acuD, acuI;
	int numPag, aux = 0;
	int cual=0;
	bool derecha, izquierda, flag;
	
	MenuState menuState;
	Mochila* mochila;
	Equipo* cazador;
	Equipo* recolector;
	std::vector<coords> equipables;
	std::vector<std::string> crafteo;
	std::vector<coords> materiales;
	SDL_Rect seleccion;
	int equipar; // 0 significa cazador, 1 significa recolector
	int objeto, nivelObj;
};

