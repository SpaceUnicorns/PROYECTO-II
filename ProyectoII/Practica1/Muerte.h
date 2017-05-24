#pragma once
#include "EstadoPG.h"
#include "Nivel1.h"
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
	virtual void update(){
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

		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();


		pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\objs.txt", rec, caz, act, false));
		delete borrar;
	}
};

