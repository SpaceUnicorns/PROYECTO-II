#pragma once
#include "Enemigo.h"
class Lobo :
	public Enemigo
{
public:

	Lobo(juegoPG *juego, Cazador* hunter, Recolector* collector, GrafoMapa* mapa, int px, int py);
	virtual ~Lobo();
	virtual void draw();
	//virtual void update();
	virtual void setColisionBox(int w, int h) { static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->setDimBox(w, h); }
	virtual void setEstado(EstadoEnemigo est);
};

