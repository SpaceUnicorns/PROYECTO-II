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
			pAux = dynamic_cast<ObjetoPG*>(pVecObj[i]);
			if (pAux->encuentraComponente("ColisionBox") && pObj != pAux && pAux->nombre[1] == "Enemigo"){
				SDL_Rect aux = pAux->getColisionBox();
				p = pObj->getColisionBox();
				if (aux.x > p.x && aux.x < p.x + p.w && aux.y > p.y && aux.y < p.y + p.h  )
				{				
					static_cast<Enemigo*>(pVecObj[i])->life -= 2;
					static_cast<Enemigo*>(pVecObj[i])->setEstado(EstadoEnemigo::Atrapado);
					pObj->setRect(0, 999999);
					pObj->getPJuego()->estados.top()->borrarObj(pObj);
					break;
				}
			}

		}
		comprueba = 0;
	}
	comprueba++;
}