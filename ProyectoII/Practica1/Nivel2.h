#pragma once
#include "Nivel1.h"
class Nivel2 :
	public Nivel1
{
public:
	Nivel2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool firstT = true);
	virtual ~Nivel2();
	virtual void callback();
	virtual void update(int delta);
	virtual void cargaTriggers();
private:
	Trigger* TriggerLevel1;
	Trigger* TriggerCabania;
	bool change;
	bool firsTime;
};

