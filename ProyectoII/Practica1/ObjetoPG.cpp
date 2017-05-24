#include "ObjetoPG.h"
#include "ColisionBox.h"
#include "checkML.h"
#include "Equipo.h"

ObjetoPG::ObjetoPG(juegoPG * juego, int px, int py)
{
	pJuego = juego;
	rect.x = px;
	rect.y = py;
	start();
	absRect = rect;
	nombre.push_back("default");
	alpha = 255;
	detectable = true;
	bool desaparece = true;
	terreno = 0; // 0 nieve, 1 madera, 2 piedra, 3 tierra;
}

ObjetoPG::~ObjetoPG(){

	std::map <std::string, Componente*>::iterator it = mapaComponentes.begin();
	while (it != mapaComponentes.end()){
		delete it->second;
		it++;
	}
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
void ObjetoPG::lateDraw(){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (it != itFin){
		it->second->lateDraw();
		it++;
	}
}
void ObjetoPG::awake(){}
void ObjetoPG::sleep(){}
void ObjetoPG::newComponente(Componente* cmp, std:: string const & name){
	if (!encuentraComponente(name))	mapaComponentes.insert(std::pair<std::string, Componente*>(name, cmp));
}

void ObjetoPG::deleteComponente(std::string const & name){
	if (encuentraComponente(name)){
		Componente * aux = mapaComponentes.at(name);
		mapaComponentes.erase(name);
		delete aux;
	}
}
bool ObjetoPG::encuentraComponente(std::string const & name){
	try{
		mapaComponentes.at(name);
		return true;
	}
	catch (std::out_of_range & e){
		std::cout << "No he encontrado el componente: " << name << "\n";
		return false;
	}
}
void ObjetoPG::start(){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (it != itFin){
		it->second->start();
		it++;
	}
}
void ObjetoPG::update(int delta){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (it != itFin){
		it->second->update(delta);
		it++;
	}
}
void ObjetoPG::lateUpdate(int delta){
	std::map <std::string, Componente*>::const_iterator it = mapaComponentes.cbegin();
	std::map <std::string, Componente*>::const_iterator itFin = mapaComponentes.cend();

	while (it != itFin){
		it->second->lateUpdate(delta);
		it++;
	}
}
void ObjetoPG::swAble(){
	if (activo) sleep();
	else awake();
	activo = !activo;
}
