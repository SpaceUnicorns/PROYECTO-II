#pragma once
#include "Componente.h"
class Deteccion :
	public Componente
{
public:
	Deteccion(ObjetoJuego* entidad, float radio);
	virtual ~Deteccion();
	virtual void update();
	bool compruebaRadio(SDL_Rect target, float& distancia);
	bool cazadorIn(float& dist);
	bool recolectorIn(float& dist);

private:
	float radio;
	bool detectado;
};

