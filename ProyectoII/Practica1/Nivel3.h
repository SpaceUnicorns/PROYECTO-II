#pragma once
#include "Nivel1.h"
class Nivel3 :
	public Nivel1
{
public:
	Nivel3(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool firstT = true);
	virtual ~Nivel3();
	virtual void callback();
	virtual void update();
	virtual void cargaTriggers();
private:
	bool change;
	bool firsTime;
};

