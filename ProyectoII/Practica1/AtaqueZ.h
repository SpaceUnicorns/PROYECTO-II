#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class AtaqueZ :
	public Componente, public ObjetoPG
{
public:
	AtaqueZ(ObjetoJuego* entidad);
	~AtaqueZ();

	void Attack();
	void update();
	void movimiento();
private:
	SDL_Rect rect;
	bool atacando;
};

