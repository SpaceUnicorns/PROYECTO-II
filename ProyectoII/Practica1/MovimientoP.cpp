#include "MovimientoP.h"
#include "EstadoPG.h"
#include "ColisionBox.h"
#include "Recolector.h"
#include "ObjetoPG.h"
#include "Mochila.h"
#include "Cazador.h"
#include "TrampaAbierta.h"
#include "Equipo.h"
#include "Nivel1.h"


MovimientoP::MovimientoP(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	pCBox = static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"));
	direccion = Default;
	moviendose = false;
}


MovimientoP::~MovimientoP()
{
	
}


void MovimientoP::update(){
	if (pObj->isAble()){
		pEstado = dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top());
		//Antes de actualizar la posición comprobamos si colisiona con la posición siguiente.
		info = nullptr;
		if (framerate % 8 == 0 && moviendose) {// se mueve 1 frame cada 16 ms x 16ms
			pObj->changeAnimH();
			
		}
		if (moviendose && contPasos == 0)
		{
			int rnd = rand() % 4;
			switch (pObj->getTerreno()){
				case 0:
					if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve1", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve2", 0, 0, 0);
					else if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve3", 0, 0, 0);
					break;
				case 1:
					if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera1", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera2", 0, 0, 0);
					else if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera3", 0, 0, 0);
					break;
				case 2:
					if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra1", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra2", 0, 0, 0);
					else if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra3", 0, 0, 0);
					break;
				case 3:
					if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra1", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra2", 0, 0, 0);
					else if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra3", 0, 0, 0);
					break;
			}
		}
		if (moviendose){ 
			contPasos++; 
			if (contPasos >= 20)contPasos = 0;
		}
		framerate++;

		nextPos.x = nextPos.y = 0;

		int colAux;
		//MOVIMIENTO DIRECCIONES
		if (pObj->getPJuego()->input.dDS){ //Diagonal Arriba-Derecha
			nextPos.x = pObj->velocity.x; nextPos.y = -1* pObj->velocity.y;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = dDS;
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(0); // posiciona la 'j' de la matriz de la animacion
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
			moviendose = true;
		}
		else if (pObj->getPJuego()->input.dDI){//Diagonal Abajo-Derecha
			nextPos.x = pObj->velocity.x; nextPos.y = pObj->velocity.y;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = dDI;
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(3);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
			moviendose = true;
		}
		else if (pObj->getPJuego()->input.dII){//Diagonal Abajo-Izquierda
			nextPos.x = -1 * pObj->velocity.x; nextPos.y = pObj->velocity.y;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = dII;
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(7);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
			moviendose = true;
		}
		else if (pObj->getPJuego()->input.dIS){//Diagonal Arriba-Izquierda
			nextPos.x = -1 * pObj->velocity.x; nextPos.y = -1 * pObj->velocity.y;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = dIS;
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(2);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
			moviendose = true;
		}
		else if (pObj->getPJuego()->input.arriba){
			nextPos.x = 0; nextPos.y = -1 * pObj->velocity.x;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = Up;
				pObj->setAbsRect(nextPos.x, nextPos.y);
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(4);
			}
			moviendose = true;
		}
		else if (pObj->getPJuego()->input.derecha){
			nextPos.x = pObj->velocity.x; nextPos.y = 0;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = Right;
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(6);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
			moviendose = true;
		}
		else if (pObj->getPJuego()->input.abajo){
			nextPos.x = 0; nextPos.y = pObj->velocity.x;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = Down;
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(5);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
			moviendose = true;
		}
		else if (pObj->getPJuego()->input.izquierda){
			nextPos.x = -1 * pObj->velocity.x; nextPos.y = 0;
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux != 1 && colAux != 4 && colAux != 5){
				direccion = Left;
				pEstado->setCamara(nextPos.x, nextPos.y);
				pObj->changeAnimV(1);
				pObj->setAbsRect(nextPos.x, nextPos.y);
			}
			moviendose = true;
		}
		else moviendose = false;


		//RECOLECTOR PUEDE COGER OBJETOS
		Mochila* mochilaAux = static_cast<Mochila*> (static_cast<Nivel1*>(pEstado)->getRecolector()->dameComponente("Mochila"));
		colAux = pCBox->isColiding(nextPos, info);
		if (colAux == 2) {
			if (dynamic_cast<Recolector*>(pObj)) {
				if (pObj->getPJuego()->input.e) {
					pObj->getPJuego()->input.e = false; 
					if (info->nombre.size() > 3) info->desaparece = false;
					for (unsigned int i = 0; i + 1 < info->nombre.size(); i += 2){
						pEstado->reproduceFx("RecogeItem1", 0, 0, 0);
						mochilaAux->newItem(info->nombre[i + 1], atoi(info->nombre[i].c_str()));
					}
					if(info->desaparece)pEstado->eraseVectObj(info);
					//std::cout << "He cogido una " << info->nombre << "\n";
				}
			}
		}
		else if (colAux == 3) pObj->esconderse(); 
		else pObj->salirEscondite(); 

		if (pObj->getPJuego()->input.e && !pObj->herido) {
			switch (direccion)
			{
			case Up: nextPos.x = 0; nextPos.y = -15;
				break;
			case dDS: nextPos.x = 30; nextPos.y = -15;
				break;
			case Right:nextPos.x = 30; nextPos.y = 0;
				break;
			case dDI: nextPos.x = 30; nextPos.y = 15;
				break;
			case Down: nextPos.x = 0; nextPos.y = 30;
				break;
			case dII: nextPos.x = -30; nextPos.y = 15;
				break;
			case Left: nextPos.x = -30; nextPos.y = 0;
				break;
			case dIS: nextPos.x = -30; nextPos.y = -15;
				break;
			default:
				break;
			}
			colAux = pCBox->isColiding(nextPos, info);
			if (colAux == 4 ){
				pObj->getPJuego()->input.e = false;
				Equipo* equipoAux = static_cast<Equipo*> (pObj->dameComponente("Equipo"));
				if (equipoAux->tieneEquipo(info->destructor)){
					equipoAux->decreaseCant();
					mochilaAux->removeItem(info->destructor, 1);
					pEstado->eraseVectObj(info);
				}
				//std::cout << "He cogido una " << info->nombre << "\n";
			}
		}


		pObj->getPJuego()->input.e = false;

	}
}
