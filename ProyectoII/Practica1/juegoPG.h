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
#include "fmod.hpp"

enum Texturas_t {
	TMenu, TFondo, TBotonJ, TBotonS, TBotonM, TBotonV, TTileSet, TTextBox, TArbol, TCColision, TJugador, TJugador2,
	TSombra1, TMenuResaltado, TLyov, TZhenia, TEquipables, TMateriales, TCebo, TCuerda, TEnredadera, THueso, TMadera, 
	TPiedra, TTrampaCerrada, TYesca, TGris, TLuz, TNieve1, TNieve2, TLobete, TTapa, TContinuar, TOpciones, TGoToMenu,
	TCabaña
};

class juegoPG
{
public:

	juegoPG();
	~juegoPG();
	void run();

	//Atributos-------------------------------------------------------------------------------------------
	FMOD::System     *system;
	FMOD_RESULT       result;
	std::stack<EstadoJuego*> estados;
	struct Input{
		bool izquierda, arriba, derecha, abajo, dDS, dDI, dIS, dII, sw, e, enter, follow; //Diagonal Derecha Superior, Diegonal Izquierda SUperior;
	};
	Input input;

	//Métodos****************************************************************************************************************************
	void setSalir(){ exit = true; }
	TexturasSDL* getFuente(){ return fuente; }
	TexturasSDL* getTextura(Texturas_t et) const { return vecTexturas[et]; }
	SDL_Renderer* getRender() const { return pRender; }
	void getMousePos(int & mpx, int & mpy) const {
		mpx = pmx; mpy = pmy;
	}

	TexturasSDL* getPag(int n) const { return vecPaginas[n]; };
	bool hasExit(){ return exit; }
	int getScreenWidth(){ return SCREEN_WIDTH; }
	int getScreenHeight(){ return SCREEN_HEIGHT; }
	EstadoJuego* getEstadoActual() { return estados.top(); }
	int getVida(){ return vida; }

	//Este metodo cambia la vida y el rect de la niebla oscura
	void cambiaVida(int cambio);
	SDL_Rect getNieblaRect() { return nieblaRect; }

private:
	SDL_Event e;
	
	std::vector<TexturasSDL*> vecTexturas;
	std::vector<TexturasSDL*> vecPaginas;
	
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
	//void freeMedia();

	//Métodos práctica 1------------------------------------------------------------------------------------------------------------------------------------------

	void initSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);	    // : Inicia el renderizador.En caso de error, muestra un mensaje y deja todos los atributos con valores nulos.
	void closeSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);    // : Libera los atributos iniciados en initSDL.
	void render() const;												// : Limpia el buffer, pide a todos los globos que se dibujen y lo muestra.
	//void onClick();														// : Pide a los globos que comprueben si lo han pinchado(máximo uno) y actualiza el número de globos que quedan activos y los puntos obtenidos al pinchar globos.
	//void update();														// : Pide a todos los globos que actualicen su estado, y actualiza el número de globos que quedan activos.
	void handle_event();												// : Comprueba si se ha producido el evento SDL_Quit o el evento soltar el botón izquierdo del ratón.Para el caso SDL_Quit, ejecuta onExit().En el otro caso, ejecuta onClick(), pasando como argumentos la posición del ratón.
	void onExit();

	//Cosas de los personajes
	int vida;
	SDL_Rect nieblaRect;
};

