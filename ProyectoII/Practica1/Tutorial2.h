#pragma once
#include "Nivel1.h"
#include "Trigger.h"
#include "TextCb.h"
class Tutorial2 :
	public Nivel1
{
public:
	Tutorial2(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz);
	virtual ~Tutorial2();
	virtual void onKeyUp(char k);
	virtual void callback();
	virtual void update();
private:
	bool change;
	bool firsTime;
};
class changeScene :
	public Componente
{
public:
	changeScene(ObjetoJuego* ent, Nivel1* aux) : Componente(ent){
		reacciona = false;
		pObj = dynamic_cast<Trigger*>(ent);
		this->aux = aux;
	};
	virtual ~changeScene(){};
	virtual void callback();
	virtual void update(){};
	virtual void draw(){};

private:
	bool reacciona;
	Trigger* pObj;
	Nivel1* aux;
};
