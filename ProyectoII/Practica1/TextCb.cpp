#include "TextCb.h"
#include <string>


TextCb::TextCb(ObjetoJuego* ent) : Componente(ent)
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
	f.open("../docs/textos/dialogo1.txt", std::ios::in);
	std::string x;
	while (!f.eof()){
		//f >> x;
		getline(f,x);

		if (!f.fail()){
			aux.push_back(x);
		}
	}
	f.close();
	aux.push_back(" ");
	once = false;
}


TextCb::~TextCb()
{
}
void TextCb::draw(){
	if (pObj->isTriggering()){
		pObj->getPJuego()->getTextura(TTextBox)->draw(pObj->getPJuego()->getRender(), textBox);
		static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->drawFont(font, aux[cont]);
	}
}
void TextCb::callback(){
	std::cout << "TRIGGERED\n";
	
}
void TextCb::update(){
	if (cont < aux.size() -1 && pObj->isTriggering()){
		timer++;
		if (timer >= 90){
			cont++; timer = 0;
		}
	}
	else {
		cont = 0;
		if (pObj->isTriggering()){aux.clear();
		aux.push_back("Otra vez tu?");
		aux.push_back(" ");
		}
		pObj->setTriggered(false);
	}
	//pObj->swTriggered();
}