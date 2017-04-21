#include "MovimientoP.h"
#include "EstadoPG.h"
#include "ColisionBox.h"
#include "Recolector.h"
#include "ObjetoPG.h"
#include "Mochila.h"
#include "Cazador.h"
#include "TrampaAbierta.h"


MovimientoP::MovimientoP(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	pCBox = static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"));
	
}


MovimientoP::~MovimientoP()
{
	
}


void MovimientoP::update(){
	if (pObj->isAble()){
		pEstado = dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top());
		//Antes de actualizar la posici�n comprobamos si colisiona con la posici�n siguiente.
		info = nullptr;
		if (framerate % 16 == 0) // se mueve 1 frame cada 16 ms x 16ms
			pObj->changeAnimH();

		framerate++;

		nextPos.x = nextPos.y = 0;



		//RECOLECTOR PUEDE COGER OBJETOS
		int colAux = pCBox->isColiding(nextPos, info);
		if (colAux == 2) {
			if (dynamic_cast<Recolector*>(pObj)) {
				if (pObj->getPJuego()->input.e) {
					pObj->getPJuego()->input.e = false;
					for (unsigned int i = 0; i + 1 < info->nombre.size(); i += 2){
						pEstado->reproduceFx("RecogeItem1", -100, 0, 0);
						static_cast<Mochila*> (pObj->dameComponente("Mochila"))->newItem(info->nombre[i + 1], atoi(info->nombre[i].c_str()));
					}
					pEstado->eraseVectObj(info);
					//std::cout << "He cogido una " << info->nombre << "\n";
				}
			}
		}
		else if (colAux == 3) pObj->esconderse();
		else pObj->salirEscondite();


		pObj->getPJuego()->input.e = false;

		//MOVIMIENTO DIRECCIONES
		if (pObj->getPJuego()->input.dDS){ //Diagonal Arriba-Derecha
			nextPos.x = 2; nextPos.y = -1;
			if (pCBox->isColiding(nextPos, info) != 1){
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(7); // posiciona la 'j' de la matriz de la animacion
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
		}
		else if (pObj->getPJuego()->input.dDI){//Diagonal Abajo-Derecha
			nextPos.x = 2; nextPos.y = 1;
			if (pCBox->isColiding(nextPos, info) != 1){
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(5);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}

		}
		else if (pObj->getPJuego()->input.dII){//Diagonal Abajo-Izquierda
			nextPos.x = -2; nextPos.y = 1;
			if (pCBox->isColiding(nextPos, info) != 1){
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(4);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}

		}
		else if (pObj->getPJuego()->input.dIS){//Diagonal Arriba-Izquierda
			nextPos.x = -2; nextPos.y = -1;
			if (pCBox->isColiding(nextPos, info) != 1){
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(6);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}

		}
		else if (pObj->getPJuego()->input.arriba){
			nextPos.x = 0; nextPos.y = -2;
			if (pCBox->isColiding(nextPos, info) != 1){
				pObj->setAbsRect(nextPos.x, nextPos.y);
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(3);
			}

		}
		else if (pObj->getPJuego()->input.derecha){
			nextPos.x = 2; nextPos.y = 0;
			if (pCBox->isColiding(nextPos, info) != 1){
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(2);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}

		}
		else if (pObj->getPJuego()->input.abajo){
			nextPos.x = 0; nextPos.y = 2;
			if (pCBox->isColiding(nextPos, info) != 1){
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(0);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}

		}
		else if (pObj->getPJuego()->input.izquierda){
			nextPos.x = -2; nextPos.y = 0;
			if (pCBox->isColiding(nextPos, info) != 1){
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(1);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}

		}
	}
}
