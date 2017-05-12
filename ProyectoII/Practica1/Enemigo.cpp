#include "Enemigo.h"


Enemigo::Enemigo(juegoPG * juego, Cazador* hunter, Recolector* collector, GrafoMapa* mapa, int px, int py) : ObjetoPG(juego, px, py),
cazador(hunter), recolector(collector), estado(EstadoEnemigo::Quieto)
{
	estado = EstadoEnemigo::Quieto;
	activo = true;
	posIni.x = px;
	posIni.y = py;
	objetivo = nullptr;
	dameUnHogar();
	followEnem = nullptr;
	following = false;
	//nombre.push_back("Enemigo");
	contFollow = 0;
	followEnem = nullptr; // 
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
	if (!followEnem) followEnem = dynamic_cast<follow*>(mapaComponentes.at("follow"));
	followEnem->setTarget(objetivo);
	followEnem->doFollow();
	following = true;
}

void Enemigo::desactivaFollow() {
	if (!followEnem) followEnem = dynamic_cast<follow*>(mapaComponentes.at("follow"));
	if (estado == Atrapado || estado == Muerto){
			followEnem->clearFollow();
			following = false;
		}
	else {
		estado = EstadoEnemigo::Volviendo;
		followEnem->setTarget(casita);
		followEnem->doFollow();
		following = true;
	}

}

void Enemigo::followThis(ObjetoPG* target) {
	if (!followEnem) followEnem = dynamic_cast<follow*>(mapaComponentes.at("follow"));
	followEnem->setTarget(target);
	followEnem->doFollow();
	following = true;
}