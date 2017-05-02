#include "Deteccion.h"


Deteccion::Deteccion(ObjetoJuego* entidad, float radio) :Componente(entidad), radio(radio)
{
	enemy = dynamic_cast<Enemigo*>(entidad);
	activo = true;
	detectado = false;
	cont = contPasos = 0;
	dirAtaque = 2;
	vista.A.x = enemy->getAbsRect().x; vista.A.y = enemy->getAbsRect().y;
	vista.B.x = vista.A.x + 300;  vista.B.y = enemy->getAbsRect().y - 200;
	vista.C.x = vista.B.x;  vista.C.y = enemy->getAbsRect().y + 200;
	ultAtaque = 0;
	direccionAux = nullptr;
	info = nullptr;
	vagar = contVagar = 0;
}


Deteccion::~Deteccion()
{
}
// Comportamientos-----------------------------------------------------------------------------------------------------------------------------------------

void Deteccion::quieto(){
	cont++;
	if (vagar > 0 && contVagar < 150){
		Punto p = { 0, 0 };
		if (vagar == 1){
			p.x -= 2;
			if (static_cast<ColisionBox*>(enemy->dameComponente("ColisionBox"))->isColiding(p, info) != 1){
				enemy->setAbsRect(-2, 0);
				enemy->setRect(-2, 0);
				dirAtaque = 6;
				if (contPasos == 0)
				{
					int rnd = rand() % 4;
					if (rnd == 0)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 1)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve1", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 2)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve2", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 3)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve3", enemy->getRect().x, enemy->getRect().y, 0);
				}
				contPasos++;
			}
		}
		else if (vagar == 2){
			p.x += 2;
			if (static_cast<ColisionBox*>(enemy->dameComponente("ColisionBox"))->isColiding(p, info) != 1){
				enemy->setAbsRect(2, 0);
				enemy->setRect(2, 0);
				dirAtaque = 2;
				if (contPasos == 0)
				{
					int rnd = rand() % 4;
					if (rnd == 0)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 1)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve1", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 2)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve2", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 3)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve3", enemy->getRect().x, enemy->getRect().y, 0);
				}
				contPasos++;
			}
		}
		else if (vagar == 3){
			p.y -= 1;
			if (static_cast<ColisionBox*>(enemy->dameComponente("ColisionBox"))->isColiding(p, info) != 1){
				enemy->setAbsRect(0, -1);
				enemy->setRect(0, -1);
				dirAtaque = 0;
				if (contPasos == 0)
				{
					int rnd = rand() % 4;
					if (rnd == 0)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 1)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve1", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 2)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve2", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 3)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve3", enemy->getRect().x, enemy->getRect().y, 0);
				}
				contPasos++;
			}
		}
		else if (vagar == 4) {
			p.y += 1;
			if (static_cast<ColisionBox*>(enemy->dameComponente("ColisionBox"))->isColiding(p, info) != 1){
				enemy->setAbsRect(0, 1);
				enemy->setRect(0, 1);
				dirAtaque = 4;
				if (contPasos == 0)
				{
					int rnd = rand() % 4;
					if (rnd == 0)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 1)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve1", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 2)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve2", enemy->getRect().x, enemy->getRect().y, 0);
					else if (rnd == 3)
						enemy->getPJuego()->getEstadoActual()->reproduceFx("LoboNieve3", enemy->getRect().x, enemy->getRect().y, 0);
				}
				contPasos++;
			}
		}
		if (contPasos >= 20)contPasos = 0;
		contVagar++;
		static_cast<ColisionBox*>(enemy->dameComponente("ColisionBox"))->setRectBox(enemy->getRect().x - 5, enemy->getRect().y + 40);
		if (contVagar >= 150){ vagar = 0; contVagar = 0; }
	}
	if (cont > 300){
		rnd = (rand() % 11) + 80;
		if (rnd >=80 && rnd < 88){
			direccionAux = nullptr;
			if (rnd >=80 && rnd <82){ if (enemy->getAbsRect().x > 150)vagar = 1; }
			else if (rnd >81 && rnd <84){ vagar = 2; }
			else if (rnd >83 && rnd <86){ if (enemy->getAbsRect().y > 150)vagar = 3; }
			else if (rnd >85 && rnd < 88){ vagar = 4; }
		}
		if (rnd >= 88){
			float distRec;
			recolectorIn(distRec);
			float distCaz;
			cazadorIn(distCaz);
			if (distCaz < 2000 || distRec < 2000){
				if (rnd == 88)
					enemy->getPJuego()->getEstadoActual()->reproduceFx("Aullido1", enemy->getRect().x, enemy->getRect().y, 0);
				else if (rnd == 89)
					enemy->getPJuego()->getEstadoActual()->reproduceFx("Aullido2", enemy->getRect().x, enemy->getRect().y, 0);
				else
					enemy->getPJuego()->getEstadoActual()->reproduceFx("Aullido3", enemy->getRect().x, enemy->getRect().y, 0);
			}
		}
		cont = 0;
	}
	if (cont > 50){
		Punto cazP, recP;
		cazP.x = enemy->getCazador()->getAbsRect().x; cazP.y = enemy->getCazador()->getAbsRect().y;
		recP.x = enemy->getRecolector()->getAbsRect().x; recP.y = enemy->getRecolector()->getAbsRect().y;
		if (inTriangle(vista, cazP) && inTriangle(vista, recP)){
			float distRec, distCaz;
			detectado = true;
			recolectorIn(distRec);
			cazadorIn(distCaz);
			if (distRec < distCaz && enemy->getRecolector()->esDetectable()){
				enemy->setTarget(1);
				enemy->activaFollow();
				enemy->setEstado(Moviendo);
			}
			else if (enemy->getCazador()->esDetectable()){
				enemy->setTarget(0);
				enemy->activaFollow();
				enemy->setEstado(Moviendo);
			}
			cont = 0;
		}
		else if (inTriangle(vista, cazP) && enemy->getCazador()->esDetectable()){
			detectado = true;
			enemy->setTarget(0);
			enemy->activaFollow();
			enemy->setEstado(Moviendo);
			cont = 0;
		}
		else if (inTriangle(vista, recP) && enemy->getRecolector()->esDetectable()){
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
	compruebaRadio(enemy->getCasita()->getAbsRect(), distCasa);
	if (distCasa > 1000){
		cont = 0;
		enemy->desactivaFollow();
		enemy->setEstado(Volviendo);
	}
}
void Deteccion::movimiento(){
	dirAtaque = enemy->getDir();
	float distRec;
	recolectorIn(distRec);
	float distCaz;
	cazadorIn(distCaz);
	cont++;
	if (cont > 100)
	{
		acechar();
		cont = 0;
	}
	if (enemy->getTarget() == enemy->getRecolector() && enemy->getRecolector()->esDetectable()){
		dirAtaque = enemy->getDir();
		setVista(dirAtaque);
		if (distRec <= 80){
			preparaAtaque(1);
			enemy->setEstado(Atacando);
		}
	}
	else if (enemy->getTarget() == enemy->getCazador() && enemy->getCazador()->esDetectable()){
		if (distCaz <= 80){
			preparaAtaque(0);
			enemy->setEstado(Atacando);
		}
	}
}
void Deteccion::volviendo(){
	cont++;
	if (cont >= 500){
		cont = 0;
		dirAtaque = enemy->getDir();
		enemy->setEstado(Quieto);
	}
}
void Deteccion::atacando(){
	if (cont == 0)
		enemy->getPJuego()->getEstadoActual()->reproduceFx("Grunido", enemy->getRect().x, enemy->getRect().y, 0);
	if (cont < 100)
		cont++;
	else { enemy->setEstado(PostAtaque); cont = 0; }
	switch (dirAtaque)
	{
	case 4:
		if (cont < 100){
			enemy->setAbsRect(0, -2);
			enemy->setRect(0, -2);
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
			enemy->setAbsRect(0, 2);
			enemy->setRect(0, 2);
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
}
void Deteccion::postAtaque(){
	direccionAux = nullptr;
	if (cont == 0){ // Segun adonde atacara el lobo da la vuelta a una posicion u otra
		rnd = rand() % 2;
		if (ultAtaque == 0){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); dirAtaque = 5; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); dirAtaque = 3; }
		}
		else if (ultAtaque == 1){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); dirAtaque = 4; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); dirAtaque = 6; }
		}
		else if (ultAtaque == 2){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); dirAtaque = 5; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); dirAtaque = 7; }
		}
		else if (ultAtaque == 3){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); dirAtaque = 0; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); dirAtaque = 6; }
		}
		else if (ultAtaque == 4){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); dirAtaque = 7; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x - 100, enemy->getAbsRect().y); dirAtaque = 1; }
		}
		else if (ultAtaque == 5){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); dirAtaque = 0; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); dirAtaque = 2; }
		}
		else if (ultAtaque == 6){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); dirAtaque = 1; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y - 100); dirAtaque = 3; }
		}
		else if (ultAtaque == 7){
			if (rnd == 0){ delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x + 100, enemy->getAbsRect().y); dirAtaque = 4; }
			else { delete direccionAux; direccionAux = new ObjetoPG(enemy->getPJuego(), enemy->getAbsRect().x, enemy->getAbsRect().y + 100); dirAtaque = 2; }
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
		else enemy->setEstado(Moviendo);
		cont = 0;
	}
	cont++;
}
void Deteccion::atrapado(){
	if (cont == 0)enemy->desactivaFollow();
	if (enemy->life <= 0){ enemy->setEstado(Muerto); }
	cont++;
	if (cont >= 1000)
	{
		cont = 0;
		enemy->setEstado(Quieto);
	}
}
void Deteccion::herido(){		
	//Animacion Herido
	if (enemy->life < 0)
		enemy->setEstado(Muerto);
	else if (cont > 100){
		cont = 0;
		enemy->setEstado(Quieto);
	}
}
void Deteccion::muerto(){}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
void Deteccion::update() {

	enemy->setTarget(0);
	setVista(dirAtaque);
	switch (enemy->getEstado())
	{
	case Quieto:
		quieto();
		break;
	case Moviendo:
		movimiento();
		break;
	case Volviendo:
		volviendo();
		break;
	case Atacando:
		atacando();
		break;
	case Atrapado:
		atrapado();
		break;
	case PostAtaque:
		postAtaque();
		break;
	case Herido:
		herido();
		break;
	case Muerto:
		muerto();
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
	if (distCaz <  distRec && distCaz < 250 && enemy->getCazador()->esDetectable()) {//Llamamos al follow del lobo
		detectado = true;
		enemy->setTarget(0);
		//std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
		enemy->setEstado(Moviendo);
	}
	else if (distCaz >= distRec && distRec< 250 && enemy->getRecolector()->esDetectable()) {//Llamamos al follow del lobo
		detectado = true;
		enemy->setTarget(1);
		//std::cout << "TE SIGO JOPUTA" << "\n";
		enemy->activaFollow();
		enemy->setEstado(Moviendo);
	}
	else {
		detectado = false;
		enemy->setEstado(Quieto);
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