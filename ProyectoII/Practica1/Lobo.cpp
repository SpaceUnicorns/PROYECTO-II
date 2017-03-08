#include "Lobo.h"



Lobo::Lobo(juegoPG *juego, int px, int py):Enemigo(juego,px,py)
{
	et = TLobete;//Añadir TLobo al array de texturas
	rect.w = 80;
	rect.h = 50;//Lo que quiero que ocupe en pantalla
	anim.w = 238;
	anim.h = 155;
	anim.x = anim.y = 0;//Lo que quiero que se vea del sprite
	newComponente(new ColisionBox(this), "ColisionBox");
	setColisionBox(80, 50);
}


Lobo::~Lobo()
{
}

void Lobo::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}