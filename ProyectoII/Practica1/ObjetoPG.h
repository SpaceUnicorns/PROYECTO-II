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
	virtual void lateDraw();
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
	virtual void setAbsRect(int incrX, int incrY){ absRect.x += incrX; absRect.y += incrY; }
	virtual SDL_Rect getRect(){ return rect; }
	virtual SDL_Rect getAbsRect(){ return absRect; }
	virtual juegoPG* getPJuego(){ return pJuego; }
	virtual  SDL_Rect getColisionBox(){ return rect; };
	virtual Componente* dameComponente(std::string const &s){
		if (encuentraComponente(s)) return mapaComponentes.at(s);
		else return nullptr;
	}
	//Animacion-------------------------------------------
	virtual void changeAnimV(int fila) { anim.y = anim.h * fila; } // coloca la 'j'
	virtual void changeAnimH() { anim.x += anim.w; if (anim.x >= anim.w*6) anim.x = 0; } // coloca la 'i'
	virtual Texturas_t getEnumText()const { return et; }
	bool interactuable=false;
	bool obstaculo = false;
	std::vector<std::string> nombre;
	std::vector<std::string> receta;
protected: 
	ObjetoPG(juegoPG * juego, int px, int py);
	
	//Atributos-------------------------------------------
	bool activo;
	std::map <std::string, Componente*> mapaComponentes; 
	juegoPG * pJuego;
	Texturas_t et;
	SDL_Rect rect;
	SDL_Rect absRect;
	SDL_Rect aux; //Rect auxiliar para cual quier cuenta con rectangulos (Se usa para la camara)	
	SDL_Rect anim;
};

