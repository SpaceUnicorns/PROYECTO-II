#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class ColisionBox;
enum Direc {Up, dDS, Right, dDI, Down, dII, Left, dIS, Default};
class MovimientoP :
	public Componente
{
public:
	MovimientoP(ObjetoJuego* ent);
	virtual ~MovimientoP();

	//M�todos--------------------------------------------------
	virtual void update();

	ObjetoPG* info = nullptr;
	ObjetoPG *pObj;
private:
	
	int framerate = 0;
	Punto nextPos; 
	ColisionBox * pCBox;
	EstadoPG* pEstado;
	Direc direccion;
	//Direc direccion;
	//Funciones----------------------------------------------------------------------
	/*bool isColiding(Punto const & P);
	bool inTriangle(TrianguloBorde  tr, Punto const & P); //Calcula si un punto est� dentro del triangulo.
	int triangleOrientation(TrianguloBorde const &tr);*/
};

