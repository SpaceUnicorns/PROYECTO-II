#include "Enemigo.h"
#include "Nivel1.h"

Enemigo::Enemigo(juegoPG * juego, Cazador* hunter, Recolector* collector, int px, int py) : ObjetoPG(juego, px, py),
cazador(hunter), recolector(collector), estado(EstadoEnemigo::Quieto)
{
	estado = EstadoEnemigo::Quieto;
	activo = true;
	posIni.x = px;
	posIni.y = py;
	objetivo = nullptr;
	dameUnHogar();
	followEnem = nullptr;
}

void Enemigo::dameUnHogar() {
	casita = new ObjetoPG(pJuego,posIni.x,posIni.y);
}


Enemigo::~Enemigo()
{
	delete casita;
}

void Enemigo::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	posIni.x -= aux.x;
	posIni.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
}

void Enemigo::activaFollow() {
	estado = EstadoEnemigo::Moviendo;
	if (!encuentraComponente("follow")) {
		newComponente(new follow(this, objetivo, dynamic_cast<Nivel1*>(pJuego->getEstadoActual())->getGrafoMapa(), false), "follow");
		followEnem = dynamic_cast<follow*>(mapaComponentes.at("follow"));
	}
	followEnem->setTarget(objetivo);
	followEnem->doFollow();
}

void Enemigo::desactivaFollow() {
	if (estado != EstadoEnemigo::Atrapado){
		estado = EstadoEnemigo::Volviendo;
		followEnem->setTarget(casita);
		followEnem->doFollow();
	}
	else
		followEnem->clearFollow();
}

void Enemigo::followThis(ObjetoPG* target) {
	if (!encuentraComponente("follow")) {
		newComponente(new follow(this, objetivo, dynamic_cast<Nivel1*>(pJuego->getEstadoActual())->getGrafoMapa(), false), "follow");
		followEnem = dynamic_cast<follow*>(mapaComponentes.at("follow"));
	}
	followEnem->setTarget(target);
	followEnem->doFollow();
}