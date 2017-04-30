#include "Tutorial.h"
#include "Trigger.h"
#include "TextCb.h"
class changeScene :
	public Componente
{
public:
	changeScene(ObjetoJuego* ent, Nivel1* aux) : Componente(ent){ 
		reacciona = false; 
		pObj = dynamic_cast<Trigger*>(ent);
		this->aux = aux;
	};
	virtual ~changeScene(){};
	virtual void callback();
	virtual void update(){};
	virtual void draw(){};

private:
	bool reacciona;
	Trigger* pObj;
	Nivel1* aux;
};

void changeScene::callback(){
	if (!reacciona){
		aux->callback();
	}
	reacciona = true;
}

Tutorial::Tutorial(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz) : Nivel1(jug,map,objetos,posRec, posCaz, "R")
{
	firsTime = true;
	change = false;
	Trigger *auxTr; auxTr = new Trigger(pJuego, 8730, 10050, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial2Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 6810, 10280, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/tutorial1Lyov.txt"));
	auxTr->setTriggerDim(250, 250);
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 6950, 9202, pCazador, pRecolector);
	auxTr->setCallback(new changeScene(auxTr,this));
	auxTr->setTriggerDim(100, 800);
	vecTriggers.push_back(auxTr);
}

void Tutorial::onKeyUp(char k){
	if (k != 't') Nivel1::onKeyUp(k);
}
void Tutorial::update(){
	Nivel1::update();
	if (change){
		
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		Punto caz; caz.x = 6925; caz.y = 8930; Punto rec; rec.x = 6970; rec.y = 8930;
		pJuego->estados.push(new Nivel1(pJuego, "../docs/mapa.txt", "../docs/objetos.txt", rec, caz, "R"));
		delete borrar;
	}
}
void Tutorial::callback(){
	change = true;
	
}
Tutorial::~Tutorial()
{
}
