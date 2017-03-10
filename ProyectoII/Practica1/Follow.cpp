#include "Follow.h"
#include "EstadoPG.h"
#include "ColisionBox.h"

Follow::Follow(ObjetoJuego* ent, ObjetoPG* tg) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	target = tg;
	paso = 80;
	following = false;
	hitInfo = nullptr;
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
		/*case 4: aux.x = path[k].x + paso; aux.y = path[k].y - paso; //dDS
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
	/*if (path[k].x > 1024 || path[k].x < 0) return false;
	if (path[k].y > 768 || path[k].y < 0) return false;*/
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

	while (dir < 4 && !exito){
		path.push_back(sigDireccion(dir,k));
		if (esValida(k+1)){
			if (path[k+1].compruebaRadio(target->getColisionBox(),paso ))
			{
				std::cout << "He encontrado un camino debuti loco \n"; exito = true;
				return;
			}
			else{ // marcar
				//marcas[sol[k].fila][sol[k].col] = true;
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
	path.clear();

}
void Follow::update(){
	if (pObj->getPJuego()->input.follow){
		pObj->getPJuego()->input.follow = false;
		following = true;
		calculaPath();
	}
}
