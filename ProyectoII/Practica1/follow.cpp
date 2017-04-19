#include "follow.h"


follow::follow(ObjetoJuego* ent, ObjetoPG* tg, GrafoMapa* m, bool aliado) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	target = tg;
	paso = 122;
	following = false;
	hitInfo = nullptr;
	cont = 0;
	map = m;
	al = aliado;
}


follow::~follow()
{
}

void follow::setTarget(ObjetoPG* targe) {
	target = targe;
}

void follow:: update(){
	if (pObj->getPJuego()->input.sw && al){
		direccion.clear();
		cont = 0;
		path.clear();
	}

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
	std::cout << x << " " << y << " \n";
	std::cout << xx << " " << yy << " \n";
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
void follow::lateUpdate(){
	if (pObj->getPJuego()->input.follow && al){
		pObj->getPJuego()->input.follow = false;
		doFollow();
	}
	
		//Primero calculamos posiciones absolutas y calculamos luego la distancia euclidea
		int x, y, xx, yy;
		int auxX, auxY;
		x = pObj->getColisionBox().x;
		y = pObj->getColisionBox().y;
		xx = target->getColisionBox().x;
		yy = target->getColisionBox().y;

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

		if (direccion.size() != 0)
		{
			switch (direccion[cont])
			{
			case 0:
				pObj->setRect(0, -2);
				pObj->setAbsRect(0, -2);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso-=4;
				break;
			case 1:
				pObj->setRect(2, -1);
				pObj->setAbsRect(2, -1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				break;
			case 2:
				pObj->setRect(2, 0);
				pObj->setAbsRect(2, 0);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso-=2;
				break;
			case 3:
				pObj->setRect(2, 1);
				pObj->setAbsRect(2, 1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				break;
			case 4:
				pObj->setRect(0, 2);
				pObj->setAbsRect(0, 2);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 4;
				break;
			case 5:
				pObj->setRect(-2, 1);
				pObj->setAbsRect(-2, 1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				break;
			case 6:
				pObj->setRect(-2, 0);
				pObj->setAbsRect(-2, 0);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso-=2;
				break;
			case 7:
				pObj->setRect(-2, -1);
				pObj->setAbsRect(-2, -1);
				static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + 15, pObj->getRect().y + 40);
				paso -= 2.23;
				break;
			}
			
			if (paso <= 0) { 
				paso = 120; 
				std::cout << direccion[cont] << "\n";
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