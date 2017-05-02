#include "AtaqueZ.h"
#include "Cazador.h"

AtaqueZ::AtaqueZ(ObjetoJuego* entidad, juegoPG * juego, int px, int py) : Componente(entidad), ObjetoPG(juego, px, py)
{
	rect.x = px;
	rect.y = py;
	rect.w = 30;
	rect.h = static_cast<Cazador*>(entidad)->getRect().h;
	newComponente(new ColisionBox(this, rect, true), "AttackBox"); //poner en el cazador directamente (?)
	
	atacando = false;
	pObj = dynamic_cast<Cazador*>(entidad);
	box = dynamic_cast<ColisionBox*>(dameComponente("AttackBox"));
}


AtaqueZ::~AtaqueZ()
{
}

void AtaqueZ::update() {
 // recolocar el box
	/*if (pObj->getPJuego()->input.dDS) { //Diagonal Arriba-Derecha
		box->setRectBox(getX() + 40, getY() - 55);
	}
	else if (pObj->getPJuego()->input.dDI) {//Diagonal Abajo-Derecha
		box->setRectBox(getX() + 40, getY() - 50);
	}
	else if (pObj->getPJuego()->input.dII) {//Diagonal Abajo-Izquierda
		box->setRectBox(getX() - 20, getY() - 50);
	}
	else if (pObj->getPJuego()->input.dIS) {//Diagonal Arriba-Izquierda
		box->setRectBox(getX() - 20, getY() - 55);
	}
	*/
	//else 
	
	if (pObj->getPJuego()->input.arriba) {
		box->setDimBox(pObj->getRect().h, 30);
		box->setRectBox(getX() - (pObj->getRect().h / 2), getY() - 40);
	}
	else if (pObj->getPJuego()->input.derecha) { //done
		box->setDimBox(30, pObj->getRect().h);
		box->setRectBox(getX() + getW(), getY());
	}
	else if (pObj->getPJuego()->input.abajo) {
		box->setDimBox(pObj->getRect().h, 30);
		box->setRectBox(getX() - (pObj->getRect().h/2), getY() + 40);
	}
	else if (pObj->getPJuego()->input.izquierda) { //done
		box->setDimBox(30, pObj->getRect().h);
		box->setRectBox(getX() - rect.w, getY());
	}

	if (atacando) Attack();

}


void AtaqueZ::Attack() {

	int x = box->getRectBox().x;
	int y = box ->getRectBox().y;
	
	Punto p;
	p.x = getX();
	p.y = getY();

	ObjetoPG* enemy;
	enemy = nullptr;

	if (box->isColiding(p, enemy)) {
		//el lobo pierde vida
		//dynamic_cast<Enemigo*>(enemy)->QUITARMUCHAVIDAPAYO();
	}

	atacando = false;

}

