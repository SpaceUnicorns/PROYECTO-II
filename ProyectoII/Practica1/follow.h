#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "GrafoMapa.h"
#include "ColisionBox.h"
class follow :
	public Componente
{
public:
	follow(ObjetoJuego* ent, ObjetoPG* target, GrafoMapa* m);
	virtual ~follow();
	virtual void lateUpdate();
protected:
	GrafoMapa* map;
	//std::vector<std::pair<int, int>> path;
	std::vector<void*> path;
	ObjetoPG* target;
	float coste, paso;
	bool following;
	int signoY, signoX, cont;
	Punto vecDir;
	Punto nextPos;
	ObjetoPG * hitInfo;
	ObjetoPG *pObj;
	std::vector<int> direccion;
};

