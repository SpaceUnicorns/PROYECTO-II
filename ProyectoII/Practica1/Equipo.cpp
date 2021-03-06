#include "Equipo.h"
#include "TrampaAbierta.h"
#include "AntorchaC.h"
#include "AtaqueCazador.h"

Equipo::Equipo(ObjetoJuego* entidad, Mochila* moch) :Componente(entidad)
{
	pObj = dynamic_cast<ObjetoPG*>(entidad);
	equipado = Nada;
	cantidad = 0;
	delay = 1000;
	mochila = moch;
}


Equipo::~Equipo()
{
}
void Equipo::update(int delta)
{
	if (delay > 0)
		delay-=delta;
	if (delay <= 0){
		
		switch (equipado)
		{
		case Nada:
			break;
		case Trampa:
			if (pObj->getPJuego()->input.enter && cantidad > 0 && !pObj->herido)
			{
				static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj().push_back(new TrampaAbierta(pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y + 30));
				mochila->removeItem("Trampa", 1);
				cantidad--;
				pObj->getPJuego()->input.enter = false;
				pObj->getPJuego()->getEstadoActual()->reproduceFx("PonerTrampa", 0, 0, 0);
				delay = 1000;
			}
			if (cantidad == 0) { equipado = Nada; }
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
			//Rellenar en funci�n de lo que haga
			if (cantidad > 0 && static_cast<AtaqueCazador*>(pObj->dameComponente("AtaqueCazador"))->getAxResistance() <= 0){
				dynamic_cast<AtaqueCazador*>(pObj->dameComponente("AtaqueCazador"))->setAxResistance(10);
				std::cout << "Has usado el hacha\n";
				mochila->removeItem("Hacha", 1);
				cantidad--;
				delay = 1000;
			}
			if (cantidad == 0) equipado = Nada;
			break;
		case Pala:
			/*if (cantidad > 0 && !pObj->herido){
				//Rellenar en funci�n de lo que haga
				std::cout << "Has usado la pala\n";
				mochila->removeItem("Pala", 1);
				cantidad--;
				delay = 1000;
			}*/
			if (cantidad == 0) equipado = Nada;
			break;
		case Pico:
			/*if (pObj->getPJuego()->input.enter && cantidad > 0 && !pObj->herido){
				//Rellenar en funci�n de lo que haga
				std::cout << "Has usado el pico\n";
				mochila->removeItem("Pico", 1);
				cantidad--;
				delay = 1000;
			}*/
			if (cantidad == 0) equipado = Nada;
			break;

		}
	}

}