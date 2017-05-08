#pragma once
#include "Nivel1.h"
#include "Trigger.h"
#include "TextCb.h"
class Tutorial2 :
	public Nivel1
{
public:
	Tutorial2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz);
	virtual ~Tutorial2();
	virtual void onKeyUp(char k);
	virtual void callback();
	virtual void update();
private:
	bool change;
	bool firsTime;
};

