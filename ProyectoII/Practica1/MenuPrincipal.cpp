#include "MenuPrincipal.h"
#include "MenuPrincipalComp.h"
#include "Tutorial.h"
#include "Tutorial2.h"
#include "Mochila.h"

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

void MenuPrincipal::update()
{
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
			
			//IR A TUTORIAL 1
			//Punto rec; rec.x = 6925; rec.y = 10265; Punto caz; caz.x = 0; caz.y = 0;
			//getPJuego()->estados.push(new Tutorial(getPJuego(), "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));
			
			//IR A TUTORIAL 2
			//Punto rec; rec.x = 0; rec.y = 0; Punto caz; caz.x = 6925; caz.y = 10260;
			//pJuego->estados.push(new Tutorial2(pJuego, "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));

			//IR A JUEGO JUNTOS 6850, 9150
			Punto caz; caz.x = 6950; caz.y = 9150; Punto rec; rec.x = 7010; rec.y = 9130;
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetosNivel1.txt", rec, caz, "R"));
			static_cast<Mochila*> (static_cast<Nivel1*>(pJuego->estados.top())->getRecolector()->dameComponente("Mochila"))->newItem("Hacha", 1);
			static_cast<Mochila*> (static_cast<Nivel1*>(pJuego->estados.top())->getRecolector()->dameComponente("Mochila"))->newItem("Cuerda", 1);
			
			delete borrar;
		}
	}
}

MenuPrincipal::~MenuPrincipal()
{
	deleteComponente("Menu");
}
