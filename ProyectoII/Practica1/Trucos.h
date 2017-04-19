#pragma once
#include "EstadoPG.h"
#include "Recolector.h"
class Trucos :
	public EstadoPG
{
public:
	Trucos(juegoPG*jug, Recolector* pRec);
	virtual ~Trucos();
	virtual void draw();
	virtual void onKeyUp(char k);
private:
	void volver();
	Recolector* pRecolector;
	SDL_Rect font;
	SDL_Color fuente;
	bool firstTime;
	void desbloquea();
	std::string codigo;
	std::string renderCodigo;
	TexturasSDL * fondo;
	SDL_Rect rFondo, rect, boton;
};

