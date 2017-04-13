#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "ObjetoHuella.h"

enum Dir { Arriba, DDS, Derecha, DDI, Abajo, DII, Izquierda, DIS, None };

class Huella :
	public Componente
{
public:
	Huella(ObjetoJuego* ent);
	virtual ~Huella();
	virtual void lateUpdate();
	virtual void update();
	virtual void draw();
	void setHuella(Dir dir);
	void quitaHuella(int ind);
private:
	Dir state;
	ObjetoPG* pObj;
	std::vector<ObjetoHuella*> vecHuellas;
	int sizeMax, it, timer;
	
};



