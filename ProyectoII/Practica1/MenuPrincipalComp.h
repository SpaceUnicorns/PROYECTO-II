#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Nivel1.h"
#include "MenuPrincipal.h"
class MenuPrincipalComp :
	public Componente
{
	enum estadosMP {Jugar, Salir};
public:
	MenuPrincipalComp(ObjetoJuego* ent);
	virtual void update();
	virtual ~MenuPrincipalComp();
private:
	int temp, temp2;
	estadosMP estado;
	ObjetoPG *pObj;
};

