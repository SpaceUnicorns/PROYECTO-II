#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class ColisionBox :
	public Componente
{
public:
	ColisionBox(ObjetoJuego* ent);
	ColisionBox(ObjetoJuego* ent, SDL_Rect const & newRect);
	virtual ~ColisionBox();
	//Atributos--------------------------------------
	SDL_Rect boxRect;
	ObjetoPG* pObj;

	//Metodos----------------------------------------
	virtual void update();
	virtual void draw();
};

