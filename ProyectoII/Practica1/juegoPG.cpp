#include "juegoPG.h"
using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 

//---------------------------------------------------------------------------------------------------------------
#include "GameOver.h"
#include "Pausa.h"
#include "MenuPG.h"
#include "Nivel1.h"
#include <typeinfo>
#include "Error.h"

juegoPG::juegoPG()
{
	srand(1);
	
	pWin = nullptr;  	//The window we'll be rendering to
	pRender = nullptr;   //The renderer by the window
	try{
		initSDL(pWin, pRender);
	}
	catch (EInitMixer &msg){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.mensaje().c_str(), nullptr); }
	catch (EInitTTF &msg){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.mensaje().c_str(), nullptr); }

	vecTexturas.resize(8);
	initMedia();	
	
	estados.push(new MenuPG(this,0));

}
void juegoPG::initMedia(){
	
	//Cargamos las texturas
	std::string str = "Textura";
	for (unsigned int i = 0; i < vecTexturas.size(); i++){
		vecTexturas[i] = new TexturasSDL;
		vecTexturas[i]->load(pRender, "..\\bmps\\" + (str += to_string(i + 1)) + ".png");
		str = "Textura";
	}
	//Cargamos la fuente
	try{
		fuente = new TexturasSDL;
		fuente->loadFuente("..\\bmps\\font.ttf", 50);
		//Inicializamos el color para el texto
		
	}
	catch (ELoadFont &msg){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.mensaje().c_str(), nullptr); }
	
}

juegoPG::~juegoPG()
{
	closeSDL(pWin, pRender);

	for (unsigned int i = 0; i < vecTexturas.size(); i++)
		delete vecTexturas[i];

	delete fuente;
	while (!estados.empty()){
		delete estados.top();
		estados.pop();
	}
	vecTexturas.clear();
	
}
//--------------------------------------------------------------------------------------------------------------------
void juegoPG::run(){
		Uint32 msUpdate = 150;
		std::cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		render();
		handle_event();
		while (!exit) {
				if (SDL_GetTicks() - lastUpdate >= msUpdate) { // while(elapsed >= MSxUpdate)
					estados.top()->update();
					lastUpdate = SDL_GetTicks();
				}
			
				render();
			
			handle_event();
		}
		if (exit) cout << "EXIT \n";
}
//----------------------------------------------------------------------------------------------------------------------
void juegoPG::handle_event(){
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT){
			onExit();
		}
		else if (e.type == SDL_KEYUP){
			if (e.key.keysym.sym == SDLK_ESCAPE){
				estados.top()->onKeyUp('S');
			}
			else if (e.key.keysym.sym == SDLK_p){
				estados.top()->onKeyUp('p');
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				//cout << "CLICK";
				pmx = e.button.x;
				pmy = e.button.y;
				estados.top()->onClick();
			}
		}
		else if (e.type == SDL_MOUSEMOTION){
			pmx = e.button.x;
			pmy = e.button.y;
			estados.top()->onOver();
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------
void juegoPG::initSDL(SDL_Window* &pWindow, SDL_Renderer* &pRenderer) {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		throw EInitSDL("SDL could not initialize!");
	}
	else {
		int x = SDL_GetCurrentDisplayMode(0,&pMode);
		if (x == 0){
			SCREEN_HEIGHT = pMode.h; 
			SCREEN_WIDTH = pMode.w;
		}
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWindow = SDL_CreateWindow("Ghost balloons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (pWindow == nullptr){
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			throw EInitWindow("Window could not be created!");
		}
		else {
			//Get window surface:
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
			if (pRenderer == nullptr){
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				throw EInitRender("Renderer could not be created!");
			}
		}
	}

	if (TTF_Init() < 0){			//Inicializamos la libreria  de fuentes
		cout << "TTF could not be initialized! \nTTF_Error: " << TTF_GetError() << '\n';
		throw EInitTTF("Font could not be initialized!, There will be no marker");
	}
	int initted = Mix_Init(27);
	if (initted & 27 != 27){
		cout << "Mixer could not be initialized! \nMixer_Error: " << Mix_GetError() << '\n';
		throw EInitMixer("Sound could not be initialized!, The Game will have no Sound");
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		cout << "Mixer (OpenAudio) could not be initialized! \nMixer_Error: " << Mix_GetError() << '\n';
		throw EInitMixer("Sound could not be initialized!, The Game will have no Sound");
	}

	
}
//-----------------------------------------------------------------------------------------------------------------

void juegoPG::closeSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer) {

	Mix_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(pRenderer);
	pRenderer = nullptr;

	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;

	SDL_Quit();
}
//--------------------------------------------------------------------------------------------------------------------------

void juegoPG::render() const {

	//Clear the window to background color 
	SDL_RenderClear(pRender);

	//llamar al draw de envima de la pila
	estados.top()->draw();

	//Show the window
	SDL_RenderPresent(pRender);
}
void juegoPG::onExit(){
	exit = true;
}

