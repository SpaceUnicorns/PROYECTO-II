#pragma once
#include "ObjetoPG.h"
#include "Cazador.h"
#include "Recolector.h"
class Trigger :
	public ObjetoPG
{
public:
	Trigger(juegoPG * juego, int px, int py, Cazador* tgC, Recolector* tgR);
	virtual ~Trigger();
	virtual void draw();
	virtual void update();
	bool isTriggering(){ return triggered; }
	void swTriggered(){ triggered = !triggered; }
	void setCallback(Componente* com){ cb = com; }
	void setTriggered(bool x){ triggered = x; }
protected:
	bool triggered;
	Componente* cb; //Callback;
	Cazador* tgCazador;
	Recolector* tgRecolector;
	
};

