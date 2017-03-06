#pragma once
#include "Componente.h"
#include "Cazador.h"
class Follow :
	public Componente
{
public:
	Follow(ObjetoJuego* ent, ObjetoPG* target);
	virtual ~Follow();
	//Métodos--------------------------------------------------
	virtual void update();

	ObjetoPG *pObj;
private:
	ObjetoPG * hitInfo;	
	struct vec {
		int x, y;
	};
	struct esq{
		bool esquivando;
		int cont;
	};
	esq esquivandoH, esquivandoV;

	ObjetoPG* target;
	int signoY, signoX;
	vec vecDir;
	Punto nextPos;
};

