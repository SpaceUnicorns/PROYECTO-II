#pragma once
#include "Nivel1.h"
#include "Mochila.h"

class autoSave
{
public:
	autoSave(Nivel1* n);
	~autoSave();

	void Guardar();
	void mapear(Mochila* m, std::vector<std::string>& v);

private:
	//Posicion de los personajes
	int xCazador, yCazador;
	int xRecolector, yRecolector;
	//Ultimo personaje activo
	std::string activo;
	//Mochila
	Mochila* mochila;
	std::vector<std::string> items;
};

