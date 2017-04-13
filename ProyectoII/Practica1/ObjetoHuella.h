#pragma once
#include "ObjetoPG.h"

class Huella;
class ObjetoHuella :
	public ObjetoPG
{
public:
	ObjetoHuella( int ind, Componente* comp, juegoPG * juego, int px, int py);
	~ObjetoHuella();
	virtual void draw();
	virtual void update();

private:
	Huella* componente;
	int timer, indice;
};

