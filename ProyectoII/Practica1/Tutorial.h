#pragma once
#include "Nivel1.h"
class Tutorial :
	public Nivel1
{
public:
	Tutorial(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz);
	virtual ~Tutorial();
	virtual void onKeyUp(char k);
	virtual void callback();
	virtual void update(int delta);
	virtual void draw(){
		if (!shownVideo){
			SDL_RenderPresent(pJuego->getRender());
			shownVideo = true;
			paraMusica(" ", false);
			std::string auxStr = "cmd /c ..\\videos\\inicio.exe /i1004  /x0 /y0 /w" + to_string(pJuego->getScreenWidth()) + " /h" + to_string(pJuego->getScreenHeight()) + " /u3";
			const char* c = auxStr.c_str();
			std::system(c);
			reproduceMusica("Bosque", false);
		}
		Nivel1::draw();
	}
private:
	bool change, controlsShown;
	bool firsTime;
	bool shownVideo;
};


