#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Nivel1.h"
class Antorcha :
	public Componente
{
public:
	Antorcha(ObjetoJuego* ent, Nivel1* nivel);
	virtual ~Antorcha();
	virtual void update();
	virtual void draw();
	void swAble();
private:
	int time;
	int contFrames, alpha;
	bool able;
	Nivel1* level;
	ObjetoPG* pObj;
};

