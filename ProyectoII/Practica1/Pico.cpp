#include "Pico.h"
#include "ColisionBox.h"


Pico::Pico(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	interactuable = true;
	et = TPico;
	rect.w = 80;
	rect.h = 40;
	nombre[0] = "1";
	nombre.push_back("Pico");
	receta.push_back("1");
	receta.push_back("Madera");
	receta.push_back("1");
	receta.push_back("Hueso");
	receta.push_back("1");
	receta.push_back("Cuerda");

	SDL_Rect colision = { rect.x, rect.y + 10, 50, 10 };
	newComponente(new ColisionBox(this, colision, false), "ColisionBox");

}


Pico::~Pico()
{
}
void Pico::draw() {
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}