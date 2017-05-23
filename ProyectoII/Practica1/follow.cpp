#include "follow.h"
#include "Cabania.h"

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
	pCBox = static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"));
}


follow::~follow()
{
}

void follow::update(int delta){

	if (target && al && !pObj->isAble()){
		int auxX, auxY;
		auxX = abs(pObj->getAbsRect().x - target->getAbsRect().x);
		auxY = abs(pObj->getAbsRect().y - target->getAbsRect().y);
		if ((float)sqrt((double)(auxX*auxX) + (double)(auxY*auxY)) > 1200 && contFollowSolo <= 0){
			direccion.clear();
			cont = 0;
			path.clear();
			if (!following){
				int rnd = rand() % 5 + 1;
				if (pObj->nombre[1] == "Zhenia") pObj->getPJuego()->getEstadoActual()->reproduceFx("ZheniaHabla" + to_string(rnd), pObj->getRect().x, pObj->getRect().y, 0);
				else pObj->getPJuego()->getEstadoActual()->reproduceFx("LyovHabla" + to_string(rnd), pObj->getRect().x, pObj->getRect().y, 0);
			}
			doFollow();
			contFollowSolo = 50;
		}
	}
	contFollowSolo--;
	if (pObj->getPJuego()->input.sw && al){
		direccion.clear();
		cont = 0;
		path.clear();
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
	x = pObj->getAbsRect().x + pObj->getRect().w*0.5;
	y = pObj->getAbsRect().y + pObj->getRect().h*0.9;
	xx = target->getAbsRect().x + target->getRect().w*0.5;
	yy = target->getAbsRect().y + target->getRect().h*0.9;
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
void follow::lateUpdate(int delta){
	if (pObj->getPJuego()->input.follow && al && !pObj->isAble() && dynamic_cast<Cabania*>(pObj->getPJuego()->getEstadoActual()) == nullptr){
		pObj->getPJuego()->input.follow = false;
		doFollow();
		int rnd = rand() % 3 + 1;
		pObj->getPJuego()->getEstadoActual()->reproduceFx("Silbido" + to_string(rnd), target->getRect().x, target->getRect().y, 0);
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
		contPasos += delta;
		if (direccion.size() != 0 && contPasos > 333)
		{
			int rnd = rand() % 4;
			if (al){
				switch (pObj->getTerreno()){
				case 0:
					if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve1", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve2", 0, 0, 0);
					else if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarNieve3", 0, 0, 0);
					break;
				case 1:
					if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera1", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera2", 0, 0, 0);
					else if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarMadera3", 0, 0, 0);
					break;
				case 2:
					if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra1", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra2", 0, 0, 0);
					else if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarPiedra3", 0, 0, 0);
					break;
				case 3:
					if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra", 0, 0, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra1", 0, 0, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra2", 0, 0, 0);
					else if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("AndarTierra3", 0, 0, 0);
					break;
				}
			}
			else
			{
				if (pObj->getTerreno() == 0){
					if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve", pObj->getRect().x, pObj->getRect().y, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve1", pObj->getRect().x, pObj->getRect().y, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve2", pObj->getRect().x, pObj->getRect().y, 0);
					else if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve3", pObj->getRect().x, pObj->getRect().y, 0);
				}
				else {
					if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboPiedra", pObj->getRect().x, pObj->getRect().y, 0);
					else if (rnd == 1)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboPiedra1", pObj->getRect().x, pObj->getRect().y, 0);
					else if (rnd == 2)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboPiedra2", pObj->getRect().x, pObj->getRect().y, 0);
					else if (rnd == 3)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboPiedra3", pObj->getRect().x, pObj->getRect().y, 0);
				}
			}
			contPasos = 0;
		}

		//Sale del escondite
		ObjetoPG* info;
		int colAux = pCBox->isColiding(nextPos, info);
		if (colAux == 3 && al) pObj->esconderse();
		else pObj->salirEscondite();

		if (direccion.size() != 0)
		{
			if (framerate >= 150) {// se mueve 1 frame cada 16 ms x 16ms
				pObj->changeAnimH();
				framerate = 0;
			}
			framerate+=delta;
			dir = direccion[cont];
			switch (direccion[cont])
			{
			case 0:
				pObj->setRect(0, -2*delta/16);
				pObj->setAbsRect(0, -2*delta/16);
				paso-=delta/4;
				pObj->changeAnimV(4);
				break;
			case 1:
				pObj->setRect(2*delta / 16, -1*delta / 16);
				pObj->setAbsRect(2 * delta / 16, -1 * delta / 16);
				paso -= delta/ 7;
				pObj->changeAnimV(0);
				break;
			case 2:
				pObj->setRect(2 * delta / 16, 0);
				pObj->setAbsRect(2 * delta / 16, 0);
				paso-=delta/2;
				pObj->changeAnimV(6);
				break;
			case 3:
				pObj->setRect(2 * delta / 16, 1 * delta / 16);
				pObj->setAbsRect(2 * delta / 16, 1 * delta / 16);
				paso -= delta/7;
				pObj->changeAnimV(3);
				break;
			case 4:
				pObj->setRect(0, 2 * delta / 16);
				pObj->setAbsRect(0, 2 * delta / 16);
				paso -= delta / 4;
				pObj->changeAnimV(5);
				break;
			case 5:
				pObj->setRect(-2 * delta / 16, 1 * delta / 16);
				pObj->setAbsRect(-2 * delta / 16, 1 * delta / 16);
				paso -= delta / 7;
				pObj->changeAnimV(7);
				break;
			case 6:
				pObj->setRect(-2 * delta / 16, 0);
				pObj->setAbsRect(-2 * delta / 16, 0);
				paso -= delta / 8;
				pObj->changeAnimV(1);
				break;
			case 7:
				pObj->setRect(-2 * delta / 16, -1 * delta / 16);
				pObj->setAbsRect(-2 * delta / 16, -1 * delta / 16);
				paso -= delta / 7;
				pObj->changeAnimV(2);
				break;
			}
			static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->setRectBox(pObj->getRect().x + pObj->getRect().w*0.3, pObj->getRect().y + pObj->getRect().h*0.8);
			if (paso <= 0) { 
				paso = 122; 
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