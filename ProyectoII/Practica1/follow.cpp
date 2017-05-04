#include "follow.h"


follow::follow(ObjetoJuego* ent, ObjetoPG* tg, GrafoMapa* m, bool aliado) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	target = tg;
	paso = 122;
	following = false;
	hitInfo = nullptr;
	cont = contPasos = 0;
	map = m;
	al = aliado;
	framerate = 0;
}


follow::~follow()
{
}

void follow::update(){
	if (pObj->getPJuego()->input.sw && al){
		direccion.clear();
		cont = 0;
		path.clear();
	}
	if (target && al && !pObj->isAble()){
		int auxX, auxY;
		auxX = abs(pObj->getAbsRect().x - target->getAbsRect().x);
		auxY = abs(pObj->getAbsRect().y - target->getAbsRect().y);
		if ((float)sqrt((double)(auxX*auxX) + (double)(auxY*auxY)) > 1000){
			direccion.clear();
			cont = 0;
			path.clear();
			doFollow();
		}
	}

}

void follow::setTarget(ObjetoPG* targe) {
	target = targe;
}
void follow::clearFollow()
{
	direccion.clear();
	cont = 0;
	path.clear();
}
void follow::doFollow()
{
	// Nos aseguramos de que el vector path y direccion este vacio
	direccion.clear();
	cont = 0;
	path.clear();
	//actualiza el mapa
	map->actualizaMapa(static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj());
	int x, y, xx, yy;

	// Hallamos las coordenadas de cada objeto y las transformamos a las coordenadas absolutas que ocupan dentro del mapa
	x = pObj->getAbsRect().x + pObj->getAbsRect().w*0.2;
	y = pObj->getAbsRect().y + pObj->getAbsRect().h*0.8;
	xx = target->getAbsRect().x + target->getAbsRect().w*0.2;
	yy = target->getAbsRect().y + target->getAbsRect().h*0.8;
	map->transformaCoord(x, y);
	map->transformaCoord(xx, yy);

	
	/*pObj->setRect((pObj->getAbsRect().x / x) - 51, (pObj->getAbsRect().y / y) - 31);
	pObj->setAbsRect((pObj->getAbsRect().x / x) - 51, (pObj->getAbsRect().y / y) - 31);
	static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);*/
	//Resolvemos el camino
	if (x > 0 && xx > 0 && y > 0 && yy > 0 && y < map->dameAltura()-1 && yy < map->dameAltura()-1 && x < map->dameAnchura() && xx < map->dameAnchura()){
		map->solve(map->XYToNode(x, y), map->XYToNode(xx, yy), &path, &coste);
		coste = 0;
		int auxX, auxY;
		int dirX, dirY;

		//codificamos en el vector de direcciones
		for (int i = 0; i < path.size() - 1 && path.size() > 0; i++)
		{
			map->NodeToXY(path[i], &dirX, &dirY);
			map->NodeToXY(path[i + 1], &auxX, &auxY);

			if (auxX > dirX)
			{
				if (auxY > dirY)
					direccion.push_back(3);
				else if (auxY < dirY)
					direccion.push_back(1);
				else
					direccion.push_back(2);
			}
			else if (auxX < dirX)
			{
				if (auxY > dirY)
					direccion.push_back(5);
				else if (auxY < dirY)
					direccion.push_back(7);
				else
					direccion.push_back(6);
			}
			else
			{
				if (auxY > dirY)
					direccion.push_back(4);
				else
					direccion.push_back(0);
			}
		}
		following = true;
	}

}
void follow::lateUpdate(){
	if (pObj->getPJuego()->input.follow && al && !pObj->isAble()){
		pObj->getPJuego()->input.follow = false;
		doFollow();
	}
	
		//Primero calculamos posiciones absolutas y calculamos luego la distancia euclidea
		int x, y, xx, yy;
		int auxX, auxY;
		x = pObj->getColisionBox().x;
		y = pObj->getColisionBox().y;
		if (target){
			xx = target->getColisionBox().x;
			yy = target->getColisionBox().y;
		}
		else
		{
			xx = x; yy = y;
		}
		auxX = x; auxY = y;
		x = x + (x - xx);
		y = y + (y - yy)+2;
		xx = xx + (auxX - xx);
		yy = yy + (auxY - yy)+2;

		if (xx >= x) auxX = xx - x;
		else auxX = x - xx;

		if (yy >= y) auxY = yy - y;
		else auxY = y - yy;

		//Si la distancia es menor de cierto valor, devolvemos following a false
		if ((float)sqrt((double)(auxX*auxX) + (double)(auxY*auxY)) < 50){
			following = false;
			direccion.clear();
			cont = 0;
			path.clear();

		}
	if (following)
	{
		if (direccion.size() != 0 && contPasos == 0)
		{
			int rnd = rand() % 4;
			if (al){
				if (rnd == 0)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve", pObj->getRect().x, pObj->getRect().y, 0);
				else if (rnd == 1)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve1", pObj->getRect().x, pObj->getRect().y, 0);
				else if (rnd == 2)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve2", pObj->getRect().x, pObj->getRect().y, 0);
				else if (rnd == 3)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve3", pObj->getRect().x, pObj->getRect().y, 0);
			}
			else
			{
				if (rnd == 0)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve", pObj->getRect().x, pObj->getRect().y, 0);
				else if (rnd == 1)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve1", pObj->getRect().x, pObj->getRect().y, 0);
				else if (rnd == 2)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve2", pObj->getRect().x, pObj->getRect().y, 0);
				else if (rnd == 3)
					pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve3", pObj->getRect().x, pObj->getRect().y, 0);
			}
		}
		if (direccion.size() != 0){
			contPasos++;
			if (contPasos >= 20)contPasos = 0;
		}
		if (direccion.size() != 0)
		{
			if (framerate % 8 == 0) {// se mueve 1 frame cada 16 ms x 16ms
				pObj->changeAnimH();

			}
			framerate++;
			dir = direccion[cont];
			switch (direccion[cont])
			{
			case 0:
				pObj->setRect(0, -2);
				pObj->setAbsRect(0, -2);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso-=4;
				pObj->changeAnimV(4);
				break;
			case 1:
				pObj->setRect(2, -1);
				pObj->setAbsRect(2, -1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				pObj->changeAnimV(0);
				break;
			case 2:
				pObj->setRect(2, 0);
				pObj->setAbsRect(2, 0);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso-=2;
				pObj->changeAnimV(6);
				break;
			case 3:
				pObj->setRect(2, 1);
				pObj->setAbsRect(2, 1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				pObj->changeAnimV(3);
				break;
			case 4:
				pObj->setRect(0, 2);
				pObj->setAbsRect(0, 2);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 4;
				pObj->changeAnimV(5);
				break;
			case 5:
				pObj->setRect(-2, 1);
				pObj->setAbsRect(-2, 1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				pObj->changeAnimV(7);
				break;
			case 6:
				pObj->setRect(-2, 0);
				pObj->setAbsRect(-2, 0);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso-=2;
				pObj->changeAnimV(1);
				break;
			case 7:
				pObj->setRect(-2, -1);
				pObj->setAbsRect(-2, -1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				pObj->changeAnimV(2);
				break;
			}
			
			if (paso <= 0) { 
				paso = 120; 
				cont++;
				if (cont == direccion.size()){ 
					following = false;
					direccion.clear();
					path.clear();
					cont = 0; 
				
				}
			}
		}
	}
}