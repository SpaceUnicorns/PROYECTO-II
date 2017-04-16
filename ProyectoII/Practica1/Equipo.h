#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Mochila.h"
class Equipo :
	public Componente
{

	enum Equipamento{Nada, Trampa, Antorcha, Hacha};
public:
	Equipo(ObjetoJuego* entidad, Mochila* moch);
	virtual ~Equipo();
	virtual void update();
	void setEquipo(std:: string equip, int num) {
		if (equip == "Trampa") equipado = Trampa;
		else if (equip == "Antorcha") equipado = Antorcha;
		else if (equip == "Hacha") equipado = Hacha;
		else equipado = Nada;

		cantidad = num;
	};
private:
	ObjetoPG* pObj;
	Mochila* mochila;
	Equipamento equipado;
	int cantidad;
};

