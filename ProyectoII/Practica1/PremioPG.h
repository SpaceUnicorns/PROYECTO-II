#pragma once
#include "ObjetoPG.h"
class PremioPG :
	public ObjetoPG
{
public:

	PremioPG(juegoPG * juego, int px, int py);
	virtual ~PremioPG();
//Metodos--------------------------------------------------------------------------------------------------
	void creaPremio();
	bool esVisible();
	virtual void draw();
	virtual void update();
	virtual bool onClick();
	int damePuntos(){ return puntos; }

private:
	SDL_Rect anim;
	int contTurnos, contUpdate;
	bool visible;
	int puntos;
	const static int PP = 25;
};

