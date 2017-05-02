#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "ColisionBox.h"

class AtaqueZ :
	public Componente, public ObjetoPG
{
public:
	AtaqueZ(ObjetoJuego* entidad, juegoPG * juego, int px, int py);
	~AtaqueZ();

	void Attack();
	void update();
	int getX() { pObj->getRect().x; };
	int getY() { pObj->getRect().y; };
	int getW() { pObj->getRect().w; }
	void setAttack() { atacando = true; }
private:
	SDL_Rect rect;
	ObjetoPG* pObj;
	ColisionBox* box;
	bool atacando;
};

