#include "AtaqueZ.h"
#include "ColisionBox.h"
#include "Cazador.h"

AtaqueZ::AtaqueZ(ObjetoJuego* entidad) : Componente(entidad)
{
	rect.x = static_cast<Cazador*>(entidad)->getRect().x + 50;
	rect.y = static_cast<Cazador*>(entidad)->getRect().y + 20;
	rect.w = 20;
	rect.h = 20;
	//newComponente(new ColisionBox(this, rect, true), "AttackBox");
	atacando = false;
}


AtaqueZ::~AtaqueZ()
{
}

void AtaqueZ::update() {
	if (atacando) { Attack(); }


}


void AtaqueZ::Attack() {

	movimiento();

	atacando = false;

}

