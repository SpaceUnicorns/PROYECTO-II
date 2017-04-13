#include "ObjetoHuella.h"
#include "Huella.h"

ObjetoHuella::ObjetoHuella(int ind, Componente* comp, juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = THuella;
	rect.w = 45;
	rect.h = 55;
	timer = 0;
	componente = static_cast<Huella*>(comp);
	indice = ind;
}


ObjetoHuella::~ObjetoHuella()
{
}
void ObjetoHuella::update(){
	timer++;
	if (timer == 300){
		timer = 0;
		componente->quitaHuella(indice);
	}
}
void ObjetoHuella::draw(){
	// cambiar este metodo al update, y llamar al update desde cada entidad
	rect.y -= dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara().y;
	rect.x -= dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara().x;

	pJuego->getTextura(THuella)->draw(pJuego->getRender(), rect);
}
