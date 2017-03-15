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
	bool reaccionando(){ return reacciona; }
	void setReacciona(bool x){ reacciona = x; }
	void setTriggerDim(int h, int w){ rect.h = h; rect.w = w; }
protected:
	bool reacciona;
	bool triggered;
	Componente* cb; //Callback;
	Cazador* tgCazador;
	Recolector* tgRecolector;
	
};

