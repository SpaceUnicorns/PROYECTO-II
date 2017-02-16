#include "GameOver.h"


GameOver::GameOver(juegoPG*jug,int puntos) :EstadoPG(jug, puntos)
{
	
	//Screen dimension 640 x 480
	et = TMenu;
    menu = new Boton(pJuego, 192, 240,TBotonM, goMenu);
	vecObj.push_back(menu);
}


GameOver::~GameOver()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}