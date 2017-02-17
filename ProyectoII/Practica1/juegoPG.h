#pragma once
#include "ObjetoJuego.h"
#include "TexturasSDL.h"
#include <vector>
#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include <string>
#include "SDL_mixer.h"
#include <stack>
#include <typeinfo>
#include "EstadoJuego.h"
enum Texturas_t { TMenu, TFondo, TBotonJ, TBotonS, TBotonM, TBotonV, TTileSet, TCazador };

class juegoPG
{
public:
	juegoPG();
	~juegoPG();
	void run();

	//Atributos-------------------------------------------------------------------------------------------
	std::stack<EstadoJuego*> estados;
	//Métodos****************************************************************************************************************************
	void setSalir(){ exit = true; }
	TexturasSDL* getFuente(){ return fuente; }
	TexturasSDL* getTextura(Texturas_t et) const { return vecTexturas[et]; }
	SDL_Renderer* getRender() const { return pRender; }
	void getMousePos(int & mpx, int & mpy) const {
		mpx = pmx; mpy = pmy;
	}
	
private:
	SDL_Event e;
	std::vector<TexturasSDL*> vecTexturas;

	
	SDL_Window * pWin;        //The window we'll be rendering to
	SDL_Renderer * pRender;   //The renderer by the window  
	SDL_Texture *pTexture;    //The image we will load and show on the screen
	SDL_Color *pColor;
	SDL_DisplayMode pMode;

	int SCREEN_WIDTH = 1024;//640;   //Screen dimension
	int SCREEN_HEIGHT = 768;//480;  //Screen dimension

	int pmx, pmy;
	bool exit;
	TexturasSDL* fuente;
	

	//Métodos ------------------------------------------------------------------------------------------------------------------------------------------
	
	void initMedia();									// carga las texturas en el vector de texturas (fuente y música) 
	void freeMedia();

	//Métodos práctica 1------------------------------------------------------------------------------------------------------------------------------------------

	void initSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);	    // : Inicia el renderizador.En caso de error, muestra un mensaje y deja todos los atributos con valores nulos.
	void closeSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);    // : Libera los atributos iniciados en initSDL.
	void render() const;												// : Limpia el buffer, pide a todos los globos que se dibujen y lo muestra.
	void onClick();														// : Pide a los globos que comprueben si lo han pinchado(máximo uno) y actualiza el número de globos que quedan activos y los puntos obtenidos al pinchar globos.
	//void update();														// : Pide a todos los globos que actualicen su estado, y actualiza el número de globos que quedan activos.
	void handle_event();												// : Comprueba si se ha producido el evento SDL_Quit o el evento soltar el botón izquierdo del ratón.Para el caso SDL_Quit, ejecuta onExit().En el otro caso, ejecuta onClick(), pasando como argumentos la posición del ratón.
	void onExit();
};

