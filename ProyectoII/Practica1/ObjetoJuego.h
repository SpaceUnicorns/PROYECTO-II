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
	virtual void lateDraw() = 0;
	virtual void update(int delta) = 0;
	virtual void lateUpdate(int delta) = 0;
	virtual bool onClick() = 0;
	virtual bool onOver() = 0;
};

