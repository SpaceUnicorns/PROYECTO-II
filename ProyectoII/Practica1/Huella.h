#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "ObjetoHuella.h"

class Huella :
	public Componente
{
public:
	Huella(ObjetoJuego* ent);
	virtual ~Huella();
	virtual void lateUpdate();
	virtual void update();
	virtual void draw();
	void setHuella(int dir);
	void quitaHuella(int ind);
private:
	Dir state;
	SDL_Rect anim;
	ObjetoPG* pObj;
	std::vector<ObjetoHuella*> vecHuellas;
	int sizeMax, it, timer;
	
};



