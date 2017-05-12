	#include "MenuPG.h"


MenuPG::MenuPG(juegoPG*jug, int puntos) :EstadoPG(jug, puntos)
{
   //Screen dimension 640 x 480
	et = TMenu;
	play = new Boton(pJuego, 192, 260, TBotonJ,jugar);
	vecObj.push_back(play);
	exit = new Boton(pJuego, 192, 160, TBotonS, salir);
	vecObj.push_back(exit);
	cargar = new Boton(pJuego, 192, 360, TBotonC, jugar);
	vecObj.push_back(cargar);
	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxMCrafteo.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceMusica("Galiakberova", false);
	vecObj.push_back(new MenuPrincipal(pJuego,192,260));
}


MenuPG::~MenuPG()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}
