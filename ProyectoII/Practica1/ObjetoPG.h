#pragma once
#include "ObjetoJuego.h"
#include "SDL.h"
#include "TexturasSDL.h"
#include "juegoPG.h"
#include <map>
#include "Componente.h"
class ObjetoPG :
	public ObjetoJuego
{
public:

	virtual ~ObjetoPG();

	//Métodos
	virtual bool dentro(int x, int y)const;
	virtual void draw();
	virtual bool onClick();
	virtual bool onOver();

	virtual void update();
	virtual void start();
	virtual void lateUpdate();
	virtual bool isAble(){ return activo; }
	virtual void awake();
	virtual void sleep();
	virtual void swAble(); 




protected: 
	ObjetoPG(juegoPG * juego, int px, int py);
	//Atributos-------------------------------------------
	bool activo;
	std::map <std::string, Componente*> mapaComponentes; 
	juegoPG * pJuego;
	Texturas_t et;
	SDL_Rect rect;
};

