#include "HuellasCamino.h"


HuellasCamino::HuellasCamino(juegoPG * juego, int px, int py, std:: string s) : ObjetoPG(juego, px, py)
{
	et = THuellasCamino;
	rect.w = 45;
	rect.h = 25;
	anim.w = 280; anim.h = 360;
	anim.y = 0;
	if (s == "HS") anim.x = 0;         //Huellas Hombre Superior
	else if (s == "HI") anim.x = 280;  //Huellas Hombre Inferior
	else if (s == "LS"){               //Huellas Lobo Superior
		anim.x = 560;	
		rect.w = 80;
		rect.h = 70;
	}
	else if (s == "LI"){	           //Huellas Lobo Inferior
		anim.x = 840;
		rect.w = 80;
		rect.h = 70;
	}
	nombre[0] = "1";
	nombre.push_back(s);
	alpha = 200;
	cont = 400;
}


HuellasCamino::~HuellasCamino()
{
}
void HuellasCamino::draw(bool dibuja) {
	cont--;
	aux = (dynamic_cast<EstadoPG*>(pJuego->estados.top())->getCamara());
	rect.x -= aux.x;
	rect.y -= aux.y;
	if (cont <= 0){
		cont = 400;
		if ((rand() % 7) % 3 == 0){
			if (!(rect.x > -200 && rect.x < pJuego->getScreenWidth() && rect.y > -200 && rect.y < pJuego->getScreenHeight())) alpha = rand() % 151 + 50;
		}
	}
	if (dibuja) pJuego->getTextura(et)->draw(pJuego->getRender(), anim, rect, alpha);
}