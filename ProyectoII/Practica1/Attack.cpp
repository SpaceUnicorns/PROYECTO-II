#include "Attack.h"
#include "Enemigo.h"
#include "ColisionBox.h"

Attack::Attack(ObjetoJuego* entidad) :Componente(entidad)
{
	posicion = { 0, 0 };
	
}


Attack::~Attack()
{
}

void Attack::update(){
	posicion = { static_cast<Enemigo*>(pEntidad)->getColisionBox().x + static_cast<Enemigo*>(pEntidad)->getColisionBox().w * 0.8 , static_cast<Enemigo*>(pEntidad)->getColisionBox().y };
	
	
	//static_cast<ColisionBox*>(static_cast<Enemigo*>(pEntidad)->dameComponente("ColisionBox"))->isColiding(posicion, info);
	
	if (static_cast<Enemigo*>(pEntidad)->getTarget() != nullptr){
		if (posicion.compruebaRadio(static_cast<Enemigo*>(pEntidad)->getTarget()->getColisionBox(), 35)){

			//Hace la animación
			//El jugador deberá tener algo que lo haga inmune a daño un ratele después de recibir un ataques
			std::string nombrefacha = static_cast<Enemigo*>(pEntidad)->getTarget()->nombre;
			static_cast<Enemigo*>(pEntidad)->getPJuego()->cambiaVida(-static_cast<Enemigo*>(pEntidad)->damage);
			//std::cout << "\n\n\nLa vida de " << nombrefacha << " ha disminuido " << static_cast<Enemigo*>(pEntidad)->damage << " puntos de salud.\n\n";
		}
	}
	
}