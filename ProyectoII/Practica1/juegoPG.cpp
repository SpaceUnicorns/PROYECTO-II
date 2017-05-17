#include "juegoPG.h"
#include "checkML.h"

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
	catch (EInitTTF &msg){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.mensaje().c_str(), nullptr); }

	vecTexturas.resize(51);
	vecPaginas.resize(6);


	initMedia();	

	//La vida de los pjs (al ser compartida va en el juego)
	vida = 300;
	nieblaRect = { 600,338,400,225 };

	estados.push(new MenuPG(this,0));
	delay = 0;

}
void juegoPG::initMedia(){
	
	//Cargamos las texturas
	std::string str = "Textura";
	for (unsigned int i = 0; i < vecTexturas.size(); i++){
		vecTexturas[i] = new TexturasSDL;
		vecTexturas[i]->load(pRender, "..\\bmps\\" + (str += to_string(i + 1)) + ".png");
		str = "Textura";
	}

	str = "Pagina";
	for (unsigned int i = 0; i < vecPaginas.size(); i++) {
		vecPaginas[i] = new TexturasSDL;
		vecPaginas[i]->load(pRender, "..\\bmps\\" + (str += to_string(i + 1)) + ".png");
		str = "Pagina";
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

	system->release();

	
}
//--------------------------------------------------------------------------------------------------------------------
void juegoPG::run(){
		Uint32 msUpdate = 22;
		std::cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		render();
		handle_event();
		while (!exit) {
			if (SDL_GetTicks() - lastUpdate >= msUpdate) { // while(elapsed >= MSxUpdate)
				estados.top()->update();
				estados.top()->lateUpdate();
				lastUpdate = SDL_GetTicks();
				render();
				estados.top()->updateBorrarObj();
				handle_event();
				}

		}
		
		if (exit) cout << "EXIT \n";
}
//----------------------------------------------------------------------------------------------------------------------
void juegoPG::handle_event(){
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	input.dDS = (keystate[SDL_SCANCODE_RIGHT] && keystate[SDL_SCANCODE_UP]);
	input.dDI = (keystate[SDL_SCANCODE_RIGHT] && keystate[SDL_SCANCODE_DOWN]);
	input.dIS = (keystate[SDL_SCANCODE_LEFT] && keystate[SDL_SCANCODE_UP]);
	input.dII = (keystate[SDL_SCANCODE_LEFT] && keystate[SDL_SCANCODE_DOWN]);
	input.arriba = keystate[SDL_SCANCODE_UP];
	input.abajo = keystate[SDL_SCANCODE_DOWN];
	input.derecha = keystate[SDL_SCANCODE_RIGHT];
	input.izquierda = keystate[SDL_SCANCODE_LEFT];
	input.enter = keystate[SDL_SCANCODE_RETURN] || keystate[SDL_SCANCODE_KP_ENTER];

	int StickX, StickY;
	bool hayMando = true;
	if (Controller[0] != NULL){
		for (int ControllerIndex = 0; ControllerIndex < 2; ++ControllerIndex){

			if (Controller[ControllerIndex] != 0 && SDL_GameControllerGetAttached(Controller[ControllerIndex]))
			{
				// NOTE: We have a controller with index ControllerIndex.
				if (!input.arriba) input.arriba = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_UP);
				if (!input.abajo) input.abajo = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				if (!input.izquierda)input.izquierda = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				if (!input.derecha) input.derecha = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				//input.mcraft = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_START);
				//bool Back = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_BACK);
				bool LeftShoulder = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
				bool RightShoulder = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
				if (!input.enter) input.enter = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_A);
				/*bool BButton = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_B);
				bool XButton = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_X);
				bool YButton = SDL_GameControllerGetButton(Controller[ControllerIndex], SDL_CONTROLLER_BUTTON_Y);*/

				/*StickX = SDL_GameControllerGetAxis(Controller[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTX);
				StickY = SDL_GameControllerGetAxis(Controller[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTY);*/

				if (SDL_HapticRumbleInit(RumbleHandles[ControllerIndex]) != 0)
				{
					SDL_HapticClose(RumbleHandles[ControllerIndex]);
					RumbleHandles[ControllerIndex] = 0;
				}

				if (input.enter || LeftShoulder)
				{
					if (RumbleHandles[ControllerIndex])
					{
						SDL_HapticRumblePlay(RumbleHandles[ControllerIndex], 0.7f, 75);
					}
				}
			}
			else
			{
				// TODO: This controller is note plugged in.
			}
		}
	}
	else {
		hayMando = false;
	}

	StickX = SDL_GameControllerGetAxis(Controller[0], SDL_CONTROLLER_AXIS_LEFTX);
	StickY = SDL_GameControllerGetAxis(Controller[0], SDL_CONTROLLER_AXIS_LEFTY);

	int xDir = 0, yDir = 0;
	if (StickX < -JOYSTICK_DEAD_ZONE) xDir = -1;
	else if (StickX > JOYSTICK_DEAD_ZONE) xDir = 1;
	else xDir = 0;
	
	if (StickY < -JOYSTICK_DEAD_ZONE) yDir = -1;
	else if (StickY > JOYSTICK_DEAD_ZONE) yDir = 1;
	else yDir = 0;

			
	if (xDir == 1 && yDir == -1) input.dDS = true;
	else if (xDir == 1 && yDir == 0) input.derecha = true;
	else if (xDir == -1 && yDir == 0) input.izquierda = true;
	else if (xDir == 1 && yDir == 1) input.dDI = true;
	else if (xDir == -1 && yDir == -1) input.dIS = true;
	else if (xDir == -1 && yDir == 1) input.dII = true;
	else if (xDir == 0 && yDir == -1) input.arriba = true;
	else if (xDir == 0 && yDir == 1) input.abajo = true;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT){
			onExit();
		}
		else if (e.type == SDL_KEYUP || (hayMando && e.type == SDL_CONTROLLERBUTTONUP)){
			if (e.key.keysym.sym == SDLK_ESCAPE || e.cbutton.button == SDL_CONTROLLER_BUTTON_BACK){
				if (dynamic_cast<Nivel1*>(estados.top()) != nullptr) {
					SDL_Surface *sshot = SDL_CreateRGBSurface(0, getScreenWidth(), getScreenHeight(), 32, 0, 0, 0, 0);
					SDL_RenderReadPixels(getRender(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
					SDL_SaveBMP(sshot, "..//bmps//temporal//screenshot.bmp");
					SDL_FreeSurface(sshot);
				}
				estados.top()->onKeyUp('s');
			}
			else if (e.key.keysym.sym == SDLK_TAB || (hayMando && e.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)){
				//input.sw = true;
				estados.top()->onKeyUp('t');
			}
			else if (e.key.keysym.sym == SDLK_e || (hayMando && e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
				input.e = true;
			}
			else if (e.key.keysym.sym == SDLK_p){
				estados.top()->onKeyUp('p');
			}

			else if (e.key.keysym.sym == SDLK_q || (hayMando && e.cbutton.button == SDL_CONTROLLER_BUTTON_START)) {
				if (dynamic_cast<Nivel1*>(estados.top()) != nullptr) {
					SDL_Surface *sshot = SDL_CreateRGBSurface(0, getScreenWidth(), getScreenHeight(), 32, 0, 0, 0, 0);
					SDL_RenderReadPixels(getRender(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
					SDL_SaveBMP(sshot, "..//bmps//temporal//screenshot.bmp");
					SDL_FreeSurface(sshot);
				}
				estados.top()->onKeyUp('q');
			}
			else if (e.key.keysym.sym == SDLK_RETURN || (hayMando && e.cbutton.button == SDL_CONTROLLER_BUTTON_A)) {

				estados.top()->onKeyUp('e');
			}
			else if (e.key.keysym.sym == SDLK_RIGHT || (hayMando && e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
				estados.top()->onKeyUp('d');
			}
			else if (e.key.keysym.sym == SDLK_LEFT || (hayMando && e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
				estados.top()->onKeyUp('i');
			}
			else if (e.key.keysym.sym == SDLK_UP || (hayMando &&e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)) {
				estados.top()->onKeyUp('a');
			}
			else if (e.key.keysym.sym == SDLK_DOWN || (hayMando && e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
				estados.top()->onKeyUp('b');
			}
			else if (e.key.keysym.sym == SDLK_w) estados.top()->onKeyUp('w');
			else if (e.key.keysym.sym == SDLK_r) estados.top()->onKeyUp('r');
			else if (e.key.keysym.sym == SDLK_y) estados.top()->onKeyUp('y');
			else if (e.key.keysym.sym == SDLK_u) estados.top()->onKeyUp('u');
			else if (e.key.keysym.sym == SDLK_z) estados.top()->onKeyUp('z');
			else if (e.key.keysym.sym == SDLK_o) estados.top()->onKeyUp('o');
			else if (e.key.keysym.sym == SDLK_c) estados.top()->onKeyUp('c');
			else if (e.key.keysym.sym == SDLK_x) estados.top()->onKeyUp('x');
			else if (e.key.keysym.sym == SDLK_f) estados.top()->onKeyUp('f');
			else if (e.key.keysym.sym == SDLK_g) estados.top()->onKeyUp('g');
			else if (e.key.keysym.sym == SDLK_h) estados.top()->onKeyUp('h');
			else if (e.key.keysym.sym == SDLK_j) estados.top()->onKeyUp('j');
			else if (e.key.keysym.sym == SDLK_k) estados.top()->onKeyUp('k');
			else if (e.key.keysym.sym == SDLK_l) estados.top()->onKeyUp('l');
			else if (e.key.keysym.sym == SDLK_v) estados.top()->onKeyUp('v');
			else if (e.key.keysym.sym == SDLK_s) estados.top()->onKeyUp('S');
			else if (e.key.keysym.sym == SDLK_n) estados.top()->onKeyUp('n');
			else if (e.key.keysym.sym == SDLK_1) estados.top()->onKeyUp('1');
			else if (e.key.keysym.sym == SDLK_2)estados.top()->onKeyUp('2');
			else if (e.key.keysym.sym == SDLK_3)estados.top()->onKeyUp('3');
			else if (e.key.keysym.sym == SDLK_4)estados.top()->onKeyUp('4');
			else if (e.key.keysym.sym == SDLK_a)estados.top()->onKeyUp('a');
			else if (e.key.keysym.sym == SDLK_b)estados.top()->onKeyUp('b');
			else if (e.key.keysym.sym == SDLK_c)estados.top()->onKeyUp('c');
			else estados.top()->onKeyUp('ñ');
	

		}
		else if (e.type == SDL_KEYDOWN){
			if (e.key.keysym.sym == SDLK_a){
				std::cout << "a ";
			}
			if (e.key.keysym.sym == SDLK_s){
				std::cout << "s";
			}
			if (e.key.keysym.sym == SDLK_f){
				input.follow = true;
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
		else if (e.type == SDL_MOUSEMOTION ){
			pmx = e.button.x;
			pmy = e.button.y;
			estados.top()->onOver();
		}
	}
		/*else {
			input.sw = false;
			
		}*/
		
}

//---------------------------------------------------------------------------------------------------------------------
void juegoPG::initSDL(SDL_Window* &pWindow, SDL_Renderer* &pRenderer) {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_GAMECONTROLLER) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		throw EInitSDL("SDL could not initialize!");
	}
	else {

		int MaxJoysticks = SDL_NumJoysticks();
		int ControllerIndex = 0;
		for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
		{
			if (!SDL_IsGameController(JoystickIndex))
			{
				continue;
			}
			if (ControllerIndex >=2)
			{
				break;
			}
			Controller[ControllerIndex] = SDL_GameControllerOpen(JoystickIndex);

			SDL_Joystick *JoystickHandle = SDL_GameControllerGetJoystick(Controller[ControllerIndex]);
			RumbleHandles[ControllerIndex] = SDL_HapticOpenFromJoystick(JoystickHandle);
			ControllerIndex++;
		}
		

		int x = SDL_GetCurrentDisplayMode(0,&pMode); //0 para poner en toda la pantalla;
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

	unsigned int      version;
	result = FMOD::System_Create(&system);
	result = system->getVersion(&version);

	if (version < FMOD_VERSION)
	{
		std::cout << ("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
	}
	system->init(100, FMOD_INIT_NORMAL, NULL);
	//system->set3DSettings(1.0, 1.0f, 1.0f);


	
}
//-----------------------------------------------------------------------------------------------------------------

void juegoPG::closeSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer) {

	result = system->close();
	result = system->release();
	TTF_Quit();
	for (int ControllerIndex = 0; ControllerIndex < 2; ++ControllerIndex)
	{
		if (RumbleHandles[ControllerIndex])
			SDL_HapticClose(RumbleHandles[ControllerIndex]);
		if (Controller[ControllerIndex])
		{
			SDL_GameControllerClose(Controller[ControllerIndex]);
		}
		
	}
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

	//llamar al draw de encima de la pila
	estados.top()->draw();

	//Show the window
	SDL_RenderPresent(pRender);
}
void juegoPG::onExit(){
	exit = true;
}

void juegoPG::cambiaVida(int cambio) { 
	if (cambio >= 300){
		vida = 300;
		nieblaRect.w = 400 + 4 * (300 - vida);//Tamaño de text min + 4* vida total - vida actual
		nieblaRect.h = 225 + 2.25 * (300 - vida);
		nieblaRect.x = 1600 / 2 - nieblaRect.w / 2;
		nieblaRect.y = 900 / 2 - nieblaRect.h / 2;
	}
	if (vida + cambio <= 300 && vida + cambio >= 0) {
		vida += cambio;
		nieblaRect.w = 400 + 4 * (300 - vida);//Tamaño de text min + 4* vida total - vida actual
		nieblaRect.h = 225 + 2.25 * (300 - vida);
		nieblaRect.x = 1600/2 - nieblaRect.w / 2;
		nieblaRect.y = 900/2 - nieblaRect.h / 2;
		if (vida <= 100) estados.top()->reproduceAmb("PocaVida", false);
	}
}