#pragma once
#include "Nivel1.h"
class Cabania :
	public Nivel1
{
public:
	Cabania(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std:: string act, bool visited, int obj = 0);
	virtual ~Cabania();
	virtual void callback();
	virtual void update(int delta);
	virtual void draw();
	virtual void swPlayer();
	virtual void onKeyUp(char k);
private:
	SDL_Color color;
	SDL_Rect font;
	bool change;
	bool firsTime;
};

