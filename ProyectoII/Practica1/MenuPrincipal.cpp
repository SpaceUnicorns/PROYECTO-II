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
			std::ofstream f;
			f.open(pJuego->getPath()+"\\Galiakberova\\partidaGuardada\\mochila.txt");
			f.close();
			f.open(pJuego->getPath() + "\\Galiakberorva\\partidaGuardada\\cabanias.txt");
			f.close();
			f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
			f.close();
			getPJuego()->getEstadoActual()->paraMusica("", true);
			EstadoJuego* borrar = getPJuego()->estados.top();
			getPJuego()->estados.pop();
			
			//IR A TUTORIAL 1
			Punto rec; rec.x = 6925; rec.y = 10265; Punto caz; caz.x = 0; caz.y = 0;
			getPJuego()->estados.push(new Tutorial(getPJuego(), "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));
			
			//IR A TUTORIAL 2
			//Punto rec; rec.x = 0; rec.y = 0; Punto caz; caz.x = 6925; caz.y = 10260;
			//pJuego->estados.push(new Tutorial2(pJuego, "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));

			//IR AL NIVEL 1 6850, 9150
			/*Punto caz; caz.x = 6950; caz.y = 9150; Punto rec; rec.x = 7010; rec.y = 9130;
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetosNivel1.txt", rec, caz, "R"));*/

			//IR AL NIVEL 2
			/*Punto caz; caz.x = 950; caz.y = 950; Punto rec; rec.x = 710; rec.y = 930;
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa2.txt", "../docs/objetos.txt", rec, caz, "R"));*/
			delete borrar;
		}
		else if (opcion == 3){
			std::cout << "CARGAR\n";
			std::ifstream f;

			f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\players.txt", std::ios::in);
			Punto caz; Punto rec; std::string name; char stash; std::string act;
			while (!f.eof() && !f.fail()){
				f >> name;
				if (!f.fail()){
					f.get(stash); f.get(stash); f.get(stash);
					f >> caz.x;
					f.get(stash); f.get(stash); f.get(stash);
					f >> caz.y;
					f >> name;
					f.get(stash); f.get(stash); f.get(stash);
					f >> rec.x;
					f.get(stash); f.get(stash); f.get(stash);
					f >> rec.y;
					f >> act;

				}
			}
			f.close();

			getPJuego()->getEstadoActual()->paraMusica("", true);
			EstadoJuego* borrar = getPJuego()->estados.top();
			getPJuego()->estados.pop();
		
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act, false));
			delete borrar;

		}
	}
}

MenuPrincipal::~MenuPrincipal()
{
	deleteComponente("Menu");
}
