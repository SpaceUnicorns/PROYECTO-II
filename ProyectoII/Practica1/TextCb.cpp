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
}


TextCb::~TextCb()
{
}
void TextCb::draw(){
	if (reacciona && firstTime == 0){
		if (aux[cont][0] == 'L')
			active = "L";
		else if (aux[cont][0] == 'Z')
			active = "Z";
		if (cont2 < aux[cont].length()){
			timer2++;
			if (timer2 > 20){
			frase += aux[cont][cont2];
			font.w += 15;
			cont2++;
			timer2 = 0;
			}
		}
		pObj->getPJuego()->getTextura(TTextBox)->draw(pObj->getPJuego()->getRender(), textBox);
		if(active == "L")static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->drawFont(font, frase, colorLyov);
		else if (active == "Z")static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->drawFont(font, frase, colorZenia);
		else static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->drawFont(font, frase);
	}
}
void TextCb::callback(){
	std::cout << "TRIGGERED\n";
	reacciona = true;
}
void TextCb::update(){
	if (cont < aux.size()-1 && reacciona && firstTime == 0){
		timer++;
		if (timer >= 100){
			frase = " ";
			cont2 = 1;
			cont++; timer = 0;
			font.w = 50;
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