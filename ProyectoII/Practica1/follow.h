#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "GrafoMapa.h"
#include "ColisionBox.h"
class follow :
	public Componente
{
public:
	follow(ObjetoJuego* ent, ObjetoPG* target, GrafoMapa* m, bool aliado);
	virtual ~follow();
	virtual void lateUpdate();
	void doFollow();
protected:
	GrafoMapa* map;
	bool al;
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

