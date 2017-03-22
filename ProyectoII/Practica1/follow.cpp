#include "follow.h"


follow::follow(ObjetoJuego* ent, ObjetoPG* tg, GrafoMapa* m) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	target = tg;
	paso = 120;
	following = false;
	hitInfo = nullptr;
	cont = 0;
	map = m;
}


follow::~follow()
{
}

void follow::update(){
	if (pObj->getPJuego()->input.follow){
		pObj->getPJuego()->input.follow = false;
		//actualiza el mapa
		//map->actualizaMapa(static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj());
		int x, y, xx, yy;

		// Hallamos las coordenadas de cada objeto y las transformamos a las coordenadas absolutas que ocupan dentro del mapa
		x = pObj->getAbsRect().x + pObj->getAbsRect().w*0.2;
		y = pObj->getAbsRect().y + pObj->getAbsRect().h*0.8;
		xx = target->getAbsRect().x + target->getAbsRect().w*0.2;
		yy = target->getAbsRect().y + target->getAbsRect().h*0.8;
		map->transformaCoord(x, y);
		map->transformaCoord(xx, yy);

		//Resolvemos el camino
		std::cout << x << " " << y << " \n";
		std::cout << xx << " " << yy << " \n";
		map->solve(map->XYToNode(xx,yy), map->XYToNode(x,y), &path, &coste);
		coste = 0;
		int auxX, auxY;
		int dirX, dirY;

		//codificamos en el vector de direcciones
		for (int i = 0; i < path.size()-1 && path.size() > 0; i++)
		{
			map->NodeToXY(path[i], &dirX, &dirY);
			map->NodeToXY(path[i+1], &auxX, &auxY);

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
		std::cout << "following a true \n";

		for (void* p : path)
		{
			map->NodeToXY(p, &auxX, &auxY);
			std::cout << "pos X: " << auxX << " Y: " << auxY << "\n";
		}
		std::cout << "\n";
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
				target->setRect(0, -2);
				target->setAbsRect(0, -2);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso-=4;
				break;
			case 1:
				target->setRect(2, -1);
				target->setAbsRect(2, -1);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso -= 3;
				break;
			case 2:
				target->setRect(2, 0);
				target->setAbsRect(2, 0);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso-=2;
				break;
			case 3:
				target->setRect(2, 1);
				target->setAbsRect(2, 1);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso -= 3;
				break;
			case 4:
				target->setRect(0, 2);
				target->setAbsRect(0, 2);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso -= 4;
				break;
			case 5:
				target->setRect(-2, 1);
				target->setAbsRect(-2, 1);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso -= 3;
				break;
			case 6:
				target->setRect(-2, 0);
				target->setAbsRect(-2, 0);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso-=2;
				break;
			case 7:
				target->setRect(-2, -1);
				target->setAbsRect(-2, -1);
				static_cast<ColisionBox*>(target->dameComponente("ColisionBox"))->setRectBox(target->getRect().x + 15, target->getRect().y + 40);
				paso -= 3;
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