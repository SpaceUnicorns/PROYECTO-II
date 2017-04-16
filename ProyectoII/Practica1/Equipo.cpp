#include "Equipo.h"
#include "TrampaAbierta.h"
#include "AntorchaC.h"


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
			if (pObj->getPJuego()->input.e && cantidad > 0)
			{
				static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj().push_back(new TrampaAbierta(pObj->getPJuego(), pObj->getRect().x, pObj->getRect().y ));
				mochila->removeItem("Trampa", 1);
				cantidad--;
			}
			if (cantidad == 0) equipado = Nada;
			break;
		case Antorcha:
			//cantidad--;
			if (cantidad > 0){
				dynamic_cast<AntorchaC*>(pObj->dameComponente("AntorchaC"))->swAble();
				mochila->removeItem("Antorcha", 1);
				cantidad--;
			}
			break;
		case Hacha:
			if (pObj->getPJuego()->input.enter && cantidad > 0){
				//Rellenar en función de lo que haga
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