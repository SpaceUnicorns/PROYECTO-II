#pragma once
#include "ObjetoPG.h"
#include "Cazador.h"
#include "Recolector.h"

class Nivel1;
class Trigger :
	public ObjetoPG
{
public:
	Trigger(juegoPG * juego, int px, int py, Cazador* tgC, Recolector* tgR, int indice_ = 0, bool isCab = false);
	virtual ~Trigger();
	virtual void draw();
	virtual void update(int delta);
	bool isTriggering(){ return triggered; }
	void swTriggered(){ triggered = !triggered; }
	void setCallback(Componente* com){ cb = com; }
	std::string getCallback(){ return typeid(cb).name(); }
	void setTriggered(bool x){ triggered = x; }
	bool reaccionando(){ return reacciona; }
	void setReacciona(bool x){ reacciona = x; }
	void setTriggerDim(int h, int w){ rect.h = h; rect.w = w; }
	ObjetoPG* getCausante(std::string obj) { if (obj == "Cazador")return tgCazador; else if (obj == "Recolector")return tgRecolector; }
	void lateDraw();
	int indice;
	int getIndice(){ return indice; }

protected:
	bool firstDraw;
	Nivel1* level;
	bool isCabania;
	bool firsTime;
	bool reacciona;
	bool triggered;
	Componente* cb; //Callback;
	Cazador* tgCazador;
	Recolector* tgRecolector;
	
};

