#include "Lobo.h"
#include "Deteccion.h"
#include "Attack.h"


Lobo::Lobo(juegoPG *juego, Cazador* hunter, Recolector* collector, GrafoMapa* mapa, int px, int py) :Enemigo(juego, hunter, collector, mapa, px, py)
{
	enemigo = true;
	nombre.push_back("Lobo");
	activo = true;
	//interactuable = true;
	damage = 50;
	if (rand() % 2 == 0) et = TLoboB; else et = TLobete;//Añadir TLobo al array de texturas
	absRect.w = rect.w = 105;
	absRect.h = rect.h = 70;//Lo que quiero que ocupe en pantalla
	anim.w = 350;
	anim.h = 250;
	life = 5;
	anim.x = anim.y = 0;//Lo que quiero que se vea del sprite
	SDL_Rect aux; aux.x = rect.x; aux.y = rect.y + 30; aux.w = 80; aux.h = 20;
	newComponente(new ColisionBox(this,aux,false), "ColisionBox");
	newComponente(new Attack(this), "Attack");
	newComponente(new Deteccion(this,500),"Deteccion");
	newComponente(new follow(this, hunter, mapa, false), "follow");
	followEnem = dynamic_cast<follow*>(mapaComponentes.at("follow"));
	setEstado(Quieto);
}


Lobo::~Lobo()
{
}

void Lobo::setEstado(EstadoEnemigo est){ estado = est; static_cast<Deteccion*>(dameComponente("Deteccion"))->cont = 0; }
/*
void Lobo::update() {
	ObjetoPG::update();
	rect.x += 2;
	rect.y += 0.2;
	
}*/
void Lobo::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), anim, rect, alpha);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}