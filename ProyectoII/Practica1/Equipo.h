#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Mochila.h"
class Equipo :
	public Componente
{

	enum Equipamento{Nada, Trampa, Antorcha, Hacha,Pala, Pico};
public:
	Equipo(ObjetoJuego* entidad, Mochila* moch);
	virtual ~Equipo();
	virtual void update();
	int getEquipo(){ return equipado; };
	bool tieneEquipo(std::string equip){
		Equipamento aux;
		if (equip == "Trampa") aux = Trampa;
		else if (equip == "Antorcha") aux = Antorcha;
		else if (equip == "Hacha") aux = Hacha;
		else if (equip == "Pala") aux = Pala;
		else if (equip == "Pico") aux = Pico;
		else aux = Nada;

		return aux == equipado;
	}
	void setEquipo(std:: string equip, int num) {
		if (equip == "Trampa") equipado = Trampa;
		else if (equip == "Antorcha") equipado = Antorcha;
		else if (equip == "Hacha") equipado = Hacha;
		else if (equip == "Pala") equipado = Pala;
		else if (equip == "Pico") equipado = Pico;
		else equipado = Nada;

		cantidad = num;
	};
private:
	ObjetoPG* pObj;
	Mochila* mochila;
	Equipamento equipado;
	int cantidad;
};

