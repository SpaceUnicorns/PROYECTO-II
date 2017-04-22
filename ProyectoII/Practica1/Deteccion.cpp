#include "Deteccion.h"


Deteccion::Deteccion(ObjetoJuego* entidad, float radio):Componente(entidad),radio(radio)
{
	enemy = dynamic_cast<Enemigo*>(entidad);
	activo = true;
	detectado = false;
	cont = dirAtaque = 0;
	vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
	vista.B.x = vista.A.x + 300;  vista.B.y = enemy->getAbsRect().y - 200;
	vista.C.x = vista.B.x;  vista.C.y = enemy->getAbsRect().y + 200;
	ultAtaque = 0;
}


Deteccion::~Deteccion()
{
}

void Deteccion::update() {
	
	enemy->setTarget(0);
	if (enemy->encuentraComponente("follow"))setVista(enemy->getDir());
	switch (enemy->getEstado())
	{
	case Quieto:
		cont++;
		if (cont > 100){
			rnd = rand() % 100;
			if (rnd >80 && rnd < 89){
				direccionAux = nullptr;
				if (rnd >80 && rnd <83){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); }
				else if (rnd >82 && rnd <85){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); }
				else if (rnd >84 && rnd <87){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); }
				else if (rnd >86 && rnd <90){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); }
				enemy->followThis(direccionAux);
				cont = 0;
			}
			if (rnd > 89){
				//aulla
				/*rnd = rand() % 4;
				if (rnd == 0)enemy->getPJuego()->estados.top()->reproduceFx("aullido",500, 500,0);
				if (rnd == 1)enemy->getPJuego()->estados.top()->reproduceFx("aullido1", 500, 500, 0);
				if (rnd == 2)enemy->getPJuego()->estados.top()->reproduceFx("aullido2", 500, 500, 0);
				if (rnd == 3)enemy->getPJuego()->estados.top()->reproduceFx("aullido3", 500, 500, 0);
					*/
			}
			Punto cazP, recP;
			cazP.x = enemy->getCazador()->getAbsRect().x; cazP.y = enemy->getCazador()->getAbsRect().y;
			recP.x = enemy->getRecolector()->getAbsRect().x; recP.y = enemy->getRecolector()->getAbsRect().y;
			if (inTriangle(vista, cazP) && inTriangle(vista, recP)){
				float distRec, distCaz;
				detectado = true;
				recolectorIn(distRec);
				cazadorIn(distCaz);
				if (distRec < distCaz){
					enemy->setTarget(1);
					enemy->activaFollow();
					enemy->setEstado(Moviendo);
				}
				else{
					enemy->setTarget(0);
					enemy->activaFollow();
					enemy->setEstado(Moviendo);
				}
				cont = 0;
			}
			else if (inTriangle(vista, cazP)){
				detectado = true;
				enemy->setTarget(0);
				enemy->activaFollow();
				enemy->setEstado(Moviendo);
				cont = 0;
			}
			else if (inTriangle(vista, recP)){
				detectado = true;
				enemy->setTarget(1);
				enemy->activaFollow();
				enemy->setEstado(Moviendo);
				cont = 0;
			}
			else detectado = false;
		}
		// Al cabo de un tiempo vuelve a casa
		float distCasa;
		if (compruebaRadio(enemy->getCasita()->getAbsRect(),distCasa) > 1000){
			cont = 0;
			enemy->desactivaFollow();
			enemy->setEstado(Volviendo);
		}
		break;
	case Moviendo:
		float distRec;
		recolectorIn(distRec);
		float distCaz;
		cazadorIn(distCaz);
		cont++;
		if (cont > 50)
		{
			cont = 0;
			Punto cazP, recP;
			cazP.x = enemy->getCazador()->getAbsRect().x; cazP.y = enemy->getCazador()->getAbsRect().y;
			recP.x = enemy->getRecolector()->getAbsRect().x; recP.y = enemy->getRecolector()->getAbsRect().y;
			if (inTriangle(vista, cazP) && inTriangle(vista, recP)){
				if (distRec < distCaz){
					enemy->setTarget(1);
					enemy->activaFollow();
				}
				else{
					enemy->setTarget(0);
					enemy->activaFollow();
				}
			}
			else if (inTriangle(vista, cazP)){
				detectado = true;
				enemy->setTarget(0);
				enemy->activaFollow();
			}
			else if (inTriangle(vista, recP)){
				detectado = true;
				enemy->setTarget(1);
				enemy->activaFollow();
			}
			else { 
				detectado = false; 
				cont = 0;
				enemy->setEstado(Quieto);
			}
		}
		if (enemy->getTarget() == enemy->getRecolector()){
			dirAtaque = enemy->getDir();
			setVista(dirAtaque);
			if (distRec <= 80){
				preparaAtaque(1);
				enemy->setEstado(Atacando);
			}
		}
		else if (enemy->getTarget() == enemy->getCazador()){
			if (distCaz <= 80){
				preparaAtaque(0);
				enemy->setEstado(Atacando);
			}
		}
		break;
	case Volviendo:
		cont++;
		if (cont >= 500){
			cont = 0;
			enemy->setEstado(Quieto);
		}
		break;
	case Atacando:
		if (cont < 100)
			cont++;
		else { enemy->setEstado(PostAtaque); cont = 0; }
		switch (dirAtaque)
		{
		case 4:
			if (cont < 100){
				enemy->setAbsRect(0, -1);
				enemy->setRect(0, -1);
				ultAtaque = 0;
			}
			break;
		case 5:
			if (cont < 100){
				enemy->setAbsRect(2, -1);
				enemy->setRect(2, -1);
				ultAtaque = 1;
			}
			break;
		case 6:
			if (cont < 100){
				enemy->setAbsRect(2, 0);
				enemy->setRect(2, 0);
				ultAtaque = 2;
			}
			break;
		case 7:
			if (cont < 100){
				enemy->setAbsRect(2, 1);
				enemy->setRect(2, 1);
				ultAtaque = 3;
			}
			break;
		case 0:
			if (cont < 100){
				enemy->setAbsRect(0, 1);
				enemy->setRect(0, 1);
				ultAtaque = 4;
			}
			break;
		case 1:
			if (cont < 100){
				enemy->setAbsRect(-2, 1);
				enemy->setRect(-2, 1);
				ultAtaque = 5;
			}
			break;
		case 2:
			if (cont < 100){
				enemy->setAbsRect(-2, 0);
				enemy->setRect(-2, 0);
				ultAtaque = 6;
			}
			break;
		case 3:
			if (cont < 100){
				enemy->setAbsRect(-2, -1);
				enemy->setRect(-2, -1);
				ultAtaque = 7;
			}
			break;
		}
		static_cast<ColisionBox*>(enemy->dameComponente("ColisionBox"))->setRectBox(enemy->getRect().x - 5, enemy->getRect().y + 40);
		break;
	case Atrapado:
		cont++;
		if (cont >= 500)
		{
			cont = 0;
			enemy->setEstado(Quieto);
		}
		break;
	case PostAtaque:
		direccionAux = nullptr;
		if (cont == 0){ // Segun aonde atacara el lobo da la vuelta a una posicion u otra
			rnd = rand() % 2;
			if (ultAtaque == 0){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); }
			}
			else if (ultAtaque == 1){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); }
			}
			else if (ultAtaque == 2){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); }
			}
			else if (ultAtaque == 3){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); }
			}
			else if (ultAtaque == 4){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); }
			}
			else if (ultAtaque == 5){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); }
			}
			else if (ultAtaque == 6){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); }
			}
			else if (ultAtaque == 7){
				if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); }
				else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); }
			}
			enemy->followThis(direccionAux);
		}
		else if (cont > 100) {
			float distRec;
			recolectorIn(distRec);
			float distCaz;
			cazadorIn(distCaz);
			enemy->setTarget(0);
			delete direccionAux;

			if (distCaz <= 80){
				preparaAtaque(0);
				enemy->setEstado(Atacando);
			}
			else if (distRec <= 80){
				preparaAtaque(0);
				enemy->setEstado(Atacando);
			}
			else enemy->setEstado(Quieto);
			cont = 0;
		}
		cont++;
		break;
	case Herido:
		//Animacion Herido
		if (enemy->life < 0)
			enemy->setEstado(Muerto);
		else if (cont > 100){
			cont = 0;
			enemy->setEstado(Quieto);
		}
		break;
	case Muerto:
		break;
	}
		/*
		//DEPURACION
		std::cout << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getCazador()->getRect().y << "\n";
		std::cout << static_cast<Enemigo*>(pEntidad)->getRect().x << "     " << static_cast<Enemigo*>(pEntidad)->getRect().y << "\n";
		std::cout << static_cast<Enemigo*>(pEntidad)->getPosIni().x << "     " << static_cast<Enemigo*>(pEntidad)->getPosIni().y;
		//*/
}

void Deteccion::setVista(int dir)
{
	switch (dir)
	{
	case 0:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x - 200;  vista.B.y = enemy->getAbsRect().y - 300;
		vista.C.x = vista.B.x + 400;  vista.C.y = enemy->getAbsRect().y - 300;
		break;
	case 1:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x + 70;  vista.B.y = enemy->getAbsRect().y - 350;
		vista.C.x = vista.A.x + 350;  vista.C.y = enemy->getAbsRect().y - 70;
		break;
	case 2:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x + 300;  vista.B.y = enemy->getAbsRect().y - 200;
		vista.C.x = vista.B.x;  vista.C.y = enemy->getAbsRect().y + 200;
		break;
	case 3:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x + 70;  vista.B.y = enemy->getAbsRect().y + 350;
		vista.C.x = vista.A.x + 350;  vista.C.y = enemy->getAbsRect().y + 70;
		break;
	case 4:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x - 200;  vista.B.y = enemy->getAbsRect().y + 300;
		vista.C.x = vista.B.x + 400;  vista.C.y = enemy->getAbsRect().y + 300;
		break;
	case 5:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x - 70;  vista.B.y = enemy->getAbsRect().y + 350;
		vista.C.x = vista.A.x - 350;  vista.C.y = enemy->getAbsRect().y + 70;
		break;
	case 6:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x - 300;  vista.B.y = enemy->getAbsRect().y - 200;
		vista.C.x = vista.B.x;  vista.C.y = enemy->getAbsRect().y + 200;
		break;
	case 7:
		vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
		vista.B.x = vista.A.x - 70;  vista.B.y = enemy->getAbsRect().y - 350;
		vista.C.x = vista.A.x - 350;  vista.C.y = enemy->getAbsRect().y - 70;
		break;
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
int Deteccion::triangleOrientation(TrianguloBorde const & tr){
	static TrianguloBorde s;
	return ((tr.A.x - tr.C.x)*(tr.B.y - tr.C.y) - (tr.A.y - tr.C.y)*(tr.B.x - tr.C.x));
}

void Deteccion::preparaAtaque(int target)
{
	if (target == 0){
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
	else 
	{
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