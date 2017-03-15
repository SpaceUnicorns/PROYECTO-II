#include "TextCb.h"
#include <string>


TextCb::TextCb(ObjetoJuego* ent, std:: string s) : Componente(ent)
{
	pObj = dynamic_cast<Trigger*>(ent);
	textBox.h = pObj->getPJuego()->getScreenHeight()*0.20;
	textBox.w = pObj->getPJuego()->getScreenWidth();
	textBox.x = 0;
	textBox.y = pObj->getPJuego()->getScreenHeight() - textBox.h;
	font.x = 50;
	font.y = textBox.y + 25;
	font.w = 225;
	font.h = 25;
	cont = 0;
	timer = 0;
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
	reacciona = false;
}


TextCb::~TextCb()
{
}
void TextCb::draw(){
	if (reacciona && firstTime == 0){
		pObj->getPJuego()->getTextura(TTextBox)->draw(pObj->getPJuego()->getRender(), textBox);
		static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->drawFont(font, aux[cont]);
	}
}
void TextCb::callback(){
	std::cout << "TRIGGERED\n";
	reacciona = true;
}
void TextCb::update(){
	if (cont < aux.size()-1 && reacciona && firstTime == 0){
		timer++;
		if (timer >= 90){
			cont++; timer = 0;
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