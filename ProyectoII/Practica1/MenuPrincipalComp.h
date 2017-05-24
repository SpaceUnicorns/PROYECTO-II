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
	virtual void update(int delta);
	virtual ~MenuPrincipalComp();
	int showMessage(const char* s, bool info = false);
private:
	int temp, temp2, delay;
	estadosMP estado;
	ObjetoPG *pObj;
};

