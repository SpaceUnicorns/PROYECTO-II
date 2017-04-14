#include "Enemigo.h"
#include "Nivel1.h"

Enemigo::Enemigo(juegoPG * juego, Cazador* hunter, Recolector* collector, int px, int py) : ObjetoPG (juego,px,py),
cazador(hunter), recolector(collector), estado(EstadoEnemigo::Quieto)
{
	activo = true;
	//newComponente(new follow(this, objetivo, dynamic_cast<Nivel1*>(pJuego->getEstadoActual())->getGrafoMapa(), false), "follow");
	posIni.x = px;
	posIni.y = py;
	objetivo = nullptr;
	dameUnHogar();
}

void Enemigo::dameUnHogar() {
	casita = new ObjetoPG(pJuego, posIni.x, posIni.y);
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
	if (!encuentraComponente("follow")) {
		newComponente(new follow(this, objetivo, dynamic_cast<Nivel1*>(pJuego->getEstadoActual())->getGrafoMapa(), false), "follow");
	}
	
	dynamic_cast<follow*>(mapaComponentes.at("follow"))->setTarget(objetivo);
	dynamic_cast<follow*>(mapaComponentes.at("follow"))->doFollow();
	//std::cout << "MANOLITO SILVERFEET" << "\n";
}

void Enemigo::desactivaFollow() {
	dynamic_cast<follow*>(mapaComponentes.at("follow"))->setTarget(casita);
	dynamic_cast<follow*>(mapaComponentes.at("follow"))->doFollow();
}