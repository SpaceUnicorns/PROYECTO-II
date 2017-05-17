#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include <map>
class Mochila: public Componente
{
public:
	Mochila(ObjetoJuego* ent);
	~Mochila();
	 void newItem( std::string const & name, int cantidad);
	 void removeItem(std::string const & name, int cantidad);
	 bool findItem(std::string const & name);
	 void vaciaMochila(){
		 mochilaRecolector.erase(mochilaRecolector.cbegin(), mochilaRecolector.cend());
	 }

	 int getCantidad(std::string const & name);
private:
	std::map<std::string, int> mochilaRecolector;
	ObjetoPG *pObj;
};

