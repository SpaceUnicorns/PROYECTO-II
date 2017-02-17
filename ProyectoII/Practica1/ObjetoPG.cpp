#include "ObjetoPG.h"


ObjetoPG::ObjetoPG(juegoPG * juego, int px, int py)
{
	pJuego = juego;
	rect.x = px;
	rect.y = py;
	start();
	
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

void ObjetoPG::awake(){}
void ObjetoPG::sleep(){}
void ObjetoPG::start(){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (it != itFin){
		it->second->start();
		it++;
	}
}
void ObjetoPG::update(){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (it != itFin){
		it->second->update();
		it++;
	}
}
void ObjetoPG::lateUpdate(){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (it != itFin){
		it->second->lateUpdate();
		it++;
	}
}
void ObjetoPG::swAble(){
	if (activo) sleep();
	else awake();
	activo = !activo;
}
