#include "TrampaComponente.h"


TrampaComponente::TrampaComponente(ObjetoJuego* entidad) :Componente(entidad)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	comprueba = 0;
}


TrampaComponente::~TrampaComponente()
{
}
void TrampaComponente:: update()
{
	if (comprueba >= 50){
		SDL_Rect p;
		ObjetoPG* info;
		pVecObj = static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj();
		for (size_t i = 0; i < pVecObj.size(); i++)
		{
			if (static_cast<ObjetoPG*>(pVecObj[i])->encuentraComponente("ColisionBox") && pObj != static_cast<ObjetoPG*>(pVecObj[i])){
				SDL_Rect aux = static_cast<ObjetoPG*>(pVecObj[i])->getColisionBox();
				p = pObj->getColisionBox();
				if (aux.x > p.x && aux.x < p.x + p.w && aux.y > p.y && aux.y < p.y + p.h  )
				{
					if (typeid(*pVecObj[i]) == typeid(Cazador) || typeid(*pVecObj[i]) == typeid(Recolector)){
						pObj->getPJuego()->cambiaVida(-30);
						pObj->setRect(0, 999999);
						pObj->getPJuego()->estados.top()->borrarObj(pObj);
						break;
					}
					else if (typeid(*pVecObj[i]) == typeid(Enemigo))
					{
						static_cast<Enemigo*>(pVecObj[i])->life -= 5;
						pObj->setRect(0, 999999);
						pObj->getPJuego()->estados.top()->borrarObj(pObj);
						break;
					}
				}
			}

		}
		comprueba = 0;
	}
	comprueba++;
}