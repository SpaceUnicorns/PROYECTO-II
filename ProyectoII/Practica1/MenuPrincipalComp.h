#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
#include "Nivel1.h"
#include "MenuPrincipal.h"
class MenuPrincipalComp :
	public Componente
{
	enum estadosMP {Jugar, Salir, Cargar};
public:
	MenuPrincipalComp(ObjetoJuego* ent);
	virtual void update();
	virtual ~MenuPrincipalComp();
	int showMessage();
private:
	int temp, temp2, delay;
	estadosMP estado;
	ObjetoPG *pObj;
};

