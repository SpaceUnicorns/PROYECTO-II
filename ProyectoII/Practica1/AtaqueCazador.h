#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "ColisionBox.h"
#include "Equipo.h"
#include "MovimientoP.h"
class AtaqueCazador :
	public Componente
{
public:
	AtaqueCazador(ObjetoJuego* ent);
	virtual ~AtaqueCazador();
	virtual void update(int delta);
	ObjetoPG* info = nullptr;
	ObjetoPG *pObj;
	Direc direccion;
	void setAxResistance(int x){
		axResistance = x;
	};
	int getAxResistance(){ return axResistance; }
private:
	int axResistance;
	bool firstime;
	Equipo* equipo;
	MovimientoP* compMov;
	Punto nextPos;
	ColisionBox * pCBox;
	EstadoPG* pEstado;
};

