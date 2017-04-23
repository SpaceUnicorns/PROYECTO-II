#pragma once
#include "ObjetoPG.h"
enum Dir { DDS,DDI,DII,DIS, Arriba, Derecha, Abajo, Izquierda, None };

class Huella;
class ObjetoHuella :
	public ObjetoPG
{
public:
	ObjetoHuella( int dir, int ind, Componente* comp, juegoPG * juego, int px, int py);
	~ObjetoHuella();
	virtual void draw();
	virtual void update();
private:
	virtual void changeAnimV(int fila) { anim.y = anim.h * fila; } // coloca la 'j'
	virtual void changeAnimH() { anim.x += anim.w; if (anim.x >= anim.w * 6) anim.x = 0; } // coloca la 'i'
	virtual void setAnim(Dir dir);
	Huella* componente;
	int timer, indice, alpha;
};

