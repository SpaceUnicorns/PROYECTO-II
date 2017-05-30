#include "TextCb.h"
#include <string>
#include "Nivel1.h"

TextCb::TextCb(ObjetoJuego* ent, std:: string s) : Componente(ent)
{
	archivo = s;
	pObj = dynamic_cast<Trigger*>(ent);
	textBox.h = pObj->getPJuego()->getScreenHeight()*0.20;
	textBox.w = pObj->getPJuego()->getScreenWidth();
	textBox.x = 0;
	textBox.y = pObj->getPJuego()->getScreenHeight() - (textBox.h+50);
	font.x = 50;
	font.y = textBox.y + 60;
	font.w = 50;
	font.h = 25;
	cont = 0;
	timer = timer2= 0;
	f.open(s, std::ios::in);
	std::string x;
	while (!f.eof()){
		//f >> x;
		getline(f,x);

		if (!f.fail()){
			if (x[0] != '+')
				aux.push_back(x);
			else {
				getline(f, x);
				default = x;
			}
		}
	}
	f.close();
	aux.push_back(" ");
	firstTime = 0;
	cont2 = 1;
	reacciona = false;
	frase = " ";
	colorLyov.r = 51; colorLyov.g = 102; colorLyov.b = 0;
	colorZenia.r = 247; colorZenia.g = 25; colorZenia.b = 25;
	if (aux[0].length() > 15) delay = 250;
	else delay = 100;
	
	state = 0;
}


TextCb::~TextCb()
{
	delete estadoAux;
}
void TextCb::draw(){
	if (reacciona && firstTime == 0){
		if (aux[cont][0] == 'L'){
			active = "L";
		}
		else if (aux[cont][0] == 'Z'){
			active = "Z";
		}
		if (active == "Z" && timer == 1){ 
			int rnd = rand() % 6;
			if (rnd == 0)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("ZheniaHabla", pObj->getCausante("Cazador")->getRect().x, pObj->getCausante("Cazador")->getRect().y, 0); 
			if (rnd == 1)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("ZheniaHabla1", pObj->getCausante("Cazador")->getRect().x, pObj->getCausante("Cazador")->getRect().y, 0);
			if (rnd == 2)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("ZheniaHabla2", pObj->getCausante("Cazador")->getRect().x, pObj->getCausante("Cazador")->getRect().y, 0);
			if (rnd == 3)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("ZheniaHabla3", pObj->getCausante("Cazador")->getRect().x, pObj->getCausante("Cazador")->getRect().y, 0);
			if (rnd == 4)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("ZheniaHabla4", pObj->getCausante("Cazador")->getRect().x, pObj->getCausante("Cazador")->getRect().y, 0);
			if (rnd == 5)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("ZheniaHabla5", pObj->getCausante("Cazador")->getRect().x, pObj->getCausante("Cazador")->getRect().y, 0);
		}
		else if (active == "L"&& timer == 1){
			int rnd = rand() % 6;
			if (rnd == 0)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("LyovHabla", pObj->getCausante("Recolector")->getRect().x, pObj->getCausante("Recolector")->getRect().y, 0); 
			if (rnd == 1)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("LyovHabla1", pObj->getCausante("Recolector")->getRect().x, pObj->getCausante("Recolector")->getRect().y, 0);
			if (rnd == 2)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("LyovHabla2", pObj->getCausante("Recolector")->getRect().x, pObj->getCausante("Recolector")->getRect().y, 0);
			if (rnd == 3)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("LyovHabla3", pObj->getCausante("Recolector")->getRect().x, pObj->getCausante("Recolector")->getRect().y, 0);
			if (rnd == 4)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("LyovHabla4", pObj->getCausante("Recolector")->getRect().x, pObj->getCausante("Recolector")->getRect().y, 0);
			if (rnd == 5)
				pObj->getPJuego()->getEstadoActual()->reproduceFx("LyovHabla5", pObj->getCausante("Recolector")->getRect().x, pObj->getCausante("Recolector")->getRect().y, 0);
		}
		if (cont2 < aux[cont].length()){
			timer2++;
			if (timer2 > 3){
			frase += aux[cont][cont2];
			font.w += 15;
			cont2++;
			timer2 = 0;
			}
		}
		pObj->getPJuego()->getTextura(TTextBox)->draw(pObj->getPJuego()->getRender(), textBox);
		if(active == "L")estadoAux->drawFont(font, frase, colorLyov);
		else if (active == "Z")estadoAux->drawFont(font, frase, colorZenia);
		else estadoAux->drawFont(font, frase);
	}
}
void TextCb::callback(){

	if (!reacciona) estadoAux = static_cast<EstadoPG*>(pObj->getPJuego()->estados.top());
	int indice = pObj->getIndice();
	state = dynamic_cast<Nivel1*>(estadoAux)->getTriggerInfo()[pObj->getIndice()];
	dynamic_cast<Nivel1*>(estadoAux)->getTriggerInfo()[pObj->getIndice()] = 1;
	if(!reacciona)cargaDialogo();
	reacciona = true;
}
void TextCb::cargaDialogo(){
	
	if (state == 1){
		aux.clear();
		if (default[0] != '-') aux.push_back(default);
		aux.push_back(" ");
	}
}
void TextCb::update(int delta){
	if (cont < aux.size()-1 && reacciona && firstTime == 0){
		timer++;
		if (timer >= delay){
			frase = " ";
			cont2 = 1;
			cont++; timer = 0;
			font.w = 50;
			if (aux[0].length() > 15) delay = 200;
			else delay = 100;
		}
	}
	else {
		cont = 0;
		if (reacciona) firstTime++;
		reacciona = false;
		pObj->setReacciona(false);
	}
	if (firstTime > 0){
		aux.clear();
		if (default[0] != '-') aux.push_back(default);
		aux.push_back(" ");
	}
	if (!pObj->isTriggering()) 
		firstTime = 0;
	//pObj->swTriggered();
}