#include "Huella.h"


Huella::Huella(ObjetoJuego* ent, int _w, int _h) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(ent);
	sizeMax = 8;
	it = 0;
	state = None;
	timer = 0;
	w = _w;
	h = _h;
}


Huella::~Huella()
{
}
void Huella::setHuella(int dir ){

	if (it == sizeMax)	it = 0;
	if (vecHuellas.size() < sizeMax){
		vecHuellas.push_back(new ObjetoHuella(dir, it, this, pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y, w, h));
		it++;
	}
	else{
		quitaHuella(it);
		vecHuellas[it] = new ObjetoHuella(dir, it, this, pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y, w, h);
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
		if (pObj->getPJuego()->input.dDS) setHuella(0);
		else if (pObj->getPJuego()->input.dDI) setHuella(1);
		else if (pObj->getPJuego()->input.dII) setHuella(2);
		else if (pObj->getPJuego()->input.dIS) 
			setHuella(3);
		else if (pObj->getPJuego()->input.arriba) setHuella(4);
		else if (pObj->getPJuego()->input.derecha) setHuella(5);
		else if (pObj->getPJuego()->input.abajo) setHuella(6);
		else if (pObj->getPJuego()->input.izquierda) setHuella(7);
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