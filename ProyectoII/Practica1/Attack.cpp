#include "Attack.h"
#include "Enemigo.h"
#include "ColisionBox.h"

Attack::Attack(ObjetoJuego* entidad) :Componente(entidad)
{
	posicion = { 0, 0 };
	cont = 0;
	enemigo = dynamic_cast<Enemigo*>(pEntidad);
}


Attack::~Attack()
{
}

void Attack::update(int delta){
	posicion = { (int)(enemigo->getColisionBox().x + enemigo->getColisionBox().w * 0.8), (enemigo->getColisionBox().y) };
	
	//static_cast<ColisionBox*>(static_cast<Enemigo*>(pEntidad)->dameComponente("ColisionBox"))->isColiding(posicion, info);
	cont+=delta;
	if (enemigo->getTarget() != nullptr){
		if (posicion.compruebaRadio(enemigo->getTarget()->getColisionBox(), 100) && enemigo->getEstado() == Atacando){
			if (cont >= 1300){
				//Hace la animación
				//El jugador deberá tener algo que lo haga inmune a daño un ratele después de recibir un ataques
				std::string nombre = enemigo->getTarget()->nombre[1];
				enemigo->getPJuego()->cambiaVida(-enemigo->damage);
				std::cout << "\n\n\nLa vida de " << nombre << " ha disminuido " << enemigo->damage << " puntos de salud.\n\n";
				enemigo->getTarget()->herido = true;

				enemigo->getPJuego()->getEstadoActual()->reproduceFx("Golpe", enemigo->getRect().x, enemigo->getRect().y, 0);
				if (nombre == "Zhenia"){ enemigo->getPJuego()->getEstadoActual()->reproduceFx("ZheniaDano", enemigo->getRect().x, enemigo->getRect().y, 0); }
				else { enemigo->getPJuego()->getEstadoActual()->reproduceFx("LyovDano", enemigo->getRect().x, enemigo->getRect().y, 0); }
				cont = 0;
			}
		}
	}
	
}