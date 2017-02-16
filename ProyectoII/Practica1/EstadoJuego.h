#pragma once
class EstadoJuego
{
public:

	EstadoJuego()
	{
	}
	virtual void draw() = 0;
	virtual void onClick() = 0;
	virtual void update() = 0;
	virtual void onOver() = 0;
	virtual void onKeyUp(char k) = 0;
	virtual ~EstadoJuego()
	{
	}
};

