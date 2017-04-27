#pragma once
#include <iostream>
#include "ObjetoJuego.h"
#include <vector>
class EstadoJuego
{
public:

	EstadoJuego()
	{
	}
	virtual void draw() = 0;
	virtual void awake() = 0;
	virtual void onClick() = 0;
	virtual void update() = 0;
	virtual void lateUpdate() = 0;
	virtual void onOver() = 0;
	virtual void onKeyUp(char k) = 0;
	virtual void borrarObj(ObjetoJuego* o) {};
	virtual void updateBorrarObj() {};
	virtual void reproduceFx(std::string fx, float x, float y, float wet) = 0;
	virtual void reproduceMusica(std::string music, bool fade) = 0;
	virtual void paraMusica(std::string music, bool fade) = 0;
	virtual void reproduceAmb(std::string amb, bool fade) = 0;
	virtual void paraAmb(std::string amb, bool fade) = 0;
	virtual void cargaMapa(std::string txt, std::vector<char>& mapa) = 0;
	virtual ~EstadoJuego()
	{
	}
};

