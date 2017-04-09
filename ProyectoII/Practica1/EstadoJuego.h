#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
struct Punto{
	int x, y;
	bool compruebaRadio(SDL_Rect target, int radio){
		Punto centro; centro.y = target.h / 2 + target.y; centro.x = target.w / 2 + target.x;
		return pow(x - centro.x, 2) + pow(y - centro.y, 2) <= pow(radio, 2);
	}

};
struct TrianguloBorde{
	Punto A, B, C;
};

class EstadoJuego
{
public:

	EstadoJuego()
	{
	}
	virtual void draw() = 0;
	virtual void onClick() = 0;
	virtual void update() = 0;
	virtual void lateUpdate() = 0;
	virtual void onOver() = 0;
	virtual void onKeyUp(char k) = 0;
	virtual void reproduceFx(std::string fx, float x, float y, float wet) = 0;
	virtual void reproduceMusica(std::string music, bool fade) = 0;
	virtual void paraMusica(std::string music, bool fade) = 0;
	virtual void reproduceAmb(std::string amb, bool fade) = 0;
	virtual void paraAmb(std::string amb, bool fade) = 0;
	virtual void cargaMapa(std::string txt, std::vector<TrianguloBorde>& mapa) = 0;
	virtual ~EstadoJuego()
	{
	}
};

