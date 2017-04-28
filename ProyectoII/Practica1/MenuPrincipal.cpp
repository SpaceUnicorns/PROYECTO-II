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
			EstadoJuego* borrar = getPJuego()->estados.top();
			getPJuego()->estados.pop();
			Punto rec; rec.x = 6905; rec.y = 8930; Punto caz; caz.x = 6970; caz.y = 8930;
			getPJuego()->estados.push(new Tutorial(getPJuego(), "../docs/mapa1.txt", "../docs/objetos.txt", rec, caz));
			delete borrar;
		}
	}
}
MenuPrincipal::~MenuPrincipal()
{
	deleteComponente("Menu");
}
