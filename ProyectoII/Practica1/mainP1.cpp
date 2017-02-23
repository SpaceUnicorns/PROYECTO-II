
//David Pérez Cogolludo
//Álvaro Rodriguez Peral
#include "juegoPG.h"
#include <iostream>  // la consola: cin / cout
#include "Error.h"
#include "SDL.h"

using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 
//----------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------

int main(int argc, char* args[]) {  // SDL require esta cabecera 
	//system("chcp 1252");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	std:: string msg;
	
	try{
		juegoPG juego;
		juego.run();
	}
	catch (EInitSDL &e) {
		msg= e.mensaje();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.c_str(), nullptr);
	}
	catch (EInitWindow &e) {
		msg = e.mensaje();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.c_str(), nullptr);
	}
	catch (EInitRender &e) {
		msg = e.mensaje();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.c_str(), nullptr);
	}
	catch (ELoadTexture &e) {
		msg = e.mensaje();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", msg.c_str(), nullptr);
	}
	
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------

