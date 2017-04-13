#include "Huella.h"


Huella::Huella(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(ent);
	sizeMax = 10;
	it = 0;
	state = None;
	timer = 0;
}


Huella::~Huella()
{
}
void Huella::setHuella(Dir dir){

	if (it == sizeMax)	it = 0;
	if (vecHuellas.size() < sizeMax){
		vecHuellas.push_back(new ObjetoHuella(it, this, pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y));
		it++;
	}
	else{
		quitaHuella(it);
		vecHuellas[it] = new ObjetoHuella(it, this, pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y);
		it++;
	}

}
void Huella::quitaHuella( int ind){
	ObjetoHuella* aux;
	aux = vecHuellas[ind];
	vecHuellas[ind] = nullptr;
	delete aux;
}
void Huella::update(){
	if (timer == 10){
		if (pObj->getPJuego()->input.dDS) setHuella(DDS);
		else if (pObj->getPJuego()->input.dDI) setHuella(DDI);
		else if (pObj->getPJuego()->input.dII) setHuella(DII);
		else if (pObj->getPJuego()->input.dIS) setHuella(DIS);
		else if (pObj->getPJuego()->input.arriba) setHuella(Arriba);
		else if (pObj->getPJuego()->input.derecha) setHuella(Derecha);
		else if (pObj->getPJuego()->input.abajo) setHuella(Abajo);
		else if (pObj->getPJuego()->input.izquierda) setHuella(Izquierda);
		timer = 0;
	}
	else timer++;
}
void Huella::lateUpdate(){
	for (ObjetoHuella* ob : vecHuellas)if (ob != nullptr) ob->update();
}
void Huella::draw(){
	for (ObjetoHuella* ob : vecHuellas){
		if (ob != nullptr) ob->draw();
	}
}