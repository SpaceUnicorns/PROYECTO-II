#pragma once
#include "ObjetoJuego.h"
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
	virtual void update(){};
	virtual void start(){};
	virtual void lateUpdate(){};
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

