#include "Mochila.h"



Mochila::Mochila(ObjetoJuego* ent): Componente(ent)
{
}


Mochila::~Mochila()
{
}

void Mochila::newItem(std::string const & name, int cantidad)
{
	if (!findItem(name))	mochilaRecolector.insert(std::pair<std::string, int>(name, cantidad));
	else mochilaRecolector.at(name) += cantidad;
	std::cout <<"Tienes "<< mochilaRecolector.at(name)<< " " << name<<"\n";
}

void Mochila::removeItem(std::string const & name, int cantidad)
{
	if (findItem(name)) mochilaRecolector.at(name) -= cantidad;

	if (mochilaRecolector.at(name) <= 0)
		mochilaRecolector.erase(name);
}

bool Mochila::findItem(std::string const & name)
{ 
	try {
		mochilaRecolector.at(name);
		return true;
	}
	catch (std::out_of_range & e) {
		return false;
	}
	
}

int Mochila::getCantidad(std::string const & name) const {
	return mochilaRecolector.at(name);
}