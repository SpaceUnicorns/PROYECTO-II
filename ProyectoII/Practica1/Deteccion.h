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
	void setVista(int dir);
	void preparaAtaque(int target/*0 caz 1 rec*/);
private:
	Enemigo* enemy;
	TrianguloBorde vista;
	float radio;
	bool detectado;
	int cont;
	int rnd;
	ObjetoPG* direccionAux;
	int ultAtaque;
	int vagar, contVagar;
	int dirAtaque; // 0 arriba y sigue las agujas del reloj
};

