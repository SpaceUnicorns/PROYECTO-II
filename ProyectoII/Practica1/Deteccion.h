#pragma once
#include "Componente.h"
#include "Enemigo.h"

class Deteccion :
	public Componente
{
public:
	Deteccion(ObjetoJuego* entidad, float radio);
	virtual ~Deteccion();
	virtual void update();
	bool compruebaRadio(SDL_Rect target);
	bool cazadorIn();
	bool recolectorIn();

private:
	Enemigo* enemy;
	float radio;
	bool detectado;
	int contador;
};

