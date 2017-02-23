#include "MovimientoP.h"
#include "EstadoPG.h"


MovimientoP::MovimientoP(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
}


MovimientoP::~MovimientoP()
{
	
}

//Método que calcula si alguno de los triangulos del vector de triangulos está colisionando con la posicion a la que nos queremos mover.
bool MovimientoP::isColiding(Punto const & P){
	bool col = false;
	Punto p; p.x = P.x + pObj->getColisionBox().x; p.y = P.y + pObj->getColisionBox().y; //Posición de colisionBox + la posición a la que nos queremos mover.
	ObjetoPG* ob;
	int i = 0;
	while (i < static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj().size() && !col){
		ob = dynamic_cast<ObjetoPG*>(static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj()[i]);
		if ( ob != pObj){
			if ((ob->getColisionBox().x + ob->getColisionBox().w) < p.x || ob->getColisionBox().x > (p.x + pObj->getColisionBox().w)) col = false;
			else if ((ob->getColisionBox().y + ob->getColisionBox().h) < p.y || ob->getColisionBox().y > (p.y + pObj->getColisionBox().h)) col = false;
			else col = true;
		}
			i++;
	}
	//Comprueba la colision con los bordes
	i = 0;
	if (!col){
		while (i < static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectBordes().size() && !col){
			col = inTriangle(static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectBordes()[i], p);
			i++;
		}//fin colision con bordes
	}
	return col;
}
//Este método calcula si un punto dado se encuentra dentro del área del triangulo.
//Para saber si el punto está en el área: 
/*Calcular la orientación de los triángulos que forma el punto P con los vértices del triángulo A1A2A3.

(1)Se calcula la orientación de los triángulos A1A2P, A2A3P, A3A1P.
En el caso de que la orientación del triángulo A1A2A3 sea positiva:
Si las orientaciones de los tres triángulos que tienen como vértice el punto P, son positivas el punto está dentro del triángulo.
En caso contrario el punto está situado fuera del triángulo

En el caso de que la orientación del triángulo A1A2A3 sea negativa :
Si las orientaciones de los tres triángulos que triángulos que tienen como vértice el punto P son negativas, el punto está dentro del triángulo
En caso contrario el punto está situado fuera del triángulo.*/

bool MovimientoP::inTriangle(TrianguloBorde tr, Punto const & P){
	int x = triangleOrientation(tr);
	TrianguloBorde auxT;
	if (x >= 0){// Orientación positiva
		auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
		if (triangleOrientation(auxT) >= 0){
			auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
			if (triangleOrientation(auxT) >= 0){
				auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
				if (triangleOrientation(auxT) >= 0){
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
		
	}
	else {//Orientación negativa
		auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
		if (triangleOrientation(auxT) < 0){
			auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
			if (triangleOrientation(auxT) < 0){
				auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
				if (triangleOrientation(auxT) < 0){
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
}
//Método que calcula la orientación de un triangulo con la fórmula: (A1.x - A3.x) * (A2.y - A3.y) - (A1.y - A3.y) * (A2.x - A3.x)
//Siendo A1A2A3 el triángulo.
//Si el resultado es mayor o igual que 0, la orientación del triángulo será positiva.En caso contrario, la orientación del triángulo será negativa.
int MovimientoP::triangleOrientation(TrianguloBorde const & tr){
	TrianguloBorde s;
	return ((tr.A.x - tr.C.x)*(tr.B.y - tr.C.y) - (tr.A.y - tr.C.y)*(tr.B.x - tr.C.x));
}
void MovimientoP::update(){
	//Antes de actualizar la posición comprobamos si colisiona con la posición siguiente.

	if(framerate % 16 == 0) // se mueve 1 frame cada 16 ms x 16ms
		pObj->changeAnimH();

	framerate++;
	if (pObj->getPJuego()->input.dDS){ //Diagonal Arriba-Derecha
		nextPos.x = 2; nextPos.y = -1;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(7); // posiciona la 'j' de la matriz de la animacion
		}
	}
	else if (pObj->getPJuego()->input.dDI){//Diagonal Abajo-Derecha
		nextPos.x = 2; nextPos.y = 1;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(5);
		}

	}
	else if (pObj->getPJuego()->input.dII){//Diagonal Abajo-Izquierda
		nextPos.x = -2; nextPos.y = 1;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(4);
		}

	}
	else if (pObj->getPJuego()->input.dIS){//Diagonal Arriba-Izquierda
		nextPos.x = -2; nextPos.y = -1;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(6);
		}

	}
	else if (pObj->getPJuego()->input.arriba){
		nextPos.x = 0; nextPos.y = -2;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(3);
		}

	}
	else if (pObj->getPJuego()->input.derecha){
		bool o;
		nextPos.x = 2; nextPos.y = 0;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(2);
		}

	}
	else if (pObj->getPJuego()->input.abajo){
		nextPos.x = 0; nextPos.y = 2;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(0);
		}

	}
	else if (pObj->getPJuego()->input.izquierda){
		nextPos.x = -2; nextPos.y = 0;
		if (!isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			pObj->changeAnimV(1);
		}

	}
}
