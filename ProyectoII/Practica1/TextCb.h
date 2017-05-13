#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Trigger.h"
class TextCb :
	public Componente
{
public:
	TextCb(ObjetoJuego* ent, std::string s);
	virtual ~TextCb();
	virtual void callback();
	virtual void update();
	virtual void draw();
	
protected:

	void cargaDialogo();


	std::string archivo;
	int state;
	SDL_Rect textBox;
	SDL_Rect font;
	Trigger* pObj;
	SDL_Color colorZenia;
	SDL_Color colorLyov;
	std::string default, frase, active;
	std::ifstream f; std:: vector<std:: string> aux;
	int cont, cont2;
	int timer, timer2, delay;
	bool reacciona;
	int firstTime;
	EstadoPG *estadoAux;
};

