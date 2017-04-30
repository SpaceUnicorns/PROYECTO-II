#pragma once
#include "Nivel1.h"
class Tutorial :
	public Nivel1
{
public:
	Tutorial(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz);
	virtual ~Tutorial();
	virtual void onKeyUp(char k);
	virtual void callback();
	virtual void update();
private:
	bool change;
	bool firsTime;
};


