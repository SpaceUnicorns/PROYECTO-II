#pragma once
#include "Fuente.h"
#include "SDL.h"  // Para utilizar SDL
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>  
class TexturasSDL
{

private:
	int w, h;
	SDL_Texture* pTexture;

public:
	TexturasSDL();
	~TexturasSDL();

	Fuente font;

	void draw(SDL_Renderer*, SDL_Rect const& rect, Uint8 alpha = 255);
	void draw(SDL_Renderer* prenderer, SDL_Rect const& rectAnim, SDL_Rect& rect, Uint8 alpha= 255);
	void loadFromText(SDL_Renderer* pRenderer, const std::string text, SDL_Color color);
	void loadFuente(std::string nombre, int tamaño);
	void setBlendMode(SDL_BlendMode blending);
	int getW();
	int getH();
	void load(SDL_Renderer* pRenderer, std::string const& nombArch);			// : Carga la imagen del archivo.En caso de
	//error lo muestra y devuelve false, y en otro caso genera la textura.Cuidado con la anterior textura.



	//bool load(SDL_Renderer* pRenderer, std:: string const& nombArch, SDL_Color const& colKey); //Una vez cargado el archivo, y antes de generar la textura, pone el color colKey transparente.

	//Puedes definir una función static SDL_Surface* load(string nombreArchivo) para cargar el	archivo.
};

