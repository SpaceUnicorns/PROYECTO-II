#include "Cazador.h"
#include "MovimientoP.h"


Cazador::Cazador(juegoPG * juego, int px, int py) : ObjetoPG(juego, px,py)
{
	
	et = TJugador;
	rect.w = 45;
	rect.h = 45;
	newComponente(new MovimientoP(this),"MovimientoP");
	newComponente(new ColisionBox(this), "ColisionBox");
	anim.w = anim.h = 32; //cada frame del jugador mide 32x32
	anim.x = anim.y = 0;
	pintado = false;
}


Cazador::~Cazador()
{
}
void Cazador::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pintado = true;
	//Conversión coordenadas mapa a cámara
	pJuego->getTextura(et)->draw(pJuego->getRender(),anim, rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}

void Cazador::update(){
	std::cout << "Player:: X: " << mapX<< " y: " << mapY << "\n";
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	rect.x = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamera().w) / 2;
	rect.y = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamera().h) / 2;
	while (it != itFin){
		it->second->update();
		it++;
	}
	
}