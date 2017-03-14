#include "Piedra.h"


Piedra::Piedra(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;
	et = TPiedra;
	rect.w = 50;
	rect.h = 30;
	nombre = typeid(this).name();
	SDL_Rect colision = { rect.x,rect.y+10,50,10 };
	newComponente(new ColisionBox(this,colision,false), "ColisionBox");
}


Piedra::~Piedra()
{
	
	deleteComponente("ColisionBox");
}
void Piedra::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}
