#include "MenuPrincipalComp.h"
#include "checkML.h"


MenuPrincipalComp::MenuPrincipalComp(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	estado = Jugar;
	temp = temp2 = delay= 0;
}


MenuPrincipalComp::~MenuPrincipalComp()
{
}

void MenuPrincipalComp::update()
{
	delay++;
	if (delay > 4){

		if (temp != 0){
			temp2++;
			if (temp2 >= 10){
				temp = temp2 = 0;
			}
		}
		switch (estado){
		case (Salir) :
			if (pObj->getPJuego()->input.arriba){
				if (temp == 0){
					pObj->setRect(0, 100);
					estado = Jugar;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.abajo){
				if (temp == 0){
					pObj->setRect(0, 100);
					estado = Jugar;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.enter){
				static_cast<MenuPrincipal*>(pEntidad)->opcion = 1;
			}
			break;
		case (Jugar) :
			if (pObj->getPJuego()->input.arriba){
				if (temp == 0){
					pObj->setRect(0, -100);
					estado = Salir;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.abajo){
				if (temp == 0){
					pObj->setRect(0, -100);
					estado = Salir;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.enter){
				static_cast<MenuPrincipal*>(pEntidad)->opcion = 2;

			}
			break;
		}
	}

}