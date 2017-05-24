#pragma once
#include "ObjetoJuego.h"
#include <SDL.h>
#include "EstadoPG.h"
enum Direc { Up, dDS, Right, dDI, Down, dII, Left, dIS, Default };
class Componente
{
public:

	Componente(ObjetoJuego *pEnt)
	{
		pEntidad = pEnt;
		activo = true;
		start();
	}

	virtual ~Componente()
	{
	}
	//Métodos-----------------------------------------------------------
	virtual void callback(){};
	virtual void draw(){ };
	virtual void lateDraw(){};
	virtual void update(int delta){};
	virtual void start(){};
	virtual void lateUpdate(int delta){};
	virtual bool isAble(){ return activo; }
	virtual void awake(){};
	virtual void sleep(){};
	virtual void swAble(){ 
		if (activo) sleep();
		else awake();
		activo = !activo; 
	}
	//Atributos------------------------------------------------------------
protected: 

	ObjetoJuego *pEntidad;
	bool activo;
};

