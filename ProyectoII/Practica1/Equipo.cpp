#include "Equipo.h"
#include "TrampaAbierta.h"
#include "AntorchaC.h"
#include "AtaqueCazador.h"

Equipo::Equipo(ObjetoJuego* entidad, Mochila* moch) :Componente(entidad)
{
	pObj = dynamic_cast<ObjetoPG*>(entidad);
	equipado = Nada;
	cantidad = 0;
	mochila = moch;
}


Equipo::~Equipo()
{
}
void Equipo::update()
{
	//if (pObj->isAble())
	//{
		switch (equipado)
		{
		case Nada:
			break;
		case Trampa:
			if (pObj->getPJuego()->input.enter && cantidad > 0)
			{
				static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj().push_back(new TrampaAbierta(pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y+30));
				mochila->removeItem("Trampa", 1);
				cantidad--;
				pObj->getPJuego()->getEstadoActual()->reproduceFx("PonerTrampa", 0,0,0);
			}
			if (cantidad == 0) equipado = Nada;
			break;
		case Antorcha:
			//cantidad--;
			if (cantidad > 0){
				dynamic_cast<AntorchaC*>(pObj->dameComponente("AntorchaC"))->swAble();
				mochila->removeItem("Antorcha", 1);
				pObj->getPJuego()->getEstadoActual()->reproduceAmb("Fuego", false);
				cantidad--;
			}
			break;
		case Hacha:
			if (pObj->getPJuego()->input.enter && cantidad > 0){
				//Rellenar en función de lo que haga
				dynamic_cast<AtaqueCazador*>(pObj->dameComponente("AtaqueCazador"))->setAxResistance(10);
				std::cout << "Has usado el hacha\n";
				mochila->removeItem("Hacha", 1);
				cantidad--;
			}
			if (cantidad == 0) equipado = Nada;
			break;
		case Pala: 
			if (pObj->getPJuego()->input.enter && cantidad > 0){
			//Rellenar en función de lo que haga
			std::cout << "Has usado la pala\n";
			mochila->removeItem("Pala", 1);
			cantidad--;
			}
			if (cantidad == 0) equipado = Nada;
			break;
		case Pico:
			if (pObj->getPJuego()->input.enter && cantidad > 0){
				//Rellenar en función de lo que haga
				std::cout << "Has usado el pico\n";
				mochila->removeItem("Pico", 1);
				cantidad--;
			}
			if (cantidad == 0) equipado = Nada;
			break;

		}
		
	//}

}