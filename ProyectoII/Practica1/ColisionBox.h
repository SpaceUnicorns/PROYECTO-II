#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class ColisionBox :
	public Componente
{
public:
	ColisionBox(ObjetoJuego* ent);
	ColisionBox(ObjetoJuego* ent, SDL_Rect const & newRect, bool mov);
	virtual ~ColisionBox();
	
	
	//Atributos--------------------------------------
	
	//Metodos----------------------------------------
	virtual void update();
	virtual void draw();
	virtual void setMovible(bool mov){ movible = mov; }
	virtual bool getMovible(){ return movible; }
	virtual SDL_Rect getRectBox(){ return boxRect; }
	virtual void setRectBox(int x, int y){ boxRect.x = x; boxRect.y = y; }
	virtual void setDimBox(int w, int h){ boxRect.w = w; boxRect.h = h; }
	//Funciones------------------------------------------------------------------------------------------------------------
	int isColiding(Punto const & P, ObjetoPG* & info);

private:
	//Atributos-------------------------------------------------------
	bool movible;
	ObjetoPG* pObj;
	SDL_Rect boxRect;
	int inTriangle(TrianguloBorde  tr, Punto const & P); //Calcula si un punto está dentro del triangulo.
	int triangleOrientation(TrianguloBorde const &tr);
};

