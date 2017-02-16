#include "Pausa.h"


Pausa::Pausa(juegoPG*jug, int puntos) :EstadoPG(jug, puntos)
{
	//Screen dimension 640 x 480
	et = TMenu;
	menu = new Boton(pJuego, 192, 290,TBotonM, goMenu);
	vecObj.push_back(menu);
	resume = new Boton(pJuego, 192, 190,TBotonV, setResume);
	vecObj.push_back(resume);
}


Pausa::~Pausa()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}