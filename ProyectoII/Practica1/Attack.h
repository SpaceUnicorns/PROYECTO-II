#pragma once
#include "Enemigo.h"
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
	Enemigo* enemigo;
	Punto posicion;
	ObjetoPG* info;
	int cont;
	int conAnimacion;
};
