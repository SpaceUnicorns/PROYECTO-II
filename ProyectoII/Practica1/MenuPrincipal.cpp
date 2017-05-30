#include "MenuPrincipal.h"
#include "MenuPrincipalComp.h"
#include "Tutorial.h"
#include "Tutorial2.h"
#include "Mochila.h"
#include "Nivel2.h"
#include "Nivel3.h"

MenuPrincipal::MenuPrincipal(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = TMenuResaltado;
	int auxH = pJuego->getScreenHeight() / 2 - 21; //21 = boton.h / 2
	int auxW = pJuego->getScreenWidth() / 2 + 100;

	rect.x = auxW - 10;
	rect.y = auxH - 107;
	rect.w = 364;
	rect.h = 55;
	absRect.w = rect.w;
	absRect.h = rect.h;
	activo = true;
	newComponente(new MenuPrincipalComp(this), "Menu");
	opcion = 0;
}

void MenuPrincipal::update(int delta)
{
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (activo && it != itFin){
		it->second->update(delta);
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
			/*Punto rec; rec.x = 6925; rec.y = 10265; Punto caz; caz.x = 0; caz.y = 0;
			getPJuego()->estados.push(new Tutorial(getPJuego(), "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));*/
			//IR A TUTORIAL 2
			//Punto rec; rec.x = 0; rec.y = 0; Punto caz; caz.x = 6925; caz.y = 10260;
			//pJuego->estados.push(new Tutorial2(pJuego, "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));

			//IR AL NIVEL 1 6850, 9150
			//Punto caz; caz.x = 6950; caz.y = 9150; Punto rec; rec.x = 7010; rec.y = 9130;
			//Punto caz; caz.x = 1778; caz.y = 3576; Punto rec; rec.x = 2078; rec.y = 3596;
			//====== FINAL DEL NIVEL ======= 3077 , 1260
			//Punto caz; caz.x = 3090; caz.y = 1420; Punto rec; rec.x = 3120; rec.y = 1420;
			//pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetosNivel1.txt", rec, caz, "R","../sounds/reverb/ReverbBosque.wav"));

			//IR AL NIVEL 2
			Punto caz; caz.x = 2723; caz.y = 2394; Punto rec; rec.x = 2603; rec.y = 2394;
			//======= FINAL DEL NIVEL =========
			//Punto caz; caz.x = 5031; caz.y = 917; Punto rec; rec.x = 5000; rec.y = 917; 
			pJuego->estados.push(new Nivel2(pJuego, "../docs/mapa2.txt", "../docs/objetosNivel2.txt", rec, caz, "R"));

			//IR AL NIVEL 3
			/*Punto caz; caz.x = 3456; caz.y = 696; Punto rec; rec.x = 3496; rec.y = 726;
			pJuego->estados.push(new Nivel3(pJuego, "../docs/mapa3.txt", "../docs/objetosNivel3.txt", rec, caz, "R"));*/
			delete borrar;
		}
		else if (opcion == 3){
			std::cout << "CARGAR\n";
			std::ifstream f;

			f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\players.txt", std::ios::in);
			Punto caz; Punto rec; std::string name; char stash; std::string act; std::string level;
			while (!f.eof() && !f.fail()){
				f >> level;
				if (!f.fail()){
					f >> name;
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


			if (rec.x == caz.x) caz.x += 50;

			getPJuego()->getEstadoActual()->paraMusica("", true);
			EstadoJuego* borrar = getPJuego()->estados.top();
			getPJuego()->estados.pop();
			if (level == "Nivel1"){
				pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act,"../sounds/reverb/ReverbBosque.wav", false));
			}
			else if (level == "Nivel2"){
				pJuego->estados.push(new Nivel2(pJuego, "../docs/mapa2.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act, false));
			}
			else if (level == "Nivel3"){
				pJuego->estados.push(new Nivel3(pJuego, "../docs/mapa3.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act, false));
			}
			delete borrar;

		}
	}
}

MenuPrincipal::~MenuPrincipal()
{
	deleteComponente("Menu");
}
