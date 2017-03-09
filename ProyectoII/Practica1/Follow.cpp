#include "Follow.h"
#include "EstadoPG.h"
#include "ColisionBox.h"

Follow::Follow(ObjetoJuego* ent, ObjetoPG* tg) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	target = tg;
	paso = 20;
	following = false;
	hitInfo = nullptr;
}



Follow::~Follow()
{
}
Punto Follow:: sigDireccion(int dir){
	Punto aux;
	switch (dir)
	{
	case 0: aux.x = pObj->getRect().x + paso; aux.y = pObj->getRect().y+0; //Derecha
		break;
	case 1: aux.x = pObj->getRect().x - paso; aux.y = pObj->getRect().y +0; //Izquierda
		break;
	case 2: aux.x = pObj->getRect().x + 0; aux.y = pObj->getRect().y - paso; // Arriba;
		break;
	case 3: aux.x = pObj->getRect().x + 0; aux.y = pObj->getRect().y+paso; // Abajo;
		break;
	case 4: aux.x = pObj->getRect().x + paso; aux.y = pObj->getRect().y - paso; //dDS
		break;
	case 5: aux.x = pObj->getRect().x + paso; aux.y = pObj->getRect().y+paso; //dDI
		break;
	case 6: aux.x = pObj->getRect().x - paso; aux.y = pObj->getRect().y - paso; //dIS
		break;
	case 7: aux.x = pObj->getRect().x - paso; aux.y = pObj->getRect().y+paso; //dII
		break;
	default:
		break;
	}
	return aux;
}
bool Follow::esValida(int k){
	std::cout << "Validando\n";
	if (static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(path[k], hitInfo) == 1) return false;
	bool valida = true;
	int i = 0;
	while (i < k && valida){
		if (path[i].x == path[k].x && path[i].y == path[k].y) valida = false;
		i++;
	}
	return valida;

}
void Follow:: calculaPath(int k, bool &exito){
	int dir = 0;
	while (dir < 8 && !exito){
		path.push_back(sigDireccion(dir));
		if (esValida(k)){
			if (path[k].x == target->getRect().x && path[k].y == target->getRect().y )
			{
				std::cout << "He encontrado un camino debuti loco \n"; exito = true;
			}
			else{ // marcar
				//marcas[sol[k].fila][sol[k].col] = true;
				calculaPath(k + 1, exito);
				//desmarcar
				//marcas[sol[k].fila][sol[k].col] = F;
			}
		}
		else path.pop_back();
		dir++;
	}
}

void Follow::calculaPath(){
	vecDir.x = target->getRect().x - pObj->getRect().x;
	vecDir.y = target->getRect().y - pObj->getRect().y;
	if (vecDir.x < 0) signoX = -1;
	else signoX = 1;
	if (vecDir.y < 0) signoY = -1;
	else signoY = 1;
	bool aux = false;
	std::cout << "Here\n";
	calculaPath(0, aux);

}
void Follow::update(){
	if (pObj->getPJuego()->input.follow){
		pObj->getPJuego()->input.follow = false;
		following = true;
		calculaPath();
	}
}
