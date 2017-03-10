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
	//cutradamaxima borrar.
	int estimacion;
	ObjetoPG *pObj;
private:
	void calculaPath();
	void calculaPath(int k, bool &exito);
	Punto sigDireccion(int dir, int k);
	bool esValida(int k);
	ObjetoPG * hitInfo;	

	std::vector<Punto> path;
	ObjetoPG* target;
	bool following;
	int signoY, signoX, paso;
	Punto vecDir;
	Punto nextPos;
};

