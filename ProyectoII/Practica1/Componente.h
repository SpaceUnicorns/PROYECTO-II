#pragma once
#include "ObjetoPG.h"
class Componente
{
public:

	Componente(ObjetoPG *pEnt)
	{
		pEntidad = pEnt;
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

	ObjetoPG *pEntidad;
	bool activo;
};

