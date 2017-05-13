#include "MenuPrincipalComp.h"


MenuPrincipalComp::MenuPrincipalComp(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	estado = Jugar;
	temp = temp2 = delay= 0;
}


MenuPrincipalComp::~MenuPrincipalComp()
{
}

void MenuPrincipalComp::update()
{
	delay++;
	if (delay > 4){

		if (temp != 0){
			temp2++;
			if (temp2 >= 10){
				temp = temp2 = 0;
			}
		}
		switch (estado){
		case (Salir) :
			if (pObj->getPJuego()->input.arriba){
				if (temp == 0){
					pObj->getPJuego()->getEstadoActual()->reproduceFx("SelOpcionNormal1", 0, 0, 0);
					pObj->setRect(0, 200);
					estado = Cargar;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.abajo){
				if (temp == 0){
					pObj->getPJuego()->getEstadoActual()->reproduceFx("SelOpcionNormal1", 0, 0, 0);
					pObj->setRect(0, 100);
					estado = Jugar;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.enter){
				static_cast<MenuPrincipal*>(pEntidad)->opcion = 1;
			}
			break;
		case (Jugar) :
			if (pObj->getPJuego()->input.arriba){
				if (temp == 0){
					pObj->getPJuego()->getEstadoActual()->reproduceFx("SelOpcionNormal1", 0, 0, 0);
					pObj->setRect(0, -100);
					estado = Salir;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.abajo){
				if (temp == 0){
					pObj->getPJuego()->getEstadoActual()->reproduceFx("SelOpcionNormal1", 0, 0, 0);
					pObj->setRect(0, 100);
					estado = Cargar;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.enter){
				std::ifstream f;
				int button = 1;
				f.open("../docs/partidaGuardada/objs.txt", std::ios::in);
				std::string aux;
				f >> aux;
				if (!f.fail()) button = showMessage();
				pObj->getPJuego()->getEstadoActual()->reproduceFx("OpcionMenuNormal", 0, 0, 0);
				if(button == 1) static_cast<MenuPrincipal*>(pEntidad)->opcion = 2;

			}
			break;
		case(Cargar) :
			if (pObj->getPJuego()->input.arriba){
				if (temp == 0){
					pObj->getPJuego()->getEstadoActual()->reproduceFx("SelOpcionNormal1", 0, 0, 0);
					pObj->setRect(0, -100);
					estado = Jugar;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.abajo){
				if (temp == 0){
					pObj->getPJuego()->getEstadoActual()->reproduceFx("SelOpcionNormal1", 0, 0, 0);
					pObj->setRect(0, -200);
					estado = Salir;
					temp++;
				}
			}
			else if (pObj->getPJuego()->input.enter){
				pObj->getPJuego()->getEstadoActual()->reproduceFx("OpcionMenuNormal", 0, 0, 0);
				static_cast<MenuPrincipal*>(pEntidad)->opcion = 3;

			}
			break;
		}
	}

}
int MenuPrincipalComp::showMessage(){
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },

	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 125, 200, 0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{ 0, 255, 0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 0, 0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{ 0, 0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255, 0, 0 }
		}
	};
	
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		static_cast<ObjetoPG*>(pEntidad)->getPJuego()->getPWindow(), /* .window */
		"WARNING", /* .title */
		"Hay una partida guardada.\n Desea sobreescribirla?", /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return-1;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
	}
	else {
		return buttonid;
	}
}