#include "Lobo.h"
#include "Deteccion.h"
#include "Attack.h"


Lobo::Lobo(juegoPG *juego, Cazador* hunter, Recolector* collector, int px, int py):Enemigo(juego,hunter,collector, px,py)
{
	nombre.push_back("lobo");
	activo = true;
	//interactuable = true;
	damage = 1;
	et = TLobete;//Añadir TLobo al array de texturas
	rect.w = 80;
	rect.h = 50;//Lo que quiero que ocupe en pantalla
	anim.w = 238;
	anim.h = 155;
	anim.x = anim.y = 0;//Lo que quiero que se vea del sprite
	SDL_Rect aux; aux.x = rect.x; aux.y = rect.y + 30; aux.w = 80; aux.h = 20;
	newComponente(new ColisionBox(this,aux,false), "ColisionBox");
	newComponente(new Attack(this), "Attack");
	newComponente(new Deteccion(this,200),"Deteccion");
}


Lobo::~Lobo()
{
}/*
void Lobo::update() {
	ObjetoPG::update();
	rect.x += 2;
	rect.y += 0.2;
	
}*/
void Lobo::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Enemigo::draw();
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}