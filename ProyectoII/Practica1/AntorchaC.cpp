#include "AntorchaC.h"
#include "Equipo.h"


AntorchaC::AntorchaC(ObjetoJuego* ent, Nivel1* nivel) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(ent);
	time = 2000;
	alpha = 125;
	contFrames = 0;
	level = nivel;
	level->setAlpha(100);
	able = false;
	rectTorch.h = 350;// pJuego->getTextura(TAntorcha)->getH();
	rectTorch.w = 350;// pJuego->getTextura(TAntorcha)->getW();
	rectTorch.x = pObj->getRect().x - (rectTorch.w/2);
	rectTorch.y = pObj->getRect().y - (rectTorch.h / 2);
}


AntorchaC::~AntorchaC()
{
}
void AntorchaC::update(){
	if (able){
		contFrames++;
		if(contFrames%18 == 0 && alpha <255) alpha++;
		level->setAlpha(alpha);
	}
	if (contFrames >= time){
		level->dropTorch();
		swAble();
	}
	
}
void  AntorchaC::draw(){
	if (!pObj->isAble() && able) { 
		rectTorch.y -= dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getCamara().y;
		rectTorch.x -= dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getCamara().x;
	}
}
void AntorchaC::swAble(){
	if (able){
		contFrames = 0;
		level->setAlpha(255);
		alpha = 125;
		static_cast<Equipo*>(pObj->dameComponente("Equipo"))->setEquipo("Nada", 0);
		able = false;
	}
	else{
		able = true;
		level->setAlpha(alpha);
		rectTorch.x = pObj->getRect().x - (rectTorch.w / 2);
		rectTorch.y = pObj->getRect().y - (rectTorch.h / 2);
		level->getTorch();
	}
}
void AntorchaC::lateDraw(){
	if (able){

		int aux, aux2; aux2 = rand() % 51; aux = 0;
		if (aux2 >= 45) aux = rand() % 20;
		rectTorch.w -= aux; rectTorch.h -= aux;

		pObj->getPJuego()->getTextura(TAntorcha)->setBlendMode(pObj->getPJuego()->getRender(), SDL_BLENDMODE_ADD);
		pObj->getPJuego()->getTextura(TAntorcha)->draw(pObj->getPJuego()->getRender(), rectTorch, 25 + aux);

		pObj->getPJuego()->getTextura(TAntorcha)->draw(pObj->getPJuego()->getRender(), rectTorch, 1);
		rectTorch.w += aux; rectTorch.h += aux; //if (able) pObj->getPJuego()->getTextura(TAntorcha)->draw(pObj->getPJuego()->getRender(), level->getCamara(), 200);
	}
}