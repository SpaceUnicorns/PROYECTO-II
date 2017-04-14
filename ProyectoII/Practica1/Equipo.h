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
	void setEquipo(int equip, int num) { equipado = (Equipamento)equip; cantidad = num; };
private:
	ObjetoPG* pObj;
	Mochila* mochila;
	Equipamento equipado;
	int cantidad;
};

