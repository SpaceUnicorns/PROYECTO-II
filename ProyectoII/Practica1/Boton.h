#pragma once
#include "ObjetoPG.h"
#include "juegoPG.h"
class Boton :
	public ObjetoPG
{
public: // private???
	typedef void CallBack_t(juegoPG* jg);
protected:
	CallBack_t * cb;
public:
	Boton(juegoPG * juego, int px, int py, Texturas_t textura, CallBack_t* callback);
	virtual ~Boton();

	//Funciones------------------------------------------------------------------------------------------------------------------
	virtual void draw();
	virtual bool onClick();
	virtual void update(int delta){};
	virtual bool onOver();
private:
	SDL_Rect anim;
};

