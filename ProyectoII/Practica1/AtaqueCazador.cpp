#include "AtaqueCazador.h"
#include "Lobo.h"
AtaqueCazador::AtaqueCazador(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
	pCBox = static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"));
	direccion = Default;
	firstime = true;
	axResistance = 10;
}


AtaqueCazador::~AtaqueCazador()
{
}
void AtaqueCazador::update(int delta){
	if (pObj->isAble()){
		if (firstime){
			pEstado = dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top());
			firstime = false;
		}
		equipo = dynamic_cast<Equipo*>(pObj->dameComponente("Equipo"));
		if (equipo->tieneEquipo("Hacha")){
			if (pObj->getPJuego()->input.e) {
				std::string fx; fx = "ZheniaAtaca" + std::to_string(rand() % 5);
				pEstado->reproduceFx(fx,0,0,0);
				int colAux;
				compMov = dynamic_cast<MovimientoP*>(pObj->dameComponente("MovimientoP"));
				switch (compMov->getDir())
				{
				case Up: nextPos.x = 0; nextPos.y = -15;
					break;
				case dDS: nextPos.x = 30; nextPos.y = -15;
					break;
				case Right:nextPos.x = 30; nextPos.y = 0;
					break;
				case dDI: nextPos.x = 30; nextPos.y = 15;
					break;
				case Down: nextPos.x = 0; nextPos.y = 30;
					break;
				case dII: nextPos.x = -30; nextPos.y = 15;
					break;
				case Left: nextPos.x = -30; nextPos.y = 0;
					break;
				case dIS: nextPos.x = -30; nextPos.y = -15;
					break;
				default:
					break;
				};
				colAux = pCBox->isColiding(nextPos, info);

				if (colAux == 5){
					pObj->getPJuego()->input.e = false;
					dynamic_cast<Lobo*>(info)->setLife(-1);
					dynamic_cast<Lobo*>(info)->setEstado(Herido);
					int rnd = rand() % 2;
					if (rnd == 0)
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboHerido", nextPos.x, nextPos.y, 0);
					else
						pObj->getPJuego()->getEstadoActual()->reproduceFx("LoboHerido1", nextPos.x, nextPos.y, 0);
				
					axResistance--;

					if (axResistance <= 0){ 
						equipo->removeEquipo("Hacha"); 
						axResistance = 10;
					}
				}
			}
		}
	}

}
