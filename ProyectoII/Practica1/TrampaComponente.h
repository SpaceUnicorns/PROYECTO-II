#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "ColisionBox.h"
#include "Enemigo.h"
#include "Cazador.h"
#include "Recolector.h"
class TrampaComponente :
	public Componente
{
public:
	TrampaComponente(ObjetoJuego* entidad);
	virtual ~TrampaComponente();
	virtual void update(int delta);
private:
	ObjetoPG* pObj;
	int comprueba;
	ObjetoPG* pAux;
	std::vector<ObjetoJuego*> pVecObj;
};

