#include "EstadoPG.h"
#include "Error.h"


EstadoPG::EstadoPG(juegoPG*jug,int puntos)
{
	pJuego = jug;
	fondo.h = 480;
	fondo.w = 640;
	fondo.x = fondo.y = 0;
	colorFuente.r = 130;
	colorFuente.g = 214;
	colorFuente.b = 28;
	contPuntos = puntos;
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
	pJuego->system->createSound(/*reverb en impulsos path*/"", FMOD_DEFAULT | FMOD_OPENONLY, NULL, &irSound);

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
	
	/*
	Creamos el envio a la reverb
	*/
	cfx1->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
	reverbUnit->addInput(channelHead, &reverbConnectionfx1, FMOD_DSPCONNECTION_TYPE_SEND);
	cfx1->setPaused(false);
	reverbConnectionfx1->setMix(0.10);

	cfx2->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
	reverbUnit->addInput(channelHead, &reverbConnectionfx2, FMOD_DSPCONNECTION_TYPE_SEND);
	cfx2->setPaused(false);
	reverbConnectionfx2->setMix(0.10);

	cfx3->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
	reverbUnit->addInput(channelHead, &reverbConnectionfx3, FMOD_DSPCONNECTION_TYPE_SEND);
	cfx3->setPaused(false);
	reverbConnectionfx3->setMix(0.10);

	cfx4->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
	reverbUnit->addInput(channelHead, &reverbConnectionfx4, FMOD_DSPCONNECTION_TYPE_SEND);
	cfx4->setPaused(false);
	reverbConnectionfx4->setMix(0.10);

	camb1->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
	reverbUnit->addInput(channelHead, &reverbConnectionamb1, FMOD_DSPCONNECTION_TYPE_SEND);
	camb1->setPaused(false);
	reverbConnectionamb1->setMix(0.10);

	camb2->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
	reverbUnit->addInput(channelHead, &reverbConnectionamb2, FMOD_DSPCONNECTION_TYPE_SEND);
	camb2->setPaused(false);
	reverbConnectionamb2->setMix(0.10);
}


EstadoPG::~EstadoPG()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}
void EstadoPG::reproduceFx(std::string fx, int x, int y, float wet){
	FMOD_VECTOR pos = { x , y, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };


	try { 
		bool *cOcupied;
		cfx1->isPlaying(cOcupied);
		if (&cOcupied == false){
			cfx1->set3DAttributes(&pos, &vel);
			pJuego->system->playSound(vfx.at(fx), 0, true, &cfx1);

		}
		else {
			cfx2->isPlaying(cOcupied);
			if (&cOcupied == false){
				cfx2->set3DAttributes(&pos, &vel);
				pJuego->system->playSound(vfx.at(fx), 0, true, &cfx2);
			}
			else{
				cfx3->isPlaying(cOcupied);
				if (&cOcupied == false){
					cfx3->set3DAttributes(&pos, &vel);
					pJuego->system->playSound(vfx.at(fx), 0, true, &cfx3);
				}
				else {
					cfx4->isPlaying(cOcupied);
					cfx4->set3DAttributes(&pos, &vel);
					if (&cOcupied == false){
						pJuego->system->playSound(vfx.at(fx), 0, true, &cfx1);
					}
					else {
						cfx4->stop();
						pJuego->system->playSound(vfx.at(fx), 0, true, &cfx1);
					}
				}
			}
		}
	}
	catch (std::exception e){}
}
void EstadoPG::reproduceMusica(std::string music, bool fade){
	try {
		bool *cOcupied;
		cmusic1->isPlaying(cOcupied);
		if (&cOcupied){
			pJuego->system->playSound(vmusic.at(music), 0, true, &cmusic2);
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
			pJuego->system->playSound(vmusic.at(music), 0, true, &cmusic1);
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
	catch (std::exception e){}
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
		bool *cOcupied;
		camb1->isPlaying(cOcupied);
		if (&cOcupied){
			pJuego->system->playSound(vmusic.at(amb), 0, true, &camb2);
			vmusic.at(amb)->setMode(FMOD_LOOP_NORMAL);
			if (fade){
				unsigned long long parentclock;
				camb2->getDSPClock(NULL, &parentclock);
				camb2->addFadePoint(parentclock, 0.0f);
				camb2->addFadePoint(parentclock + 4096, 1.0f);
			}
			cAmb = 2;
		}

		else{
			pJuego->system->playSound(vmusic.at(amb), 0, true, &camb1);
			vmusic.at(amb)->setMode(FMOD_LOOP_NORMAL);
			if (fade){
				unsigned long long parentclock;
				camb1->getDSPClock(NULL, &parentclock);
				camb1->addFadePoint(parentclock, 0.0f);
				camb1->addFadePoint(parentclock + 4096, 1.0f);
			}
			cAmb = 1;
		}
	}
	catch (std::exception e){}
}
void EstadoPG::paraAmb(std::string amb, bool fade){
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


void EstadoPG::draw(){
	//Draw background
	pJuego->getTextura(et)->draw(pJuego->getRender(), fondo);
	drawFont();

	for (unsigned int i = 0; i < vecObj.size(); i++)
		vecObj[i]->draw();


}
void EstadoPG::drawFont(){
	//Dibujar puntos
	try{// bloque try catch
			pJuego->getFuente()->loadFromText(pJuego->getRender(), std::to_string(contPuntos), colorFuente);
			pJuego->getFuente()->draw(pJuego->getRender(), pJuego->getFuente()->font.recFont);
		}
		catch (ELoadFont & e){}
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