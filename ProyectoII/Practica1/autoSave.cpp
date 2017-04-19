#include "autoSave.h"

autoSave::autoSave(Nivel1* nivel) : mochila(NULL)
{
	//Ultimo personaje activo
	activo = nivel->getActivePlayer(); //STRING
	
   //Posicion de los personajes
	if (activo == "C") {
		xCazador = nivel->getCazador()->getRect().x; //INTs
		yCazador = nivel->getCazador()->getRect().y;

		xRecolector = xCazador - 50;
		yRecolector = yCazador;
	}

	else {
		xRecolector = nivel->getRecolector()->getRect().x;
		yRecolector = nivel->getRecolector()->getRect().y;

		xCazador = xRecolector - 50; //INTs
		yCazador = yRecolector;
	}

	//Mochila
	mochila = static_cast<Mochila*>(nivel->getRecolector()->dameComponente("Mochila"));
	mapear(mochila, items);

	//FALTARIA LOS OBSTACULOS
	//IMPLEMENTAR CUANDO ESTÉN HECHOS
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
		myfile << items.size() << "\n";
		for (size_t aux = 0; aux < items.size(); aux++) {
			myfile << items[aux] << "\n";
		}

	myfile.close();
}

void autoSave::mapear(Mochila* m, std::vector<std::string>& v) 
{
	std::vector<std::string> w { "Hacha", "Antorcha", "Pico", "Pala", "TrampaAbierta", "Madera",
		"Piedra", "Hueso", "Cebo", "Enredadera", "Yesca", "Cuerda", "TrampaCerrada" };

	for (size_t aux = 0; aux < w.size(); aux++) {
		if (m->findItem(w[aux])) {
			for (size_t i = 0; i < m->getCantidad(w[aux]); i++) {
				v.emplace_back(w[aux]);
			}
		}
	}
}