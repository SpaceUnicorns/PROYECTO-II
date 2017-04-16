#pragma once
#include "Nivel1.h"

class autoSave
{
public:
	autoSave(Nivel1* n);
	~autoSave();

	void Guardar();

private:
	//Posicion de los personajes
	int xCazador, yCazador;
	int xRecolector, yRecolector;
	//Ultimo personaje activo
	std::string activo;
	//Mochila
	Componente* mochila;
};

