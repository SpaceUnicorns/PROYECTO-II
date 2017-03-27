#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
#include "TrampaComponente.h"
class TrampaAbierta :
	public ObjetoPG
{
public:
	TrampaAbierta(juegoPG * juego, int px, int py);
	virtual ~TrampaAbierta();
	virtual void draw();
};

