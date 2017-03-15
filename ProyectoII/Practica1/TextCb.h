#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Trigger.h"
class TextCb :
	public Componente
{
public:
	TextCb(ObjetoJuego* ent);
	virtual ~TextCb();
	virtual void callback();
	virtual void update();
	virtual void draw();
protected:
	SDL_Rect textBox;
	SDL_Rect font;
	Trigger* pObj;
	std::ifstream f; std:: vector<std:: string> aux;
	int cont;
	int timer;
	bool once;
};

