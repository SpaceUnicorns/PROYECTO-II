#include "autoSave.h"

autoSave::autoSave(Nivel1* nivel)
{
	//Posicion de los personajes
	xCazador = nivel->getCazador()->getRect().x; //INTs
	yCazador = nivel->getCazador()->getRect().y;
	xRecolector = nivel->getRecolector()->getRect().x;
	yRecolector = nivel->getRecolector()->getRect().y;

	//Ultimo personaje activo
	activo = nivel->getActivePlayer(); //STRING

	//Mochila
	mochila = nivel->getRecolector()->dameComponente("Mochila");
}


autoSave::~autoSave() {}


void autoSave::Guardar() {
	std::ofstream myfile;
	myfile.open("../docs/autoSave.txt");
		//Posicion de los personajes
		myfile << xCazador << "\n";
		myfile << yCazador << "\n";
		myfile << xRecolector << "\n";
		myfile << yRecolector << "\n";
		//Ultimo personaje activo
		myfile << activo << "\n";
		//Mochila

			
	myfile.close();




	/*
	PARA EL SCRIPT DE LOAD


	string line;
	ifstream myfile ("../docs/autoSave.txt");
	if (myfile.is_open())
	{

		while ( getline (myfile,line) ) //CAMBIAR SEGUN SE NECESITE
		{
			cout << line << '\n';
		}
	
		myfile.close();
	}
	else cout << "Unable to open file";
	*/
}