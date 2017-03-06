#include "Follow.h"
#include "EstadoPG.h"
#include "ColisionBox.h"

Follow::Follow(ObjetoJuego* ent, ObjetoPG* tg) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	target = tg;
	esquivandoH.esquivando = esquivandoV.esquivando= false;
	esquivandoH.cont= esquivandoV.cont = 0;
	hitInfo = nullptr;
}



Follow::~Follow()
{
}
void Follow::update(){
	if (!pObj->isAble()){
		if (pObj->isFollowing()){

			if (vecDir.x < 0) signoX = -1;
			else signoX = 1;
			if (vecDir.y < 0) signoY = -1;
			else signoY = 1;

			if (pObj->getRect().x != target->getRect().x){
				nextPos.x = 1 * signoX; nextPos.y = 0;
				if (!esquivandoH.esquivando && static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos, hitInfo) != 1){
					esquivandoH.esquivando = true;
					pObj->setRect(nextPos.x, 0);
				}
				else {
					nextPos.x = 0; nextPos.y = -1;
					if (static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos, hitInfo) != 1)
						pObj->setRect(nextPos.x, nextPos.y);
					else {
						nextPos.x = 0; nextPos.y = 1;
						if (static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos, hitInfo) != 1)
							pObj->setRect(nextPos.x, nextPos.y);
					}
					esquivandoH.cont++;
				}
			}
			if (pObj->getRect().y != target->getRect().y){
				nextPos.y = 1 * signoY; nextPos.x = 0;
				if (!esquivandoH.esquivando && static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos, hitInfo) != 1){
					pObj->setRect(0, nextPos.y); esquivandoH.esquivando = true;
				}
				else {
					/*nextPos.x = -1; nextPos.y = 0;
					if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos, hitInfo))
					pObj->setRect(nextPos.x, nextPos.y);
					else {
					nextPos.x = 1; nextPos.y = 0;
					if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos, hitInfo))
					pObj->setRect(nextPos.x, nextPos.y);
					}
					esquivandoV.cont++;*/
				}
			}
			esquivandoH.esquivando = (esquivandoH.cont < 10);
			//esquivandoV.esquivando = (esquivandoV.cont < 100);

		}
		else {
			vecDir.x = 0; vecDir.y = 0;
		}
		if (pObj->getPJuego()->input.follow){
			std::cout << "\nte sigo";
			vecDir.x = target->getRect().x - pObj->getRect().x;
			vecDir.y = target->getRect().y - pObj->getRect().y;
			pObj->swFollowing();
			pObj->getPJuego()->input.follow = false;
		}

	}
}
