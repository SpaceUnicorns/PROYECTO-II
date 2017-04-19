#include "Load.h"
#include <fstream>
#include <iostream>  // la consola: cin / cout
#include "Nivel1.h"
#include "Mochila.h"

Load::Load(Nivel1* n) : nivel(NULL)
{
	nivel = n;
	Cargar();
}

Load::~Load() {}

void Load::Cargar() {
	std::string line;
	std::ifstream myfile("../docs/autoSave.txt");

	if (myfile.is_open())
	{
		//Posicion de los personajes
		int x, y;

		std::cin >> x;
		std::cin >> y;
		nivel->setCazador(x, y);

		std::cin >> x;
		std::cin >> y;
		nivel->setRecolector(x, y);

		//Ultimo personaje activo
		std::string aux;
		std::cin >> aux;
		nivel->setActivePlayer(aux);

		//Mochila
		std::cin >> x; //nº elementos
		for (int i = 0; i < x; i++) {
			std::cin >> aux;
			static_cast<Mochila*>(nivel->getRecolector()->dameComponente("Mochila"))->newItem(aux, 1);
		}

		//FALTARIAN LOS OBSTACULOS
		//IMPLEMENTAR CUANDO ESTÉN HECHOS

		myfile.close();
	}
	else std::cout << "Unable to open file\n";

}