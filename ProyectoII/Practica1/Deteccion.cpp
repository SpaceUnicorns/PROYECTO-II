#include "Deteccion.h"


Deteccion::Deteccion(ObjetoJuego* entidad, float radio):Componente(entidad),radio(radio)
{
	enemy = dynamic_cast<Enemigo*>(entidad);
	activo = true;
	detectado = false;
	contAtrapado = contAtaque = dirAtaque = 0;
	vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
	vista.B.x = vista.A.x + 300;  vista.B.y = enemy->getAbsRect().y - 200;
	vista.C.x = vista.B.x;  vista.C.y = enemy->getAbsRect().y + 200;
}


Deteccion::~Deteccion()
{
}

void Deteccion::update() {
	//std::cout << "UPDATE LOBO DEPURAR \n";

	switch (enemy->getEstado())
	{
	case Quieto:
		acechar();
		break;
	case Moviendo:
		acechar();
		if (enemy->getTarget() == enemy->getRecolector())
		{
			float distRec;
			recolectorIn(distRec);
			if (distRec <= 80)
			{
				enemy->setEstado(Atacando);
				if (enemy->getAbsRect().x < enemy->getRecolector()->getAbsRect().x)
				{
					if (enemy->getAbsRect().y < enemy->getRecolector()->getAbsRect().y)
					{
						dirAtaque = 7;
					}
					else if (enemy->getAbsRect().y >= enemy->getRecolector()->getAbsRect().y + 30)
					{
						dirAtaque = 5;
					}
					else{ dirAtaque = 6; }
				}
				else if (enemy->getAbsRect().x >= enemy->getRecolector()->getAbsRect().x + 50)
				{
					if (enemy->getAbsRect().y < enemy->getRecolector()->getAbsRect().y)
					{
						dirAtaque = 1;
					}
					else if (enemy->getAbsRect().y >= enemy->getRecolector()->getAbsRect().y + 30)
					{
						dirAtaque = 3;
					}
					else{ dirAtaque = 2; }
				}
				else
				{
					if (enemy->getAbsRect().y < enemy->getRecolector()->getAbsRect().y)
					{
						dirAtaque = 0;
					}
					else if (enemy->getAbsRect().y >= enemy->getRecolector()->getAbsRect().y)
					{
						dirAtaque = 4;
					}
				}
			}
		}
		else if (enemy->getTarget() == enemy->getCazador())
		{
			float distCaz;
			cazadorIn(distCaz);
			if (distCaz <= 80)
			{
				enemy->setEstado(Atacando);
				if (enemy->getAbsRect().x < enemy->getCazador()->getAbsRect().x)
				{
					if (enemy->getAbsRect().y < enemy->getCazador()->getAbsRect().y)
					{
						dirAtaque = 7;
					}
					else if (enemy->getAbsRect().y >= enemy->getCazador()->getAbsRect().y + 30)
					{
						dirAtaque = 5;
					}
					else{ dirAtaque = 6; }
				}
				else if (enemy->getAbsRect().x >= enemy->getCazador()->getAbsRect().x + 50)
				{
					if (enemy->getAbsRect().y < enemy->getCazador()->getAbsRect().y)
					{
						dirAtaque = 1;
					}
					else if (enemy->getAbsRect().y >= enemy->getCazador()->getAbsRect().y + 30)
					{
						dirAtaque = 3;
					}
					else{ dirAtaque = 2; }
				}
				else
				{
					if (enemy->getAbsRect().y < enemy->getCazador()->getAbsRect().y)
					{
						dirAtaque = 0;
					}
					else if (enemy->getAbsRect().y >= enemy->getCazador()->getAbsRect().y)
					{
						dirAtaque = 4;
					}
				}
			}
			break;
	case Volviendo:
		acechar();
		break;
	case Atacando:
		if (contAtaque < 100)
			contAtaque++;
		else { enemy->setEstado(Quieto); contAtaque = 0; }
		switch (dirAtaque)
		{
		case 4:
			if (contAtaque < 50){
				enemy->setAbsRect(0, -1);
				enemy->setRect(0, -1);
			}
			else
			{
				enemy->setAbsRect(0, 1);
				enemy->setRect(0, 1);
			}
			break;
		case 5:
			if (contAtaque < 50){
				enemy->setAbsRect(2, -1);
				enemy->setRect(2, -1);
			}
			else
			{
				enemy->setAbsRect(-2, 1);
				enemy->setRect(-2, 1);
			}
			break;
		case 6:
			if (contAtaque < 50){
				enemy->setAbsRect(2, 0);
				enemy->setRect(2, 0);
			}
			else
			{
				enemy->setAbsRect(-2, 0);
				enemy->setRect(-2, 0);
			}
			break;
		case 7:
			if (contAtaque < 50){
				enemy->setAbsRect(2, 1);
				enemy->setRect(2, 1);
			}
			else
			{
				enemy->setAbsRect(-2, -1);
				enemy->setRect(-2, -1);
			}
			break;
		case 0:
			if (contAtaque < 50){
				enemy->setAbsRect(0, 1);
				enemy->setRect(0, 1);
			}
			else
			{
				enemy->setAbsRect(0, -1);
				enemy->setRect(0, -1);
			}
			break;
		case 1:
			if (contAtaque < 50){
				enemy->setAbsRect(-2, 1);
				enemy->setRect(-2, 1);
			}
			else
			{
				enemy->setAbsRect(2, -1);
				enemy->setRect(2, -1);
			}
			break;
		case 2:
			if (contAtaque < 50){
				enemy->setAbsRect(-2, 0);
				enemy->setRect(-2, 0);
			}
			else
			{
				enemy->setAbsRect(2, 0);
				enemy->setRect(2, 0);
			}
			break;
		case 3:
			if (contAtaque < 50){
				enemy->setAbsRect(-2, -1);
				enemy->setRect(-2, -1);
			}
			else
			{
				enemy->setAbsRect(2, 1);
				enemy->setRect(2, 1);
			}
			break;
		default:
			break;
		}
		static_cast<ColisionBox*>(enemy->dameComponente("ColisionBox"))->setRectBox(enemy->getRect().x - 5, enemy->getRect().y + 40);
		break;
	case Atrapado:
		contAtrapado++;
		if (contAtrapado >= 500)
		{
			contAtrapado = 0;
			enemy->setEstado(Quieto);
		}
		break;
		}
		
		/*
		//DEPURACION
		std::cout << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().y << "\n";
		std::cout << static_cast<Enemigo*>(pEntidad)->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getRect().y << "\n";
		std::cout << static_cast<Enemigo*>(pEntidad)->getPosIni().x << "     " << static_cast<Enemigo*>(pEntidad)->getPosIni().y;
		//*/
	}

}

void Deteccion::acechar()
{
	float distCaz, distRec;
	cazadorIn(distCaz);
	recolectorIn(distRec);
	if (distCaz <  distRec && distCaz < radio) {//Llamamos al follow del lobo
		detectado = true;
		enemy->setTarget(0);
		//std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
		enemy->setEstado(Moviendo);
	}
	else if (distCaz >= distRec && distRec< radio) {//Llamamos al follow del lobo
		detectado = true;
		enemy->setTarget(1);
		//std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
		enemy->setEstado(Moviendo);
	}
	else {
		if (detectado)enemy->desactivaFollow();
		detectado = false;
		enemy->setEstado(Volviendo);
	}
}

bool Deteccion::compruebaRadio(SDL_Rect target, float& distancia) {
		Punto centro; centro.y = target.h / 2 + target.y; centro.x = target.w / 2 + target.x;
		distancia = sqrt(((enemy->getAbsRect().x + enemy->getRect().w / 2) - centro.x) * (enemy->getAbsRect().x + enemy->getRect().w / 2 - centro.x) + (enemy->getAbsRect().y + enemy->getRect().h / 2 - centro.y) * (enemy->getAbsRect().y + enemy->getRect().h / 2 - centro.y));
		return distancia <= radio;
}

bool Deteccion::cazadorIn(float& dist) {
	SDL_Rect rectCaz = enemy->getCazador()->getAbsRect();
	return compruebaRadio(rectCaz, dist);
}

bool Deteccion::recolectorIn(float& dist) {
	SDL_Rect rec = enemy->getRecolector()->getAbsRect();
	return compruebaRadio(rec, dist);
}
bool Deteccion::inTriangle(TrianguloBorde tr, Punto const & P){
	int x = triangleOrientation(tr);
	TrianguloBorde auxT;
	if (x >= 0){// Orientación positiva
		auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
		if (triangleOrientation(auxT) >= 0){
			auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
			if (triangleOrientation(auxT) >= 0){
				auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
				if (triangleOrientation(auxT) >= 0){
					return 1;
				}
				else return 0;
			}
			else return 0;
		}
		else return 0;

	}
	else {//Orientación negativa
		auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
		if (triangleOrientation(auxT) < 0){
			auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
			if (triangleOrientation(auxT) < 0){
				auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
				if (triangleOrientation(auxT) < 0){
					return 1;
				}
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
}
//Método que calcula la orientación de un triangulo con la fórmula: (A1.x - A3.x) * (A2.y - A3.y) - (A1.y - A3.y) * (A2.x - A3.x)
//Siendo A1A2A3 el triángulo.
//Si el resultado es mayor o igual que 0, la orientación del triángulo será positiva.En caso contrario, la orientación del triángulo será negativa.
int ColisionBox::triangleOrientation(TrianguloBorde const & tr){
	static TrianguloBorde s;
	return ((tr.A.x - tr.C.x)*(tr.B.y - tr.C.y) - (tr.A.y - tr.C.y)*(tr.B.x - tr.C.x));
}