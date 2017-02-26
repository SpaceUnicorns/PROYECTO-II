#pragma once

class ObjetoJuego 
{
protected:
	ObjetoJuego()
	{
	}

public:

	virtual ~ObjetoJuego() {};
	virtual void draw() = 0;
	virtual void drawOnSw() = 0;
	virtual void update() = 0;
	virtual bool onClick() = 0;
	virtual bool onOver() = 0;
};

