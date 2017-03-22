#pragma once
#include "Componente.h"
#include "Cazador.h"
#include "Recolector.h"
class Attack :
	public Componente
{
public:
	Attack(ObjetoJuego* entidad);
	virtual ~Attack();
	virtual void update();

private:
	SDL_Rect posEnemigo; //= static_cast<Enemigo*>(pEntidad)->getColisionBox();
	Punto posicion;
	ObjetoPG* info;
};

