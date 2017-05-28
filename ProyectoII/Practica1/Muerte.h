#pragma once
#include "EstadoPG.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
class Muerte :
	public EstadoPG
{
public:

	Muerte(juegoPG*jug) : EstadoPG(jug, 0){

		//DE MOMENTO ESTE ESTADO NO HACE NADA MÄS QUE CARGAR LA PARTIDA.
		
	}

	virtual ~Muerte()
	{
	}
	virtual void update(int delta){
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

		pJuego->getEstadoActual()->paraMusica("", true);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		if (level == "Nivel1"){
			pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act, "../sounds/reverb/ReverbBosque.wav", false));
		}
		else if (level == "Nivel2"){
			pJuego->estados.push(new Nivel2(pJuego, "../docs/mapa2.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act, false));
		}
		else if (level == "Nivel3"){
			pJuego->estados.push(new Nivel3(pJuego, "../docs/mapa3.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act, false));
		}
		delete borrar;
	}
};

