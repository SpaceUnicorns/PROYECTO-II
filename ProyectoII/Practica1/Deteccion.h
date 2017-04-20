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
	bool compruebaRadio(SDL_Rect target, float& distancia);
	bool cazadorIn(float& dist);
	bool recolectorIn(float& dist);
	void acechar();
	bool inTriangle(TrianguloBorde tr, Punto const & P);
	int triangleOrientation(TrianguloBorde const & tr);

private:
	Enemigo* enemy;
	TrianguloBorde vista;
	float radio;
	bool detectado;
	int contAtrapado;
	int contAtaque;
	int dirAtaque; // 0 arriba y sigue las agujas del reloj
};

