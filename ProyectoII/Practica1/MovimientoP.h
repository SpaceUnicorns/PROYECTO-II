#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class MovimientoP :
	public Componente
{
public:
	MovimientoP(ObjetoJuego* ent);
	virtual ~MovimientoP();

	//Métodos--------------------------------------------------
	virtual void update();

	ObjetoPG *pObj;
};

