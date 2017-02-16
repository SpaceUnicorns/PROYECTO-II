#include "ObjetoPG.h"


ObjetoPG::ObjetoPG(juegoPG * juego, int px, int py)
{
	pJuego = juego;
	rect.x = px;
	rect.y = py;
	
}


ObjetoPG::~ObjetoPG()
{
}

bool ObjetoPG::dentro(int x, int y)const{
	int xMax = rect.x + rect.w;
	int yMax = rect.y + rect.h; 
	return x < xMax && x > rect.x && y < yMax && y > rect.y;
}

bool ObjetoPG::onClick(){
	bool encontrado = false;
	int mx, my;
	pJuego->getMousePos(mx, my);
	if (dentro(mx, my)){
		encontrado = true;
	}
	return encontrado;
}
bool ObjetoPG::onOver(){
	bool encontrado = false;
	int mx, my;
	pJuego->getMousePos(mx, my);
	if (dentro(mx, my)){
		encontrado = true;
	}
	return encontrado;
}
void ObjetoPG::draw(){
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
}
