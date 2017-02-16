#pragma once
#include <iostream>
#include "SDL_ttf.h"
class Fuente
{
public:
	Fuente();
	~Fuente();
	TTF_Font * pFont;
	SDL_Rect recFont;

	//Metodos
	void load(std::string text, int tamaño);
	SDL_Surface* textSolid(std::string texto, SDL_Color color);

private:
	//Atributos

};

