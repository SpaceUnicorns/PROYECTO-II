#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Nivel1.h"
class AntorchaC :
	public Componente
{
public:
	AntorchaC(ObjetoJuego* ent, Nivel1* nivel);
	virtual ~AntorchaC();
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

