#include "Follow.h"
#include "EstadoPG.h"
#include "ColisionBox.h"

Follow::Follow(ObjetoJuego* ent, ObjetoPG* tg) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	target = tg;
	paso = 120;
	following = false;
	hitInfo = nullptr;
	cont = 1;
}



Follow::~Follow()
{
}
Punto Follow:: sigDireccion(int dir, int k){
	Punto aux;
	
		switch (dir)
		{
		case 0: aux.x = path[k].x + paso; aux.y = path[k].y + 0; //Derecha 
			std::cout << "der\n";
			std::cout << "X: " << aux.x << " Y: " << aux.y << "\n";
			break;
		case 1: aux.x = path[k ].x - paso; aux.y = path[k].y + 0; //Izquierda
			std::cout << "izq\n";
			std::cout << "X: " << aux.x << " Y: " << aux.y << "\n";
			break;
		case 2: aux.x = path[k ].x + 0; aux.y = path[k].y - paso; // Arriba;
			std::cout << "arr\n";
			std::cout << "X: " << aux.x << " Y: " << aux.y << "\n";
			break;
		case 3: aux.x = path[k].x + 0; aux.y = path[k].y + paso; // Abajo;
			std::cout << "\n";
			std::cout << "X: " << aux.x << " Y: " << aux.y << "\n";
			break;
		case 4: aux.x = path[k].x + paso; aux.y = path[k].y - paso; //dDS
			break;
		case 5: aux.x = path[k].x + paso; aux.y = path[k].y + paso; //dDI
			break;
		case 6: aux.x = path[k].x - paso; aux.y = path[k].y - paso; //dIS
			break;
		case 7: aux.x = path[k].x - paso; aux.y = path[k].y + paso; //dII*/
			break;
		default:
			break;
		
	}
	return aux;
}
bool Follow::esValida(int k){
	std::cout << "Validando\n";
	if (path[k].x > path[0].x + pObj->getPJuego()->getScrenWidth() || path[k].x < path[0].x - pObj->getPJuego()->getScrenWidth()) return false;
	if (path[k].y > path[0].y + pObj->getPJuego()->getScrenHeight() || path[k].y < path[0].y - pObj->getPJuego()->getScrenHeight()) return false;
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
		path.push_back(sigDireccion(dir,k));
		if (esValida(k+1)){
			if (path[k+1].compruebaRadio(target->getColisionBox(),paso ))
			{
				std::cout << "He encontrado un camino debuti loco \n"; exito = true;
				return;
			}
			else{ // marcar
				//marcas[sol[k].fila][sol[k].col] = true;
				Punto ideal; ideal.x = abs(target->getColisionBox().x - pObj->getColisionBox().x);
				ideal.y = abs(target->getColisionBox().y - pObj->getColisionBox().y);
				Punto temp; temp.x = abs(target->getColisionBox().x - path[k + 1].x);
				temp.y = abs(target->getColisionBox().y - path[k + 1].y);
				if (temp.x < 2*temp.x || temp.y < 2*temp.y) 
				calculaPath(k + 1, exito);
				
			}
		}
		 path.pop_back();
		dir++;
	}
	/*while (dir < 4 && !exito){
		path.push_back(sigDireccion(dir, k));
		if (esValida(k + 1)){
			if (path[k + 1].compruebaRadio(target->getColisionBox(), paso))
			{
				std::cout << "He encontrado un camino debuti loco \n"; exito = true;
				return;
			}
			/*	else{ // marcar
			//marcas[sol[k].fila][sol[k].col] = true;


			}
		}


		dir++;
	}
	
		calculaPath(k + 1, exito);*/
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
	Punto au;
	au.x = pObj->getColisionBox().x; au.y = pObj->getColisionBox().y;
	path.push_back(au);
	estimacion = 0;
	calculaPath(0, aux);
	

}
void Follow::update(){
	if (pObj->getPJuego()->input.follow){
		pObj->getPJuego()->input.follow = false;
		if (pObj->getColisionBox().x > 1024 || pObj->getColisionBox().x < 0){
			std::cout << "Estas demasiado lejos";
		}
		else if (pObj->getColisionBox().y > 768 || pObj->getColisionBox().y < 0){
			std::cout << "Estas demasiado lejos";
		}
		else {
			following = true;
			calculaPath();
		}
	}
	if (following && cont < path.size()){
		std::cout << "moviendo\n";
		vecDir.x = path[cont].x - path[cont-1].x;
		vecDir.y = path[cont].y - path[cont-1].y;
		if (vecDir.x < 0) signoX = -1;
		else signoX = 1;
		if (vecDir.y < 0) signoY = -1;
		else signoY = 1;
		if (pObj->getRect().x != path[cont].x){
			pObj->setRect(1 * signoX, 0);
		}
		if (pObj->getRect().y != path[cont].y){
			pObj->setRect(0, 1 * signoY);
		}
		if (pObj->getRect().y == path[cont].y && pObj->getRect().x == path[cont].x)
			cont++;
	}
	else {
		cont = 1;
		following = false;
		path.clear();
	}
}
