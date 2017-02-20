#include "ColisionBox.h"


ColisionBox::ColisionBox(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(ent);
	movible = true;
	boxRect.x = pObj->getRect().x;
	boxRect.y = pObj->getRect().y + pObj->getRect().h *0.8;
	boxRect.w = pObj->getRect().w;
	boxRect.h = pObj->getRect().h *0.2;
}
ColisionBox::ColisionBox(ObjetoJuego* ent, SDL_Rect const & newRect, bool mov): Componente(ent){
	pObj = dynamic_cast<ObjetoPG*>(ent);
	boxRect = newRect;
	movible = mov;
}


ColisionBox::~ColisionBox()
{
}
void ColisionBox::update(){
	if (movible){
		boxRect.x = pObj->getRect().x;
		boxRect.y = pObj->getRect().y + pObj->getRect().h *0.8;
	}
}
void ColisionBox::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//std::cout << "Dibujado";
	pObj->getPJuego()->getTextura(TCColision)->draw(pObj->getPJuego()->getRender(), boxRect);
}