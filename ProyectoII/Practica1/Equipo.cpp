#include "Equipo.h"
#include "TrampaAbierta.h"


Equipo::Equipo(ObjetoJuego* entidad, Mochila* moch) :Componente(entidad)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	equipado = Nada;
	cantidad = 0;
	mochila = moch;
}


Equipo::~Equipo()
{
}
void Equipo::update()
{
	if (pObj->isAble())
	{
		switch (equipado)
		{
		case Nada:
			break;
		case Trampa:
			if (pObj->getPJuego()->input.e && cantidad > 0)
			{
				static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj().push_back(new TrampaAbierta(pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y - 50));
				mochila->removeItem("Trampa", 1);
				cantidad--;
			}
			if (cantidad == 0) equipado = Nada;
			break;
		case Antorcha:
			break;
		case Hacha:
			break;
		}
		
	}

}