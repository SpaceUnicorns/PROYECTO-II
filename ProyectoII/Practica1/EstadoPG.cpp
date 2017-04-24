#include "EstadoPG.h"
#include "Error.h"

// Es importante ejecutar el metodo cargarAudio al principio de cada escena en la constructora despues de ejecutar la constructora del padre.
// Tambien es importante cargar los audios en el mapa de fx y el mapa de musicas
EstadoPG::EstadoPG(juegoPG*jug, int puntos)
{
	pJuego = jug;
	fondo.h = 480;
	fondo.w = 640;
	fondo.x = fondo.y = 0;
	contPuntos = puntos;

}


EstadoPG::~EstadoPG()
{
	
	for (auto it : vecObj) {
		delete it;
	}

	FMOD_RESULT result;
	if (!pJuego->hasExit()){
		for (auto it : vfx) {
			it.second->release();
		}
		
		for (auto it : vmusic) {
			it.second->release();
		}

			mainGroup->release();
			result = reverbGroup->release();
			result = reverbUnit->release();
			result = reverbGroup->removeDSP(reverbUnit);
			result = reverbUnit->disconnectAll(true, true);
	}
	
}

void::EstadoPG::cargarAssetsAudio(std::string txt, char tipo){
	std::ifstream f;
	FMOD::Sound* sound;
	std::string aux, clave;
	std::string cabecera = "../sounds/";
	f.open(txt, std::ios::in);
	while (!f.eof()){
		f >> aux;
		clave = aux;
		if (tipo == 'f'){
			aux = cabecera + aux + ".wav";
			pJuego->system->createSound(aux.c_str(), FMOD_3D, 0, &sound);
			sound->set3DMinMaxDistance(0.5f, 5000.0f);
			vfx.insert(std::pair<std::string, FMOD::Sound*>(clave, sound));

		}
		else if (tipo == 'm'){
			aux = cabecera + aux + ".mp3";
			pJuego->system->createSound(aux.c_str(), FMOD_3D, 0, &sound);
			sound->set3DMinMaxDistance(0.5f, 5000.0f);
			vmusic.insert(std::pair<std::string, FMOD::Sound*>(clave, sound));
		}
	}
	f.close();
}
void EstadoPG::cargarAudio(std::string irPath){
	// Sistema de audio

	pJuego->system->createChannelGroup("reverb", &reverbGroup);
	pJuego->system->createChannelGroup("main", &mainGroup);
	/*
	Creamos el recurso dcp y lo añadimos a la reverb
	*/
	
	pJuego->system->createDSPByType(FMOD_DSP_TYPE_CONVOLUTIONREVERB, &reverbUnit);
	reverbGroup->addDSP(FMOD_CHANNELCONTROL_DSP_TAIL, reverbUnit);

	/*
	No vamos a usar el audio asi que lo abrimos solo para leer
	*/
	FMOD::Sound* irSound;
	pJuego->system->createSound(irPath.c_str(), FMOD_DEFAULT | FMOD_OPENONLY, NULL, &irSound);

	/*
	Cogemos la informacion del archivo de audio
	*/
	FMOD_SOUND_FORMAT irSoundFormat;
	FMOD_SOUND_TYPE irSoundType;
	int irSoundBits, irSoundChannels;
	irSound->getFormat(&irSoundType, &irSoundFormat, &irSoundChannels, &irSoundBits);
	unsigned int irSoundLength;
	irSound->getLength(&irSoundLength, FMOD_TIMEUNIT_PCM);

	/*
	El formato del archivo de respuesta a impulso debe ser wav, PCM, 16 bits, 48 kh, el numero de canales no es importante
	*/
	unsigned int irDataLength = sizeof(short)* (irSoundLength * irSoundChannels + 1);
	short* irData = (short*)malloc(irDataLength);
	irData[0] = (short)irSoundChannels;
	unsigned int irDataRead;
	irSound->readData(&irData[1], irDataLength - sizeof(short), &irDataRead);
	reverbUnit->setParameterData(FMOD_DSP_CONVOLUTION_REVERB_PARAM_IR, irData, irDataLength);

	/*
	Tenemos un canal en seco y otro con la reverb sola
	*/
	reverbUnit->setParameterFloat(FMOD_DSP_CONVOLUTION_REVERB_PARAM_DRY, -80.0f);

	/*
	Liberamos el recurso de respuesta a impulso
	*/
	free(irData);
	irSound->release();

	pJuego->system->set3DSettings(1.0, 1.0, 1.0);
	FMOD_VECTOR forward = { 0.0f, 1.0f, 0.0f };
	FMOD_VECTOR up = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR listenerpos = { 0, 0, 0};
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };;
	pJuego->system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);
	pJuego->system->update();
}
void EstadoPG::reproduceFx(std::string fx, float x, float y, float wet){
	FMOD_VECTOR pos = { -x , -1, y };
	FMOD_VECTOR forward = { 0.0f, 1.0f, 0.0f };
	FMOD_VECTOR up = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

		bool cOcupied = false;
		cfx1->isPlaying(&cOcupied);
		FMOD::Sound* s = vfx[fx];
		if (!cOcupied){
			pJuego->system->playSound(s, mainGroup, false, &cfx1);
			//cfx1->set3DAttributes(&pos, &vel);
			cfx1->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
			reverbUnit->addInput(channelHead, &reverbConnectionfx1, FMOD_DSPCONNECTION_TYPE_SEND);
			reverbConnectionfx1->setMix(0.50f);
		}
		else {
			cOcupied = false;
			//FMOD::Sound *s = vfx[fx]; -- REVISAR ESTILO
			cfx2->isPlaying(&cOcupied);
			if (!cOcupied){
				pJuego->system->playSound(s, mainGroup, false, &cfx2);
			//	cfx2->set3DAttributes(&pos, &vel);
				cfx2->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
				reverbUnit->addInput(channelHead, &reverbConnectionfx2, FMOD_DSPCONNECTION_TYPE_SEND);
				reverbConnectionfx2->setMix(0.50f);
			}
			else{
				cOcupied = false;
				cfx3->isPlaying(&cOcupied);
				if (!cOcupied){
					pJuego->system->playSound(s, mainGroup, false, &cfx3);
					//cfx3->set3DAttributes(&pos, &vel);
					cfx3->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
					reverbUnit->addInput(channelHead, &reverbConnectionfx3, FMOD_DSPCONNECTION_TYPE_SEND);
					reverbConnectionfx3->setMix(0.50f);
				}
				else {
					cOcupied = false;
					cfx4->isPlaying(&cOcupied);
					if (!cOcupied){
						pJuego->system->playSound(s, mainGroup, false, &cfx1);
					}
					else {
						cfx4->stop();
						pJuego->system->playSound(s, mainGroup, false, &cfx1);
					}
					//cfx4->set3DAttributes(&pos, &vel);
					cfx4->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
					reverbUnit->addInput(channelHead, &reverbConnectionfx4, FMOD_DSPCONNECTION_TYPE_SEND);
					reverbConnectionfx4->setMix(0.50f);
				}
			}
		}
		pJuego->system->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
		pJuego->system->update();

}
void EstadoPG::reproduceMusica(std::string music, bool fade){

		bool cOcupied = false;
		cmusic1->isPlaying(&cOcupied);
		if (cOcupied){
			vmusic.at(music)->setMode(FMOD_LOOP_NORMAL);
			pJuego->system->playSound(vmusic.at(music), mainGroup, false, &cmusic2);
			if (fade){
				unsigned long long parentclock;
				cmusic2->getDSPClock(NULL, &parentclock);
				cmusic2->addFadePoint(parentclock, 0.0f);
				cmusic2->addFadePoint(parentclock + 4096, 1.0f);
			}
			cMusic = 2;
		}

		else{
			vmusic.at(music)->setMode(FMOD_LOOP_NORMAL);
			pJuego->system->playSound(vmusic.at(music), mainGroup, false, &cmusic1);

			if (fade){
				unsigned long long parentclock;
				cmusic1->getDSPClock(NULL, &parentclock);
				cmusic1->addFadePoint(parentclock, 0.0f);
				cmusic1->addFadePoint(parentclock + 4096, 1.0f);
			}
			cMusic = 1;
		}
}
void EstadoPG::paraMusica(std::string music, bool fade){
	try {
		if (cMusic == 1){
			if (fade){
				unsigned long long parentclock;
				cmusic1->getDSPClock(NULL, &parentclock);
				cmusic1->addFadePoint(parentclock, 1.0f);
				cmusic1->addFadePoint(parentclock + 4096, 0.0f);
			}
			cmusic1->stop();
		}
		if (cMusic == 2){
			if (fade){
				unsigned long long parentclock;
				cmusic2->getDSPClock(NULL, &parentclock);
				cmusic2->addFadePoint(parentclock, 1.0f);
				cmusic2->addFadePoint(parentclock + 4096, 0.0f);
			}
			cmusic2->stop();
		}
	}
	catch (std::exception e){}
}

void EstadoPG::reproduceAmb(std::string amb, bool fade){
	try {
		bool cOcupied = false;
		camb1->isPlaying(&cOcupied);
		if (cOcupied){
			pJuego->system->playSound(vmusic.at(amb), mainGroup, false, &camb2);
			vmusic.at(amb)->setMode(FMOD_LOOP_NORMAL);
			if (fade){
				unsigned long long parentclock;
				camb2->getDSPClock(NULL, &parentclock);
				camb2->addFadePoint(parentclock, 0.0f);
				camb2->addFadePoint(parentclock + 4096, 1.0f);
			}
			camb1->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
			reverbUnit->addInput(channelHead, &reverbConnectionamb1, FMOD_DSPCONNECTION_TYPE_SEND);
			reverbConnectionamb1->setMix(0.50f);
			cAmb = 2;
		}

		else{
			pJuego->system->playSound(vmusic.at(amb), mainGroup, false, &camb1);
			vmusic.at(amb)->setMode(FMOD_LOOP_NORMAL);
			if (fade){
				unsigned long long parentclock;
				camb1->getDSPClock(NULL, &parentclock);
				camb1->addFadePoint(parentclock, 0.0f);
				camb1->addFadePoint(parentclock + 4096, 1.0f);
			}
			camb2->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
			reverbUnit->addInput(channelHead, &reverbConnectionamb1, FMOD_DSPCONNECTION_TYPE_SEND);
			reverbConnectionamb1->setMix(0.50f);
			cAmb = 1;
		}
	}
	catch (std::exception e){}
}
void EstadoPG::paraAmb(std::string amb, bool fade){
	//try {
		if (cMusic == 1){
			if (fade){
				unsigned long long parentclock;
				cmusic1->getDSPClock(NULL, &parentclock);
				cmusic1->addFadePoint(parentclock, 1.0f);
				cmusic1->addFadePoint(parentclock + 4096, 0.0f);
			}
			cmusic1->stop();
		}
		if (cMusic == 2){
			if (fade){
				unsigned long long parentclock;
				cmusic2->getDSPClock(NULL, &parentclock);
				cmusic2->addFadePoint(parentclock, 1.0f);
				cmusic2->addFadePoint(parentclock + 4096, 0.0f);
			}
			cmusic2->stop();
		}
	//}
	//catch (std::exception e){}
}


void EstadoPG::draw(){
	//Draw background
	pJuego->getTextura(et)->draw(pJuego->getRender(), fondo);
	//drawFont();

	for (unsigned int i = 0; i < vecObj.size(); i++)
		vecObj[i]->draw();


}
void EstadoPG::drawFont(SDL_Rect rect, std::string const & s, SDL_Color color){
	//Dibujar puntos
	//try{// bloque try catch
			pJuego->getFuente()->loadFromText(pJuego->getRender(), s, color);
			pJuego->getFuente()->draw(pJuego->getRender(), rect);
	//	}
		//catch (ELoadFont & e){}
	}

void EstadoPG::update(){
	for (unsigned int i = 0; i < vecObj.size(); i++){
		vecObj[i]->update();
	}
	for (unsigned int i = 0; i < vecTriggers.size(); i++){
		vecTriggers[i]->update();
	}
}

void EstadoPG::lateUpdate(){
	for (unsigned int i = 0; i < vecObj.size(); i++){
		vecObj[i]->lateUpdate();
	}
}
void EstadoPG::onClick(){
	bool encontrado = false;
	int it = vecObj.size() - 1;
	while (!encontrado && it >= 0){
		encontrado = vecObj[it]->onClick();
		it--;
	}
}
void EstadoPG::onOver(){
	bool encontrado = false;
	int it = vecObj.size() - 1;
	while (!encontrado && it >= 0){
		encontrado = vecObj[it]->onOver();
		it--;
	}
}
void EstadoPG::updateBorrarObj()
{
	int x = 0;
	if (vecBorrar.size() > 0)
	{
		std::cout << " ";
	}
	for (size_t i = 0; i < vecBorrar.size(); i++)
	{
		for (size_t j = 0; j < vecObj.size(); j++)
		{
			if (vecBorrar[i] == vecObj[j]) {
				x = j;
			}
		}
		delete vecObj[x];
		vecObj.resize(vecObj.size() - 1);
	}
	vecBorrar.clear();
}
void EstadoPG::cargaMapa(std::string txt, std::vector<char>& mapa)
{
	std::ifstream f; char aux = 'p';
	int x = 0;
	int y = -31;
	Tile aux2;
	TrianguloBorde auxBorde;
	Punto auxPunto;
	SDL_Rect rectAux; rectAux.x = rectAux.y = -1; rectAux.w = 122; rectAux.h = 83;
	f.open(txt, std::ios::in);
	int tile;
	while (!f.eof() && !f.fail()){
		f >> tile;
		if (!f.fail()){
			if (tile == 0 ){
				//Creamos los puntos de los triangulos que forman un sprite. Cada sprite al ser un rombo forma dos rectángulos. 
				//Calculamos los puntos de los dos rectangulos y los añadimos al vector de Bordes
				auxPunto.x = x; auxPunto.y = y + 32; auxBorde.A = auxPunto;
				auxPunto.x = x + 62; auxPunto.y = y; auxBorde.B = auxPunto;
				auxPunto.x = x + 122; auxPunto.y = y + 32; auxBorde.C = auxPunto;
				vectBordes.push_back(auxBorde);
				auxPunto.x = x + 62; auxPunto.y = y + 62; auxBorde.B = auxPunto;
				vectBordes.push_back(auxBorde);
				//Con estas líneas se muestra en pantalla el sprite de los colliders de los bordes del mapa
				/*rectAux.x = 244; aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				vecTile.push_back(aux2); */
				mapa.push_back('X');
			}
			else if (tile == 999) mapa.push_back('L');
			else mapa.push_back('s');
			//std::cout << x << "\n";
			switch (tile){
			case 0:
				x += 122;
				break;
				//Tile nieve
			case 1:
				rectAux.x = 0; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 2:
				rectAux.x = 1 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 3:
				rectAux.x = 2 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 4:
				rectAux.x = 3 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 5:
				rectAux.x = 4 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 6:
				rectAux.x = 5 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 7:
				rectAux.x = 6 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 8:
				rectAux.x = 7 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 9:
				rectAux.x = 8 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 10:
				rectAux.x = 9 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 11:
				rectAux.x = 10 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 12:
				rectAux.x = 11 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 13:
				rectAux.x = 12 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 14:
				rectAux.x = 13 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 15:
				rectAux.x = 14 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 16:
				rectAux.x = 15 * 122; rectAux.y = 20 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////////////// Rampa 1
			case 20:
				rectAux.x = 0; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 21:
				rectAux.x = 1 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 22:
				rectAux.x = 2 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 23:
				rectAux.x = 3 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 24:
				rectAux.x = 4 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 25:
				rectAux.x = 5 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 26:
				rectAux.x = 6 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 27:
				rectAux.x = 7 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 28:
				rectAux.x = 8 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 29:
				rectAux.x = 9 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 30:
				rectAux.x = 10 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 31:
				rectAux.x = 11 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 32:
				rectAux.x = 12 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 33:
				rectAux.x = 13 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 34:
				rectAux.x = 14 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 35:
				rectAux.x = 15 * 122; rectAux.y = 56 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////// Rampa 2
			case 40:
				rectAux.x = 0; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 41:
				rectAux.x = 1 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 42:
				rectAux.x = 2 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 43:
				rectAux.x = 3 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 44:
				rectAux.x = 4 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 45:
				rectAux.x = 5 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 46:
				rectAux.x = 6 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 47:
				rectAux.x = 7 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 48:
				rectAux.x = 8 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 49:
				rectAux.x = 9 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 50:
				rectAux.x = 10 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 51:
				rectAux.x = 11 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 52:
				rectAux.x = 12 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 53:
				rectAux.x = 13 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 54:
				rectAux.x = 14 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 55:
				rectAux.x = 15 * 122; rectAux.y = 57 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////////////////// bosque full
			case 60:
				rectAux.x = 0; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 61:
				rectAux.x = 1 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 62:
				rectAux.x = 2 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 63:
				rectAux.x = 3 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 64:
				rectAux.x = 4 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 65:
				rectAux.x = 5 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 66:
				rectAux.x = 6 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 67:
				rectAux.x = 7 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 68:
				rectAux.x = 8 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 69:
				rectAux.x = 9 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 70:
				rectAux.x = 10 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 71:
				rectAux.x = 11 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 72:
				rectAux.x = 12 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 73:
				rectAux.x = 13 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 74:
				rectAux.x = 14 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 75:
				rectAux.x = 15 * 122; rectAux.y = 19 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////////////////// Bosque N
			case 80:
				rectAux.x = 0; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 81:
				rectAux.x = 1 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 82:
				rectAux.x = 2 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 83:
				rectAux.x = 3 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 84:
				rectAux.x = 4 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 85:
				rectAux.x = 5 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 86:
				rectAux.x = 6 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 87:
				rectAux.x = 7 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 88:
				rectAux.x = 8 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 89:
				rectAux.x = 9 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 90:
				rectAux.x = 10 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 91:
				rectAux.x = 11 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 92:
				rectAux.x = 12 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 93:
				rectAux.x = 13 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 94:
				rectAux.x = 14 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 95:
				rectAux.x = 15 * 122; rectAux.y = 21 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////// Bosque S
			case 120:
				rectAux.x = 0; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 121:
				rectAux.x = 1 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 122:
				rectAux.x = 2 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 123:
				rectAux.x = 3 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 124:
				rectAux.x = 4 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 125:
				rectAux.x = 5 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 126:
				rectAux.x = 6 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 127:
				rectAux.x = 7 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 128:
				rectAux.x = 8 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 129:
				rectAux.x = 9 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 130:
				rectAux.x = 10 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 131:
				rectAux.x = 11 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 132:
				rectAux.x = 12 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 133:
				rectAux.x = 13 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 134:
				rectAux.x = 14 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 135:
				rectAux.x = 15 * 122; rectAux.y = 24 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////////////////// bosque W
			case 100:
				rectAux.x = 0; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 101:
				rectAux.x = 1 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 102:
				rectAux.x = 2 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 103:
				rectAux.x = 3 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 104:
				rectAux.x = 4 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 105:
				rectAux.x = 5 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 106:
				rectAux.x = 6 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 107:
				rectAux.x = 7 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 108:
				rectAux.x = 8 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 109:
				rectAux.x = 9 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 110:
				rectAux.x = 10 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 111:
				rectAux.x = 11 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 112:
				rectAux.x = 12 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 113:
				rectAux.x = 13 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 114:
				rectAux.x = 14 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 115:
				rectAux.x = 15 * 122; rectAux.y = 22 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////////////////////// bosque E
			case 140:
				rectAux.x = 0; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 141:
				rectAux.x = 1 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 142:
				rectAux.x = 2 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 143:
				rectAux.x = 3 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 144:
				rectAux.x = 4 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 145:
				rectAux.x = 5 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 146:
				rectAux.x = 6 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 147:
				rectAux.x = 7 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 148:
				rectAux.x = 8 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 149:
				rectAux.x = 9 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 150:
				rectAux.x = 10 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 151:
				rectAux.x = 11 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 152:
				rectAux.x = 12 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 153:
				rectAux.x = 13 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 154:
				rectAux.x = 14 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 155:
				rectAux.x = 15 * 122; rectAux.y = 23 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////////////// Bosque Ne
			case 160:
				rectAux.x = 0; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 161:
				rectAux.x = 1 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 162:
				rectAux.x = 2 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 163:
				rectAux.x = 3 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 164:
				rectAux.x = 4 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 165:
				rectAux.x = 5 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 166:
				rectAux.x = 6 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 167:
				rectAux.x = 7 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 168:
				rectAux.x = 8 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 169:
				rectAux.x = 9 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 170:
				rectAux.x = 10 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 171:
				rectAux.x = 11 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 172:
				rectAux.x = 12 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 173:
				rectAux.x = 13 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 174:
				rectAux.x = 14 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 175:
				rectAux.x = 15 * 122; rectAux.y = 25 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////////////////////// Bosque NW
			case 180:
				rectAux.x = 0; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 181:
				rectAux.x = 1 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 182:
				rectAux.x = 2 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 183:
				rectAux.x = 3 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 184:
				rectAux.x = 4 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 185:
				rectAux.x = 5 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 186:
				rectAux.x = 6 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 187:
				rectAux.x = 7 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 188:
				rectAux.x = 8 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 189:
				rectAux.x = 9 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 190:
				rectAux.x = 10 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 191:
				rectAux.x = 11 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 192:
				rectAux.x = 12 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 193:
				rectAux.x = 13 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 194:
				rectAux.x = 14 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 195:
				rectAux.x = 15 * 122; rectAux.y = 28 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////////////////////Bosque SE
			case 200:
				rectAux.x = 0; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 201:
				rectAux.x = 1 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 202:
				rectAux.x = 2 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 203:
				rectAux.x = 3 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 204:
				rectAux.x = 4 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 205:
				rectAux.x = 5 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 206:
				rectAux.x = 6 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 207:
				rectAux.x = 7 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 208:
				rectAux.x = 8 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 209:
				rectAux.x = 9 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 210:
				rectAux.x = 10 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 211:
				rectAux.x = 11 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 212:
				rectAux.x = 12 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 213:
				rectAux.x = 13 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 214:
				rectAux.x = 14 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 215:
				rectAux.x = 15 * 122; rectAux.y = 26 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////////// Bosque SW
			case 220:
				rectAux.x = 0; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 221:
				rectAux.x = 1 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 222:
				rectAux.x = 2 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 223:
				rectAux.x = 3 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 224:
				rectAux.x = 4 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 225:
				rectAux.x = 5 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 226:
				rectAux.x = 6 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 227:
				rectAux.x = 7 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 228:
				rectAux.x = 8 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 229:
				rectAux.x = 9 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 230:
				rectAux.x = 10 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 231:
				rectAux.x = 11 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 232:
				rectAux.x = 12 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 233:
				rectAux.x = 13 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 234:
				rectAux.x = 14 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 235:
				rectAux.x = 15 * 122; rectAux.y = 27 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////// Bosque NWE
			case 240:
				rectAux.x = 0; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 241:
				rectAux.x = 1 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 242:
				rectAux.x = 2 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 243:
				rectAux.x = 3 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 244:
				rectAux.x = 4 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 245:
				rectAux.x = 5 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 246:
				rectAux.x = 6 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 247:
				rectAux.x = 7 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 248:
				rectAux.x = 8 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 249:
				rectAux.x = 9 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 250:
				rectAux.x = 10 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 251:
				rectAux.x = 11 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 252:
				rectAux.x = 12 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 253:
				rectAux.x = 13 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 254:
				rectAux.x = 14 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 255:
				rectAux.x = 15 * 122; rectAux.y = 30 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////////// Bosque SWE
			case 260:
				rectAux.x = 0; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 261:
				rectAux.x = 1 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 262:
				rectAux.x = 2 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 263:
				rectAux.x = 3 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 264:
				rectAux.x = 4 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 265:
				rectAux.x = 5 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 266:
				rectAux.x = 6 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 267:
				rectAux.x = 7 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 268:
				rectAux.x = 8 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 269:
				rectAux.x = 9 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 270:
				rectAux.x = 10 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 271:
				rectAux.x = 11 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 272:
				rectAux.x = 12 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 273:
				rectAux.x = 13 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 274:
				rectAux.x = 14 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 275:
				rectAux.x = 15 * 122; rectAux.y = 32 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////// Bosque NWS
			case 280:
				rectAux.x = 0; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 281:
				rectAux.x = 1 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 282:
				rectAux.x = 2 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 283:
				rectAux.x = 3 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 284:
				rectAux.x = 4 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 285:
				rectAux.x = 5 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 286:
				rectAux.x = 6 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 287:
				rectAux.x = 7 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 288:
				rectAux.x = 8 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 289:
				rectAux.x = 9 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 290:
				rectAux.x = 10 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 291:
				rectAux.x = 11 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 292:
				rectAux.x = 12 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 293:
				rectAux.x = 13 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 294:
				rectAux.x = 14 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 295:
				rectAux.x = 15 * 122; rectAux.y = 29 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////////////////////// Bosque NES
			case 300:
				rectAux.x = 0; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 301:
				rectAux.x = 1 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 302:
				rectAux.x = 2 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 303:
				rectAux.x = 3 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 304:
				rectAux.x = 4 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 305:
				rectAux.x = 5 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 306:
				rectAux.x = 6 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 307:
				rectAux.x = 7 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 308:
				rectAux.x = 8 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 309:
				rectAux.x = 9 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 310:
				rectAux.x = 10 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 311:
				rectAux.x = 11 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 312:
				rectAux.x = 12 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 313:
				rectAux.x = 13 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 314:
				rectAux.x = 14 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 315:
				rectAux.x = 15 * 122; rectAux.y = 31 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////////// Bosque NWSE
			case 320:
				rectAux.x = 0; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 321:
				rectAux.x = 1 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 322:
				rectAux.x = 2 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 323:
				rectAux.x = 3 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 324:
				rectAux.x = 4 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 325:
				rectAux.x = 5 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 326:
				rectAux.x = 6 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 327:
				rectAux.x = 7 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 328:
				rectAux.x = 8 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 329:
				rectAux.x = 9 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 330:
				rectAux.x = 10 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 331:
				rectAux.x = 11 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 332:
				rectAux.x = 12 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 333:
				rectAux.x = 13 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 334:
				rectAux.x = 14 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 335:
				rectAux.x = 15 * 122; rectAux.y = 37 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////////////// Bosque esq NE
			case 340:
				rectAux.x = 0; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 341:
				rectAux.x = 1 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 342:
				rectAux.x = 2 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 343:
				rectAux.x = 3 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 344:
				rectAux.x = 4 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 345:
				rectAux.x = 5 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 346:
				rectAux.x = 6 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 347:
				rectAux.x = 7 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 348:
				rectAux.x = 8 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 349:
				rectAux.x = 9 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 350:
				rectAux.x = 10 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 351:
				rectAux.x = 11 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 352:
				rectAux.x = 12 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 353:
				rectAux.x = 13 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 354:
				rectAux.x = 14 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 355:
				rectAux.x = 15 * 122; rectAux.y = 36 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////////////////// Bosque esq NW
			case 360:
				rectAux.x = 0; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 361:
				rectAux.x = 1 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 362:
				rectAux.x = 2 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 363:
				rectAux.x = 3 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 364:
				rectAux.x = 4 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 365:
				rectAux.x = 5 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 366:
				rectAux.x = 6 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 367:
				rectAux.x = 7 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 368:
				rectAux.x = 8 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 369:
				rectAux.x = 9 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 370:
				rectAux.x = 10 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 371:
				rectAux.x = 11 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 372:
				rectAux.x = 12 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 373:
				rectAux.x = 13 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 374:
				rectAux.x = 14 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 375:
				rectAux.x = 15 * 122; rectAux.y = 34 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////////////// Bosque Esquina SE
			case 380:
				rectAux.x = 0; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 381:
				rectAux.x = 1 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 382:
				rectAux.x = 2 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 383:
				rectAux.x = 3 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 384:
				rectAux.x = 4 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 385:
				rectAux.x = 5 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 386:
				rectAux.x = 6 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 387:
				rectAux.x = 7 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 388:
				rectAux.x = 8 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 389:
				rectAux.x = 9 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 390:
				rectAux.x = 10 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 391:
				rectAux.x = 11 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 392:
				rectAux.x = 12 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 393:
				rectAux.x = 13 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 394:
				rectAux.x = 14 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 395:
				rectAux.x = 15 * 122; rectAux.y = 35 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////// Bosque Esquina SW
			case 400:
				rectAux.x = 0; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 401:
				rectAux.x = 1 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 402:
				rectAux.x = 2 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 403:
				rectAux.x = 3 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 404:
				rectAux.x = 4 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 405:
				rectAux.x = 5 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 406:
				rectAux.x = 6 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 407:
				rectAux.x = 7 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 408:
				rectAux.x = 8 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 409:
				rectAux.x = 9 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 410:
				rectAux.x = 10 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 411:
				rectAux.x = 11 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 412:
				rectAux.x = 12 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 413:
				rectAux.x = 13 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 414:
				rectAux.x = 14 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 415:
				rectAux.x = 15 * 122; rectAux.y = 33 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////// Lago full
			case 420:
				rectAux.x = 0; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 421:
				rectAux.x = 1 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 422:
				rectAux.x = 2 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 423:
				rectAux.x = 3 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 424:
				rectAux.x = 4 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 425:
				rectAux.x = 5 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 426:
				rectAux.x = 6 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 427:
				rectAux.x = 7 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 428:
				rectAux.x = 8 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 429:
				rectAux.x = 9 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 430:
				rectAux.x = 10 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 431:
				rectAux.x = 11 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 432:
				rectAux.x = 12 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 433:
				rectAux.x = 13 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 434:
				rectAux.x = 14 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 435:
				rectAux.x = 15 * 122; rectAux.y = 0;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////// Lago Norte
			case 440:
				rectAux.x = 0; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 441:
				rectAux.x = 1 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 442:
				rectAux.x = 2 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 443:
				rectAux.x = 3 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 444:
				rectAux.x = 4 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 445:
				rectAux.x = 5 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 446:
				rectAux.x = 6 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 447:
				rectAux.x = 7 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 448:
				rectAux.x = 8 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 449:
				rectAux.x = 9 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 450:
				rectAux.x = 10 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 451:
				rectAux.x = 11 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 452:
				rectAux.x = 12 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 453:
				rectAux.x = 13 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 454:
				rectAux.x = 14 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 455:
				rectAux.x = 15 * 122; rectAux.y = 13 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////// Lago Sur
			case 460:
				rectAux.x = 0; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 461:
				rectAux.x = 1 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 462:
				rectAux.x = 2 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 463:
				rectAux.x = 3 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 464:
				rectAux.x = 4 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 465:
				rectAux.x = 5 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 466:
				rectAux.x = 6 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 467:
				rectAux.x = 7 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 468:
				rectAux.x = 8 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 469:
				rectAux.x = 9 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 470:
				rectAux.x = 10 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 471:
				rectAux.x = 11 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 472:
				rectAux.x = 12 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 473:
				rectAux.x = 13 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 474:
				rectAux.x = 14 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 475:
				rectAux.x = 15 * 122; rectAux.y = 12 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////// Lago W
			case 480:
				rectAux.x = 0; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 481:
				rectAux.x = 1 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 482:
				rectAux.x = 2 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 483:
				rectAux.x = 3 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 484:
				rectAux.x = 4 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 485:
				rectAux.x = 5 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 486:
				rectAux.x = 6 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 487:
				rectAux.x = 7 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 488:
				rectAux.x = 8 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 489:
				rectAux.x = 9 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 490:
				rectAux.x = 10 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 491:
				rectAux.x = 11 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 492:
				rectAux.x = 12 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 493:
				rectAux.x = 13 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 494:
				rectAux.x = 14 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 495:
				rectAux.x = 15 * 122; rectAux.y = 11 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////// Lago E
			case 500:
				rectAux.x = 0; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 501:
				rectAux.x = 1 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 502:
				rectAux.x = 2 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 503:
				rectAux.x = 3 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 504:
				rectAux.x = 4 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 505:
				rectAux.x = 5 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 506:
				rectAux.x = 6 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 507:
				rectAux.x = 7 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 508:
				rectAux.x = 8 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 509:
				rectAux.x = 9 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 510:
				rectAux.x = 10 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 511:
				rectAux.x = 11 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 512:
				rectAux.x = 12 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 513:
				rectAux.x = 13 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 514:
				rectAux.x = 14 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 515:
				rectAux.x = 15 * 122; rectAux.y = 14 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////////////////////////////// Lago NE
			case 520:
				rectAux.x = 0 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 521:
				rectAux.x = 1 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 522:
				rectAux.x = 2 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 523:
				rectAux.x = 3 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 524:
				rectAux.x = 4 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 525:
				rectAux.x = 5 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 526:
				rectAux.x = 6 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 527:
				rectAux.x = 7 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 528:
				rectAux.x = 8 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 529:
				rectAux.x = 9 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 530:
				rectAux.x = 10 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 531:
				rectAux.x = 11 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 532:
				rectAux.x = 12 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 533:
				rectAux.x = 13 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 534:
				rectAux.x = 14 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 535:
				rectAux.x = 15 * 122; rectAux.y = 9 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////////////// Lago NW
			case 540:
				rectAux.x = 0 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 541:
				rectAux.x = 1 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 542:
				rectAux.x = 2 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 543:
				rectAux.x = 3 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 544:
				rectAux.x = 4 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 545:
				rectAux.x = 5 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 546:
				rectAux.x = 6 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 547:
				rectAux.x = 7 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 548:
				rectAux.x = 8 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 549:
				rectAux.x = 9 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 550:
				rectAux.x = 10 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 551:
				rectAux.x = 11 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 552:
				rectAux.x = 12 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 553:
				rectAux.x = 13 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 554:
				rectAux.x = 14 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 555:
				rectAux.x = 15 * 122; rectAux.y = 5 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////////////////Lago SE
			case 560:
				rectAux.x = 0 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 561:
				rectAux.x = 1 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 562:
				rectAux.x = 2 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 563:
				rectAux.x = 3 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 564:
				rectAux.x = 4 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 565:
				rectAux.x = 5 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 566:
				rectAux.x = 6 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 567:
				rectAux.x = 7 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 568:
				rectAux.x = 8 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 569:
				rectAux.x = 9 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 570:
				rectAux.x = 10 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 571:
				rectAux.x = 11 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 572:
				rectAux.x = 12 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 573:
				rectAux.x = 13 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 574:
				rectAux.x = 14 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 575:
				rectAux.x = 15 * 122; rectAux.y = 10 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////// Lago SW
			case 580:
				rectAux.x = 0 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 581:
				rectAux.x = 1 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 582:
				rectAux.x = 2 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 583:
				rectAux.x = 3 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 584:
				rectAux.x = 4 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 585:
				rectAux.x = 5 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 586:
				rectAux.x = 6 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 587:
				rectAux.x = 7 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 588:
				rectAux.x = 8 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 589:
				rectAux.x = 9 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 590:
				rectAux.x = 10 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 591:
				rectAux.x = 11 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 592:
				rectAux.x = 12 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 593:
				rectAux.x = 13 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 594:
				rectAux.x = 14 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 595:
				rectAux.x = 15 * 122; rectAux.y = 6 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////////////// Lago Esquina NE
			case 600:
				rectAux.x = 0 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 601:
				rectAux.x = 1 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 602:
				rectAux.x = 2 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 603:
				rectAux.x = 3 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 604:
				rectAux.x = 4 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 605:
				rectAux.x = 5 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 606:
				rectAux.x = 6 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 607:
				rectAux.x = 7 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 608:
				rectAux.x = 8 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 609:
				rectAux.x = 9 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 610:
				rectAux.x = 10 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 611:
				rectAux.x = 11 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 612:
				rectAux.x = 12 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 613:
				rectAux.x = 13 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 614:
				rectAux.x = 14 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 615:
				rectAux.x = 15 * 122; rectAux.y = 4 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////////////////// Lago Esquina NW
			case 620:
				rectAux.x = 0 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 621:
				rectAux.x = 1 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 622:
				rectAux.x = 2 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 623:
				rectAux.x = 3 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 624:
				rectAux.x = 4 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 625:
				rectAux.x = 5 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 626:
				rectAux.x = 6 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 627:
				rectAux.x = 7 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 628:
				rectAux.x = 8 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 629:
				rectAux.x = 9 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 630:
				rectAux.x = 10 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 631:
				rectAux.x = 11 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 632:
				rectAux.x = 12 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 633:
				rectAux.x = 13 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 634:
				rectAux.x = 14 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 635:
				rectAux.x = 15 * 122; rectAux.y = 3 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////// Lago Esquina SE
			case 640:
				rectAux.x = 0 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 641:
				rectAux.x = 1 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 642:
				rectAux.x = 2 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 643:
				rectAux.x = 3 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 644:
				rectAux.x = 4 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 645:
				rectAux.x = 5 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 646:
				rectAux.x = 6 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 647:
				rectAux.x = 7 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 648:
				rectAux.x = 8 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 649:
				rectAux.x = 9 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 650:
				rectAux.x = 10 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 651:
				rectAux.x = 11 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 652:
				rectAux.x = 12 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 653:
				rectAux.x = 13 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 654:
				rectAux.x = 14 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 655:
				rectAux.x = 15 * 122; rectAux.y = 2 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////////////////////  Lago Esquina SW
			case 660:
				rectAux.x = 0 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 661:
				rectAux.x = 1 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 662:
				rectAux.x = 2 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 663:
				rectAux.x = 3 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 664:
				rectAux.x = 4 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 665:
				rectAux.x = 5 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 666:
				rectAux.x = 6 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 667:
				rectAux.x = 7 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 668:
				rectAux.x = 8 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 669:
				rectAux.x = 9 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 670:
				rectAux.x = 10 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 671:
				rectAux.x = 11 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 672:
				rectAux.x = 12 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 673:
				rectAux.x = 13 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 674:
				rectAux.x = 14 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 675:
				rectAux.x = 15 * 122; rectAux.y = 1 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////// Desnivel Full
			case 680:
				rectAux.x = 0 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 681:
				rectAux.x = 1 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 682:
				rectAux.x = 2 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 683:
				rectAux.x = 3 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 684:
				rectAux.x = 4 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 685:
				rectAux.x = 5 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 686:
				rectAux.x = 6 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 687:
				rectAux.x = 7 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 688:
				rectAux.x = 8 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 689:
				rectAux.x = 9 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 690:
				rectAux.x = 10 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 691:
				rectAux.x = 11 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 692:
				rectAux.x = 12 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 693:
				rectAux.x = 13 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 694:
				rectAux.x = 14 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 695:
				rectAux.x = 15 * 122; rectAux.y = 38 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////// Desnivel N
			case 700:
				rectAux.x = 0 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 701:
				rectAux.x = 1 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 702:
				rectAux.x = 2 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 703:
				rectAux.x = 3 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 704:
				rectAux.x = 4 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 705:
				rectAux.x = 5 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 706:
				rectAux.x = 6 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 707:
				rectAux.x = 7 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 708:
				rectAux.x = 8 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 709:
				rectAux.x = 9 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 710:
				rectAux.x = 10 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 711:
				rectAux.x = 11 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 712:
				rectAux.x = 12 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 713:
				rectAux.x = 13 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 714:
				rectAux.x = 14 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 715:
				rectAux.x = 15 * 122; rectAux.y = 40 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////// Desnivel Sur
			case 720:
				rectAux.x = 0 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 721:
				rectAux.x = 1 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 722:
				rectAux.x = 2 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 723:
				rectAux.x = 3 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 724:
				rectAux.x = 4 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 725:
				rectAux.x = 5 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 726:
				rectAux.x = 6 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 727:
				rectAux.x = 7 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 728:
				rectAux.x = 8 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 729:
				rectAux.x = 9 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 730:
				rectAux.x = 10 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 731:
				rectAux.x = 11 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 732:
				rectAux.x = 12 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 733:
				rectAux.x = 13 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 734:
				rectAux.x = 14 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 735:
				rectAux.x = 15 * 122; rectAux.y = 42 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////// Desnivel W
			case 740:
				rectAux.x = 0 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 741:
				rectAux.x = 1 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 742:
				rectAux.x = 2 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 743:
				rectAux.x = 3 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 744:
				rectAux.x = 4 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 745:
				rectAux.x = 5 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 746:
				rectAux.x = 6 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 747:
				rectAux.x = 7 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 748:
				rectAux.x = 8 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 749:
				rectAux.x = 9 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 750:
				rectAux.x = 10 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 751:
				rectAux.x = 11 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 752:
				rectAux.x = 12 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 753:
				rectAux.x = 13 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 754:
				rectAux.x = 14 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 755:
				rectAux.x = 15 * 122; rectAux.y = 39 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////// Desnivel E
			case 760:
				rectAux.x = 0 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 761:
				rectAux.x = 1 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 762:
				rectAux.x = 2 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 763:
				rectAux.x = 3 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 764:
				rectAux.x = 4 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 765:
				rectAux.x = 5 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 766:
				rectAux.x = 6 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 767:
				rectAux.x = 7 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 768:
				rectAux.x = 8 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 769:
				rectAux.x = 9 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 770:
				rectAux.x = 10 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 771:
				rectAux.x = 11 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 772:
				rectAux.x = 12 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 773:
				rectAux.x = 13 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 774:
				rectAux.x = 14 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 775:
				rectAux.x = 15 * 122; rectAux.y = 41 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////// Desnivel NE
			case 780:
				rectAux.x = 0 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 781:
				rectAux.x = 1 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 782:
				rectAux.x = 2 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 783:
				rectAux.x = 3 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 784:
				rectAux.x = 4 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 785:
				rectAux.x = 5 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 786:
				rectAux.x = 6 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 787:
				rectAux.x = 7 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 788:
				rectAux.x = 8 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 789:
				rectAux.x = 9 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 790:
				rectAux.x = 10 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 791:
				rectAux.x = 11 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 792:
				rectAux.x = 12 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 793:
				rectAux.x = 13 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 794:
				rectAux.x = 14 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 795:
				rectAux.x = 15 * 122; rectAux.y = 47 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////// Desnivel NW
			case 800:
				rectAux.x = 0 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 801:
				rectAux.x = 1 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 802:
				rectAux.x = 2 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 803:
				rectAux.x = 3 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 804:
				rectAux.x = 4 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 805:
				rectAux.x = 5 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 806:
				rectAux.x = 6 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 807:
				rectAux.x = 7 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 808:
				rectAux.x = 8 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 809:
				rectAux.x = 9 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 810:
				rectAux.x = 10 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 811:
				rectAux.x = 11 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 812:
				rectAux.x = 12 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 813:
				rectAux.x = 13 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 814:
				rectAux.x = 14 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 815:
				rectAux.x = 15 * 122; rectAux.y = 48 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////////////////// Desnivel SE
			case 820:
				rectAux.x = 0 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 821:
				rectAux.x = 1 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 822:
				rectAux.x = 2 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 823:
				rectAux.x = 3 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 824:
				rectAux.x = 4 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 825:
				rectAux.x = 5 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 826:
				rectAux.x = 6 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 827:
				rectAux.x = 7 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 828:
				rectAux.x = 8 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 829:
				rectAux.x = 9 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 830:
				rectAux.x = 10 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 831:
				rectAux.x = 11 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 832:
				rectAux.x = 12 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 833:
				rectAux.x = 13 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 834:
				rectAux.x = 14 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 835:
				rectAux.x = 15 * 122; rectAux.y = 49 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				///////////////////////////////////////////////////////////////////////////////////////////// Desnivel SW
			case 840:
				rectAux.x = 0 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 841:
				rectAux.x = 1 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 842:
				rectAux.x = 2 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 843:
				rectAux.x = 3 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 844:
				rectAux.x = 4 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 845:
				rectAux.x = 5 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 846:
				rectAux.x = 6 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 847:
				rectAux.x = 7 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 848:
				rectAux.x = 8 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 849:
				rectAux.x = 9 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 850:
				rectAux.x = 10 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 851:
				rectAux.x = 11 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 852:
				rectAux.x = 12 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 853:
				rectAux.x = 13 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 854:
				rectAux.x = 14 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 855:
				rectAux.x = 15 * 122; rectAux.y = 50 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				////////////////////////////////////////////////////////////////////////////////////// Desnivel WNE
			case 860:
				rectAux.x = 0 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 861:
				rectAux.x = 1 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 862:
				rectAux.x = 2 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 863:
				rectAux.x = 3 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 864:
				rectAux.x = 4 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 865:
				rectAux.x = 5 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 866:
				rectAux.x = 6 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 867:
				rectAux.x = 7 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 868:
				rectAux.x = 8 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 869:
				rectAux.x = 9 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 870:
				rectAux.x = 10 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 871:
				rectAux.x = 11 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 872:
				rectAux.x = 12 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 873:
				rectAux.x = 13 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 874:
				rectAux.x = 14 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 875:
				rectAux.x = 15 * 122; rectAux.y = 53 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				//////////////////////////////////////////////////////////////////////////////////////////// Desnivel WSE
			case 880:
				rectAux.x = 0 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 881:
				rectAux.x = 1 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 882:
				rectAux.x = 2 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 883:
				rectAux.x = 3 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 884:
				rectAux.x = 4 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 885:
				rectAux.x = 5 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 886:
				rectAux.x = 6 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 887:
				rectAux.x = 7 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 888:
				rectAux.x = 8 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 889:
				rectAux.x = 9 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 890:
				rectAux.x = 10 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 891:
				rectAux.x = 11 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 892:
				rectAux.x = 12 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 893:
				rectAux.x = 13 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 894:
				rectAux.x = 14 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 895:
				rectAux.x = 15 * 122; rectAux.y = 51 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Desnivel NWS
			case 900:
				rectAux.x = 0 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 901:
				rectAux.x = 1 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 902:
				rectAux.x = 2 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 903:
				rectAux.x = 3 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 904:
				rectAux.x = 4 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 905:
				rectAux.x = 5 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 906:
				rectAux.x = 6 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 907:
				rectAux.x = 7 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 908:
				rectAux.x = 8 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 909:
				rectAux.x = 9 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 910:
				rectAux.x = 10 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 911:
				rectAux.x = 11 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 912:
				rectAux.x = 12 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 913:
				rectAux.x = 13 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 914:
				rectAux.x = 14 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 915:
				rectAux.x = 15 * 122; rectAux.y = 54 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Desnivel NES
			case 920:
				rectAux.x = 0 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 921:
				rectAux.x = 1 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 922:
				rectAux.x = 2 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 923:
				rectAux.x = 3 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 924:
				rectAux.x = 4 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 925:
				rectAux.x = 5 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 926:
				rectAux.x = 6 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 927:
				rectAux.x = 7 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 928:
				rectAux.x = 8 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 929:
				rectAux.x = 9 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 930:
				rectAux.x = 10 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 931:
				rectAux.x = 11 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 932:
				rectAux.x = 12 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 933:
				rectAux.x = 13 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 934:
				rectAux.x = 14 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 935:
				rectAux.x = 15 * 122; rectAux.y = 52 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Desnivel NWSE
			case 940:
				rectAux.x = 0 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 941:
				rectAux.x = 1 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 942:
				rectAux.x = 2 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 943:
				rectAux.x = 3 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 944:
				rectAux.x = 4 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 945:
				rectAux.x = 5 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 946:
				rectAux.x = 6 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 947:
				rectAux.x = 7 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 948:
				rectAux.x = 8 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 949:
				rectAux.x = 9 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 950:
				rectAux.x = 10 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 951:
				rectAux.x = 11 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 952:
				rectAux.x = 12 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 953:
				rectAux.x = 13 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 954:
				rectAux.x = 14 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 955:
				rectAux.x = 15 * 122; rectAux.y = 55 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Desnivel bajada NS
			case 960:
				rectAux.x = 0 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 961:
				rectAux.x = 1 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 962:
				rectAux.x = 2 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 963:
				rectAux.x = 3 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 964:
				rectAux.x = 4 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 965:
				rectAux.x = 5 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 966:
				rectAux.x = 6 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 967:
				rectAux.x = 7 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 968:
				rectAux.x = 8 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 969:
				rectAux.x = 9 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 970:
				rectAux.x = 10 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 971:
				rectAux.x = 11 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 972:
				rectAux.x = 12 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 973:
				rectAux.x = 13 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 974:
				rectAux.x = 14 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 975:
				rectAux.x = 15 * 122; rectAux.y = 44 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Desnivel bajada WE
			case 980:
				rectAux.x = 0 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 981:
				rectAux.x = 1 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 982:
				rectAux.x = 2 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 983:
				rectAux.x = 3 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 984:
				rectAux.x = 4 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 985:
				rectAux.x = 5 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 986:
				rectAux.x = 6 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 987:
				rectAux.x = 7 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 988:
				rectAux.x = 8 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 989:
				rectAux.x = 9 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 990:
				rectAux.x = 10 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 991:
				rectAux.x = 11 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 992:
				rectAux.x = 12 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 993:
				rectAux.x = 13 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 994:
				rectAux.x = 14 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 995:
				rectAux.x = 15 * 122; rectAux.y = 43 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Desnivel Esquina NW
			case 1000:
				rectAux.x = 0 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1001:
				rectAux.x = 1 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1002:
				rectAux.x = 2 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1003:
				rectAux.x = 3 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1004:
				rectAux.x = 4 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1005:
				rectAux.x = 5 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1006:
				rectAux.x = 6 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1007:
				rectAux.x = 7 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1008:
				rectAux.x = 8 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1009:
				rectAux.x = 9 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1010:
				rectAux.x = 10 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1011:
				rectAux.x = 11 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1012:
				rectAux.x = 12 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1013:
				rectAux.x = 13 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1014:
				rectAux.x = 14 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1015:
				rectAux.x = 15 * 122; rectAux.y = 45 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Desnivel Cueva
			case 1020:
				rectAux.x = 0 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1021:
				rectAux.x = 1 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1022:
				rectAux.x = 2 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1023:
				rectAux.x = 3 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1024:
				rectAux.x = 4 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1025:
				rectAux.x = 5 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1026:
				rectAux.x = 6 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1027:
				rectAux.x = 7 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1028:
				rectAux.x = 8 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1029:
				rectAux.x = 9 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1030:
				rectAux.x = 10 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1031:
				rectAux.x = 11 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1032:
				rectAux.x = 12 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1033:
				rectAux.x = 13 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1034:
				rectAux.x = 14 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1035:
				rectAux.x = 15 * 122; rectAux.y = 46 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Camino NS
			case 1040:
				rectAux.x = 0 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1041:
				rectAux.x = 1 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1042:
				rectAux.x = 2 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1043:
				rectAux.x = 3 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1044:
				rectAux.x = 4 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1045:
				rectAux.x = 5 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1046:
				rectAux.x = 6 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1047:
				rectAux.x = 7 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1048:
				rectAux.x = 8 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1049:
				rectAux.x = 9 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1050:
				rectAux.x = 10 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1051:
				rectAux.x = 11 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1052:
				rectAux.x = 12 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1053:
				rectAux.x = 13 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1054:
				rectAux.x = 14 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1055:
				rectAux.x = 15 * 122; rectAux.y = 16 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Camino EW
			case 1060:
				rectAux.x = 0 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1061:
				rectAux.x = 1 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1062:
				rectAux.x = 2 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1063:
				rectAux.x = 3 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1064:
				rectAux.x = 4 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1065:
				rectAux.x = 5 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1066:
				rectAux.x = 6 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1067:
				rectAux.x = 7 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1068:
				rectAux.x = 8 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1069:
				rectAux.x = 9 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1070:
				rectAux.x = 10 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1071:
				rectAux.x = 11 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1072:
				rectAux.x = 12 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1073:
				rectAux.x = 13 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1074:
				rectAux.x = 14 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1075:
				rectAux.x = 15 * 122; rectAux.y = 15 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Camino Curva SE
			case 1080:
				rectAux.x = 0 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1081:
				rectAux.x = 1 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1082:
				rectAux.x = 2 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1083:
				rectAux.x = 3 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1084:
				rectAux.x = 4 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1085:
				rectAux.x = 5 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1086:
				rectAux.x = 6 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1087:
				rectAux.x = 7 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1088:
				rectAux.x = 8 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1089:
				rectAux.x = 9 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1090:
				rectAux.x = 10 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1091:
				rectAux.x = 11 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1092:
				rectAux.x = 12 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1093:
				rectAux.x = 13 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1094:
				rectAux.x = 14 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1095:
				rectAux.x = 15 * 122; rectAux.y = 17 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
				/////////////////////////////////////////////////////////////////////////////////////////// Camino Curva WN
			case 1100:
				rectAux.x = 0 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1101:
				rectAux.x = 1 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1102:
				rectAux.x = 2 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1103:
				rectAux.x = 3 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1104:
				rectAux.x = 4 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1105:
				rectAux.x = 5 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1106:
				rectAux.x = 6 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1107:
				rectAux.x = 7 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1108:
				rectAux.x = 8 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1109:
				rectAux.x = 9 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1110:
				rectAux.x = 10 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1111:
				rectAux.x = 11 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1112:
				rectAux.x = 12 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1113:
				rectAux.x = 13 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1114:
				rectAux.x = 14 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;
			case 1115:
				rectAux.x = 15 * 122; rectAux.y = 18 * 83;
				aux2.rectTileset = rectAux;
				aux2.x = x; aux2.y = y; aux2.capa = 1;
				x += 122;
				vecTile.push_back(aux2);
				break;

			case 999: y += 31; if (y == 0 || y % 62 == 0) x = 61; else x = 0;
				break;
			}

			f.get(aux);
		}
	}
	f.close();
}