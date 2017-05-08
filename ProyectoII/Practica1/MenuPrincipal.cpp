#include "MenuPrincipal.h"
#include "MenuPrincipalComp.h"
#include "Tutorial.h"

MenuPrincipal::MenuPrincipal(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = TMenuResaltado;
	rect.w = 256;
	rect.h = 82;
	absRect.w = rect.w;
	absRect.h = rect.h;
	activo = true;
	newComponente(new MenuPrincipalComp(this), "Menu");
	opcion = 0;
}

void MenuPrincipal::update(){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (activo && it != itFin){
		it->second->update();
		it++;
	}
	if (opcion != 0){
		if (opcion == 1){
			/*EstadoJuego* borrar = getPJuego()->estados.top();
			getPJuego()->estados.pop();
			delete borrar;*/
			getPJuego()->setSalir();
		}
		else if (opcion == 2){
			getPJuego()->getEstadoActual()->paraMusica("", true);
			EstadoJuego* borrar = getPJuego()->estados.top();
			getPJuego()->estados.pop();
			/*Punto rec; rec.x = 6912; rec.y = 10286; Punto caz; caz.x = 0; caz.y = 0;
			getPJuego()->estados.push(new Tutorial(getPJuego(), "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));
			*/

			//Descomentar esto para ir directamente al nivel
			Punto caz; caz.x = 6925; caz.y = 8930; Punto rec; rec.x = 6970; rec.y = 8930;
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetosNivel1.txt", rec, caz, "R"));
			delete borrar;
		}
	}
}
MenuPrincipal::~MenuPrincipal()
{
	deleteComponente("Menu");
}
