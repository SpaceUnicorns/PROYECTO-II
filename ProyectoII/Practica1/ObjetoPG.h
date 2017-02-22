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
	virtual void newComponente(Componente* comp, std:: string const & name);
	virtual void deleteComponente(std::string const & name);
	virtual bool encuentraComponente(std::string const & name);
	virtual void setRect(int incrX, int incrY){ rect.x += incrX; rect.y += incrY; }
	virtual SDL_Rect getRect(){ return rect; }
	virtual juegoPG* getPJuego(){ return pJuego; }
	virtual  SDL_Rect getColisionBox(){ return rect; };
	//Animacion-------------------------------------------
	virtual void changeAnimV(int fila) { anim.y = anim.h * fila; } // coloca la 'j'
	virtual void changeAnimH() { anim.x += anim.w; if (anim.x >= anim.w*6) anim.x = 0; } // coloca la 'i'
	

protected: 
	ObjetoPG(juegoPG * juego, int px, int py);
	//Atributos-------------------------------------------
	bool activo;
	std::map <std::string, Componente*> mapaComponentes; 
	juegoPG * pJuego;
	Texturas_t et;
	SDL_Rect rect;
	SDL_Rect anim;
};

