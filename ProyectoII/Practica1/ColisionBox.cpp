#include "ColisionBox.h"


ColisionBox::ColisionBox(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(ent);
	boxRect.x = pObj->getRect().x;
	boxRect.y = pObj->getRect().y + pObj->getRect().h *0.8;
	boxRect.w = pObj->getRect().w;
	boxRect.h = pObj->getRect().h *0.2;
}
ColisionBox::ColisionBox(ObjetoJuego* ent, SDL_Rect const & newRect): Componente(ent){
	pObj = dynamic_cast<ObjetoPG*>(ent);
	boxRect = newRect;
}


ColisionBox::~ColisionBox()
{
}
void ColisionBox::update(){
	//draw();
	pObj->getPJuego()->getTextura(TCazador)->draw(pObj->getPJuego()->getRender(), boxRect);
}
void ColisionBox::draw(){
	//std::cout << "Dibujado";
	pObj->getPJuego()->getTextura(TCazador)->draw(pObj->getPJuego()->getRender(), boxRect);
}