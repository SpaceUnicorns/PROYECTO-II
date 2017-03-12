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
	colorFuente.r = 130;
	colorFuente.g = 214;
	colorFuente.b = 28;
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
			pJuego->system->playSound(vmusic.at(music), mainGroup, false, &cmusic2);
			vmusic.at(music)->setMode(FMOD_LOOP_NORMAL);
			if (fade){
				unsigned long long parentclock;
				cmusic2->getDSPClock(NULL, &parentclock);
				cmusic2->addFadePoint(parentclock, 0.0f);
				cmusic2->addFadePoint(parentclock + 4096, 1.0f);
			}
			cMusic = 2;
		}

		else{
			pJuego->system->playSound(vmusic.at(music), mainGroup, false, &cmusic1);
			vmusic.at(music)->setMode(FMOD_LOOP_NORMAL);
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
	drawFont();

	for (unsigned int i = 0; i < vecObj.size(); i++)
		vecObj[i]->draw();


}
void EstadoPG::drawFont(){
	//Dibujar puntos
	//try{// bloque try catch
			pJuego->getFuente()->loadFromText(pJuego->getRender(), std::to_string(contPuntos), colorFuente);
			pJuego->getFuente()->draw(pJuego->getRender(), pJuego->getFuente()->font.recFont);
	//	}
		//catch (ELoadFont & e){}
	}

void EstadoPG::update(){
	for (unsigned int i = 0; i < vecObj.size(); i++){
		vecObj[i]->update();
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