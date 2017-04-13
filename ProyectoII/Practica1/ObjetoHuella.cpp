#include "ObjetoHuella.h"
#include "Huella.h"

ObjetoHuella::ObjetoHuella(int dir, int ind, Componente* comp, juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	et = THuella;
	rect.w = 45;
	rect.h = 55;
	anim.h = 32;
	anim.w = 32;
	anim.x = anim.y = 0;
	timer = 0;
	componente = static_cast<Huella*>(comp);
	indice = ind;
	Dir state = (Dir) dir;
	setAnim(state);
	alpha = 255;
}

void ObjetoHuella::setAnim(Dir dir){
	switch (dir)
	{
	case Arriba: changeAnimV(3);
		break;
	case DDS: changeAnimV(7);
		break;
	case Derecha: changeAnimV(2);
		break;
	case DDI: changeAnimV(5);
		break;
	case Abajo: changeAnimV(0);
		break;
	case DII: changeAnimV(4);
		break;
	case Izquierda: changeAnimV(1);
		break;
	case DIS: changeAnimV(6);
		break;
	default:
		break;
	}
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
	if (alpha > 0) alpha--;
}
void ObjetoHuella::draw(){
	// cambiar este metodo al update, y llamar al update desde cada entidad
	rect.y -= dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara().y;
	rect.x -= dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara().x;

	pJuego->getTextura(THuella)->draw(pJuego->getRender(), anim, rect,alpha);
}
