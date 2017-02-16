#include "EstadoPG.h"
#include "Error.h"


EstadoPG::EstadoPG(juegoPG*jug,int puntos)
{
	pJuego = jug;
	fondo.h = 480;
	fondo.w = 640;
	fondo.x = fondo.y = 0;
	colorFuente.r = 130;
	colorFuente.g = 214;
	colorFuente.b = 28;
	contPuntos = puntos;
}


EstadoPG::~EstadoPG()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}

void EstadoPG::draw(){
	//Draw background
	pJuego->getTextura(et)->draw(pJuego->getRender(), fondo);
	drawFont();

	for (unsigned int i = 0; i < vecObj.size(); i++)
		vecObj[i]->draw();


}
void EstadoPG::drawFont(){
	//Dibujar puntos
	try{// bloque try catch
			pJuego->getFuente()->loadFromText(pJuego->getRender(), std::to_string(contPuntos), colorFuente);
			pJuego->getFuente()->draw(pJuego->getRender(), pJuego->getFuente()->font.recFont);
		}
		catch (ELoadFont & e){}
	}

void EstadoPG::update(){
	for (unsigned int i = 0; i < vecObj.size(); i++){
		vecObj[i]->update();
	}
}
void EstadoPG::onClick(){
	bool encontrado = false;
	int it = vecObj.size() - 1;
	while (!encontrado && it >= 0){
		encontrado = vecObj[it]->onClick();
		it--;
	}
}
void EstadoPG::onOver(){
	bool encontrado = false;
	int it = vecObj.size() - 1;
	while (!encontrado && it >= 0){
		encontrado = vecObj[it]->onOver();
		it--;
	}
}