#pragma once
#include "Nivel1.h"
class Cabania :
	public Nivel1
{
public:
	Cabania(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std:: string act);
	virtual ~Cabania();
	virtual void callback();
	virtual void update();
	virtual void draw();
private:
	bool change;
	bool firsTime;
};

