#include "CabañaObj.h"
#include "ColisionBox.h"
#include "Nivel1.h"
#include "autoSave.h"

CabañaObj::CabañaObj(juegoPG * juego, int px, int py) : ObjetoPG(juego, px, py)
{
	nombre = "Cabaña";
	et = TCabaña;
	interactuable = false;
	rect.w = 300;
	rect.h = 200;
	absRect.w = rect.w;
	absRect.h = rect.h;
	SDL_Rect aux; aux.x = rect.x + 33; aux.y = rect.y + 185; aux.w = 33; aux.h = 15;
	newComponente(new ColisionBox(this, aux, false), "ColisionBox");
	
	saved = false;
}


CabañaObj::~CabañaObj()
{
}

void CabañaObj::update() {
	if (cazadorIn() || recolectorIn()) { //onCollision
		std::cout << "COLISION SUPREMA\n";

		if (!saved) {
			autoSave* save = new autoSave(static_cast<Nivel1*>(pJuego->estados.top()));
			save->Guardar();
			
			delete save;
			saved = true;
		}
	}

	else {
		saved = false;
	}
}

bool CabañaObj::compruebaRadio(SDL_Rect target) 
{
	float centroY = target.h / 2 + target.y; 
	float centroX = target.w / 2 + target.x;
	float distancia = pow(rect.x - centroX, 2) + pow(rect.y - centroY, 2);
	return distancia <= pow(200, 2); //200 = RADIO
}

bool CabañaObj::cazadorIn() {
	SDL_Rect recC = static_cast<Nivel1*>(pJuego->estados.top())->getCazador()->getRect();
	return compruebaRadio(recC);
}

bool CabañaObj::recolectorIn() {
	SDL_Rect recR = static_cast<Nivel1*>(pJuego->estados.top())->getRecolector()->getRect();
	return compruebaRadio(recR);
}

void CabañaObj::draw() { //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	pJuego->getTextura(et)->draw(pJuego->getRender(), rect);
	static_cast<ColisionBox*>(mapaComponentes.at("ColisionBox"))->draw();
}