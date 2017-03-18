#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class ChangeLayer :
	public Componente
{
public:
	ChangeLayer(ObjetoJuego* ent) : Componente(ent){
		pObj = static_cast<Trigger*>(ent);
		ly = 0;
		done = false;
	};
	virtual ~ChangeLayer(){};
	virtual void callback(){
		if (ly == 0 && !done)ly = 1;
		else if (ly == 1 && !done) ly = 0;
		if (pObj->getPlayerTriggered() == "C")	static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setLayerCaz(ly);
		else static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setLayerRec(ly);
		done = true;
	}
	virtual void update(){
		if (!pObj->isTriggering() && done) done = false;
		pObj->setReacciona(false);
	}
private:
	Trigger* pObj;
	int ly;
	bool done;
};

