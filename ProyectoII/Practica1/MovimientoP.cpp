#include "MovimientoP.h"


MovimientoP::MovimientoP(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
}


MovimientoP::~MovimientoP()
{
}

void MovimientoP::update(){
	

	if (pObj->getPJuego()->input.dDS){ //Diagonal Arriba-Derecha
		pObj->setRect(2, -1);
	}
	else if (pObj->getPJuego()->input.dDI){//Diagonal Abajo-Derecha
		pObj->setRect(2, 1);
	}
	else if (pObj->getPJuego()->input.dII){//Diagonal Abajo-Izquierda
		pObj->setRect(-2, 1);
	}
	else if (pObj->getPJuego()->input.dIS){//Diagonal Arriba-Izquierda
		pObj->setRect(-2, -1);
	}
	else if (pObj->getPJuego()->input.arriba){
		pObj->setRect(0, -2);
	}
	else if (pObj->getPJuego()->input.derecha){
		pObj->setRect(2, 0);
	}
	else if (pObj->getPJuego()->input.abajo){
		pObj->setRect(0, 2);
	}
	else if (pObj->getPJuego()->input.izquierda){
		pObj->setRect(-2, 0);
	}
}
