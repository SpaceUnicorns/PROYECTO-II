#include "MovimientoP.h"


MovimientoP::MovimientoP(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	
}


MovimientoP::~MovimientoP()
{
}

void MovimientoP::update(){

	if(framerate % 16 == 0) // se mueve 1 frame cada 16 ms x 16ms
		pObj->changeAnimH();

	framerate++;
	if (pObj->getPJuego()->input.dDS){ //Diagonal Arriba-Derecha
		pObj->setRect(2, -1);
		pObj->changeAnimV(7); // posiciona la 'j' de la matriz de la animacion
	}
	else if (pObj->getPJuego()->input.dDI){//Diagonal Abajo-Derecha
		pObj->setRect(2, 1);
		pObj->changeAnimV(5);

	}
	else if (pObj->getPJuego()->input.dII){//Diagonal Abajo-Izquierda
		pObj->setRect(-2, 1);
		pObj->changeAnimV(4);

	}
	else if (pObj->getPJuego()->input.dIS){//Diagonal Arriba-Izquierda
		pObj->setRect(-2, -1);
		pObj->changeAnimV(6);

	}
	else if (pObj->getPJuego()->input.arriba){
		pObj->setRect(0, -2);
		pObj->changeAnimV(3);

	}
	else if (pObj->getPJuego()->input.derecha){
		pObj->setRect(2, 0);
		pObj->changeAnimV(2);

	}
	else if (pObj->getPJuego()->input.abajo){
		pObj->setRect(0, 2);
		pObj->changeAnimV(0);

	}
	else if (pObj->getPJuego()->input.izquierda){
		pObj->setRect(-2, 0);
		pObj->changeAnimV(1);

	}
}
