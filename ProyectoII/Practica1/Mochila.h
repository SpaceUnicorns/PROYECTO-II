#pragma once
#include "Componente.h"
#include <map>
class Mochila: public Componente
{
public:
	Mochila(ObjetoJuego* ent);
	~Mochila();
	 void newItem( std::string const & name, int cantidad);
	 void removeItem(std::string const & name, int cantidad);
	 bool findItem(std::string const & name);

	 int getCantidad(std::string const & name) const;

private:
	std::map<std::string, int> mochilaRecolector;
};

