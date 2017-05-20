	#include "MenuPG.h"


MenuPG::MenuPG(juegoPG*jug, int puntos) :EstadoPG(jug, puntos)
{
	et = TMenu;

	int auxH = pJuego->getScreenHeight() / 2 - 21; //21 = buton.h / 2
	int auxW = pJuego->getScreenWidth() / 2 + 100;

	play = new Boton(pJuego, auxW, auxH - 100, TBotonJ,jugar); //arriba
	vecObj.push_back(play);

	cargar = new Boton(pJuego, auxW, auxH, TBotonC, jugar); //medio
	vecObj.push_back(cargar);

	exit = new Boton(pJuego, auxW, auxH + 100, TBotonS, salir); //abajo
	vecObj.push_back(exit);

	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxMCrafteo.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceMusica("Galiakberova", false);

	vecObj.push_back(new MenuPrincipal(pJuego,192,260));

	EstadoPG::setAutoSnow();
}


MenuPG::~MenuPG()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}