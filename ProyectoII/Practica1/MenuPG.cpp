#include "MenuPG.h"


MenuPG::MenuPG(juegoPG*jug, int puntos) :EstadoPG(jug, puntos)
{
   //Screen dimension 640 x 480
	et = TMenu;
	play = new Boton(pJuego, 192, 290, TBotonJ,jugar);
	vecObj.push_back(play);
	exit = new Boton(pJuego, 192, 190, TBotonS, salir);
	vecObj.push_back(exit);
}


MenuPG::~MenuPG()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}
