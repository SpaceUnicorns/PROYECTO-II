#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class ColisionBox;

class MovimientoP :
	public Componente
{
public:
	MovimientoP(ObjetoJuego* ent);
	virtual ~MovimientoP();

	//Métodos--------------------------------------------------
	virtual void update();

	ObjetoPG* info = nullptr;
	ObjetoPG *pObj;
	Direc getDir(){ return direccion; }
private:
	
	bool moviendose;
	int framerate, contPasos = 0;
	Punto nextPos; 
	ColisionBox * pCBox;
	EstadoPG* pEstado;
	Direc direccion;
	//Direc direccion;
	//Funciones----------------------------------------------------------------------
	/*bool isColiding(Punto const & P);
	bool inTriangle(TrianguloBorde  tr, Punto const & P); //Calcula si un punto está dentro del triangulo.
	int triangleOrientation(TrianguloBorde const &tr);*/
};

