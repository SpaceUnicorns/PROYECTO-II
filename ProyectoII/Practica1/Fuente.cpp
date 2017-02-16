#include "Fuente.h"
#include "SDL_ttf.h"
#include "Error.h"

Fuente::Fuente()
{
	recFont.h = 50;
	recFont.w = 70;
	recFont.x = 25;
	recFont.y = 25;
}


Fuente::~Fuente()
{
}

SDL_Surface* Fuente::textSolid(std::string texto, SDL_Color color) {
	if (!pFont)throw ELoadFont("Font could not be loaded!");
	return TTF_RenderText_Solid(pFont, texto.c_str(), color);
}

void Fuente::load(std::string nombre, int tamano){
	pFont = TTF_OpenFont(nombre.c_str(), tamano);
	if (!pFont) throw ELoadFont("Font could not be loaded!");
}