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


void EstadoPG::cargaTile(char c, int i, int j, std::vector<TrianguloBorde>& mapa)
{
	//conveniente recibir un vector de char para codificar tambien las colisiones del seguimiento
	std::pair<int, int> tiles[16];
	int xAux, yAux, filaTile=1;
	xAux = j * 122*4;
	yAux = i * 31*4;
	if ( i % 2 != 0)  xAux += 61 * 4; yAux += 31 * 4;
	Tile aux;
	aux.capa = 1;
	aux.rectTileset.w = 122;
	aux.rectTileset.h = 83;

	Punto auxPunto;
	TrianguloBorde auxBorde;

	// Aqui definimos la posicion en la textura de los tiles que usaremos

	switch (c)
	{
	/////////////////////////////
	// TILES NIEVE
	////////////////////////////

	case 'Ũ': // NIEVE FULL
		filaTile = 21; ////////////////////////////////////////////SUSTITUIR POR LA FILA
		
		//Colocamos el tile grande usando los pequeños
		colocaTile(filaTile, xAux, yAux, aux);

		// Metemos a un vector de char si se puede traspasar el tile o no

		// Metemos los bordes al vector de bordes
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ų': // Nieve Rampa 1
		filaTile = 57;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ù': // Nieve Rampa 2
		filaTile = 58;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	/////////////////////////////
	// TILES LAGO
	////////////////////////////

	case 'ø': // Lago Full
		filaTile = 1;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ò': // Lago Orilla Norte
		filaTile = 14;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ó': // Lago Orilla Sur
		filaTile = 13;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ô': // Lago Orilla West
		filaTile = 12;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'õ': // Lago Orilla Este
		filaTile = 15;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ö': // Lago Orilla Norte-Este
		filaTile = 10;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ő': // Lago Orilla Norte-West
		filaTile = 6;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ç': // Lago Orilla Sur-Este
		filaTile = 11;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ȫ': // Lago Orilla Sur-West
		filaTile = 7;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '0': // Lago Esquina Norte-Este
		filaTile = 5;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '@': // Lago Esquina Norte-West
		filaTile = 4;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'δ': // Lago Esquina Sur-Este
		filaTile = 3;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'σ': // Lago Esquina Sur-West
		filaTile = 2;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	/////////////////////////////
	// TILES BOSQUE
	////////////////////////////

	case 'ª': // Bosque Full
		filaTile = 20;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ē': // Bosque North
		filaTile = 22;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'è': // Bosque South
		filaTile = 25;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '³': // Bosque West
		filaTile = 23;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'é': // Bosque East
		filaTile = 24;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '²': // Bosque North-East
		filaTile = 26;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '´': // Bosque North-West
		filaTile = 29;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ë': // Bosque South-East
		filaTile = 27;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '¹': // Bosque South-West
		filaTile = 28;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'È': // Bosque North-West-East
		filaTile = 31;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'É': // Bosque South-West-East
		filaTile = 33;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'Ê': // Bosque North-West-South
		filaTile = 30;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'Ë': // Bosque North-East-South
		filaTile = 32;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'þ': // Bosque North-West-South-East
		filaTile = 38;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'æ': // Bosque Esquina North-East
		filaTile = 36;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ß': // Bosque Esquina North-West
		filaTile = 35;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'º': // Bosque Esquina South-East
		filaTile = 37;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '¤': // Bosque Esquina South-West
		filaTile = 34;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	/////////////////////////////
	// TILES DESNIVEL
	////////////////////////////

	case 'i': // Desnivel FULL
		filaTile = 39;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;
	
	case '~': // Desnivel North
		filaTile = 41;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '}': // Desnivel South
		filaTile = 43;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ì': // Desnivel West
		filaTile = 40;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'í': // Desnivel East
		filaTile = 42;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '{': // Desnivel North-East
		filaTile = 48;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'î': // Desnivel North-West
		filaTile = 49;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ï': // Desnivel South-East
		filaTile = 50;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '|': // Desnivel South-West
		filaTile = 51;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ľ': // Desnivel West-North-East
		filaTile = 54;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '£': // Desnivel West-South-East
		filaTile = 52;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '¥': // Desnivel North-West-South
		filaTile = 55;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'Ĭ': // Desnivel North-East-South
		filaTile = 53;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '®': // Desnivel North-West-South-East
		filaTile = 56;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '±': // Desnivel Bajada North-South
		filaTile = 45;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '¶': // Desnivel Bajada West-East
		filaTile = 44;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case '»': // Desnivel Esquina North-West
		filaTile = 46;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'Ð': // Desnivel Esquina Cueva
		filaTile = 47;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;


	////////////////////////////
	// TILES Camino
	////////////////////////////

	case 'à': // Camino North-South
		filaTile = 17;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'á': // Camino East-West
		filaTile = 16;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'å': // Camino Curva Sourth-East
		filaTile = 18;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;

	case 'ă': // Camino Curva West-North
		filaTile = 19;
		colocaTile(filaTile, xAux, yAux, aux);
		meterBorde(auxPunto, xAux, yAux, auxBorde);
		break;


	/////////////////////////////
	// TILES PROTOTIPO
	////////////////////////////
	/*
	case 't':
		aux.rectTileset.x = 2 * 122;//1
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//2
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//3
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//4
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//6
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//7
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//10
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//11
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//12
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//13
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//14
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//15
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//16
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 62; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 122; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 93; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		
		break;
	/////////////////////////////////////////////////////////////////////////////////
	case 'y':
		aux.rectTileset.x = 5 * 122;//1
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//3
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//4
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//6
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//7
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//10
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//11
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//12
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//13
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//14
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//15
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//16
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 93; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 217; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 122; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'u':
		aux.rectTileset.x = 1 * 122;//1
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//3
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//4
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//6
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//7
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//10
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//11
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//12
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//13
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//14
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//15
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//16
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 31; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 186; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 248; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 93; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 186; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 248; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'i':
		aux.rectTileset.x = 0 * 122;//1
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//2
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//3
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//4
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//6
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//7
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//10
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//11
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//12
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//13
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//14
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//15
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//16
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 217; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 155; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 62; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 62; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'o':
		aux.rectTileset.x = 5 * 122;//1
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//3
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//4
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//6
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//7
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//10
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//11
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//12
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//13
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//14
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//15
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//16
		aux.rectTileset.y = 6 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 93; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 0; auxPunto.y = yAux + 124; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 217; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'a':
		aux.rectTileset.x = 1 * 122;//1
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//2
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//3
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//4
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//5
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//6
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//7
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//8
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//9
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//10
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//11
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//12
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//13
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//14
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//15
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//16
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 93; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 122; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 's':
		aux.rectTileset.x = 2 * 122;//1
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//2
		aux.rectTileset.y = 10 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//3
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//4
		aux.rectTileset.y = 10 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//5
		aux.rectTileset.y = 10 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//6
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//7
		aux.rectTileset.y = 11 * 83;
		aux.x = xAux + 0;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//8
		aux.rectTileset.y = 10 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//9
		aux.rectTileset.y = 10 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//10
		aux.rectTileset.y = 10 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//11
		aux.rectTileset.y = 11 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//12
		aux.rectTileset.y = 11 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//13
		aux.rectTileset.y = 10 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//14
		aux.rectTileset.y = 11 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//15
		aux.rectTileset.y = 11 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//16
		aux.rectTileset.y = 11 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 155; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 93; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 0; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 93; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 186; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 0; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'd':
		aux.rectTileset.x = 6 * 122;//1
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//2
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//3
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//4
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//5
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//6
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//7
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//8
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//9
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//10
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//11
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//12
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//13
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//14
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//15
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//16
		aux.rectTileset.y = 11 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 124; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 0; auxPunto.y = yAux + 124; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 124; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 0; auxPunto.y = yAux + 124; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'f':
		aux.rectTileset.x = 0 * 122;//1
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//3
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//4
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//5
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//6
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//7
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//8
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//9
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//10
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//11
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//12
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//13
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//14
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//15
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//16
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 122; auxPunto.y = yAux + 124; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 488; auxPunto.y = yAux + 124; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 122; auxPunto.y = yAux + 124; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 488; auxPunto.y = yAux + 124; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'g':
		aux.rectTileset.x = 4 * 122;//1
		aux.rectTileset.y = 14 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//2
		aux.rectTileset.y = 14 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//3
		aux.rectTileset.y = 14 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//4
		aux.rectTileset.y = 14 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 14 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//6
		aux.rectTileset.y = 14 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//7
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//8
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//9
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//10
		aux.rectTileset.y = 14 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//11
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//12
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//13
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//14
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//15
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//16
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 93; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 124; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 93; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 124; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'h':
		aux.rectTileset.x = 6 * 122;//1
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//2
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//3
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//4
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//5
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//6
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//7
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//8
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//9
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//10
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//11
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//12
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//13
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//14
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//15
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//16
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 217; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'j':
		aux.rectTileset.x = 0 * 122;//1
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//3
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//4
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//5
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//6
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//7
		aux.rectTileset.y = 12 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//8
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//9
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//10
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//11
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//12
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//13
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//14
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		aux.rectTileset.y = 9 * 83;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//15
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//16
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 31; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'k':
		aux.rectTileset.x = 1 * 122;//1
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//2
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//3
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//4
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//5
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//6
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//7
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//8
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//9
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//10
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//11
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//12
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//13
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//14
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//15
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//16
		aux.rectTileset.y = 13 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 93; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 217; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);

		break;
	case 'l':
		aux.rectTileset.x = 3 * 122;//1
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//2
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//3
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//4
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//5
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//6
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//7
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//8
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 9 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//10
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//11
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//12
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//13
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//14
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//15
		aux.rectTileset.y = 7 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//16
		aux.rectTileset.y = 8 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux; auxPunto.y = yAux + 124; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 488; auxPunto.y = yAux + 124; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 0; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux; auxPunto.y = yAux + 124; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 488; auxPunto.y = yAux + 124; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 248; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'z':
		aux.rectTileset.x = 3 * 122;//1
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//3
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//4
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//6
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//7
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//10
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//11
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//12
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//13
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//14
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//15
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//16
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
	
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'x':
		aux.rectTileset.x = 2 * 122;//1
		aux.rectTileset.y = 1 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//3
		aux.rectTileset.y = 1 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//4
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//5
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//6
		aux.rectTileset.y = 1 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//7
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//9
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//10
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//11
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//12
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//13
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//14
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//15
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//16
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 366; auxPunto.y = yAux+ 62; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 124; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 135; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'c':
		aux.rectTileset.x = 3 * 122;//1
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//2
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//3
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//4
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//5
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//6
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//7
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//8
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//9
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//10
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//11
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//12
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//13
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//14
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//15
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//16
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 62; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 122; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 93; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'v':
		aux.rectTileset.x = 2 * 122;//1
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//2
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//3
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//4
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//5
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//6
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//7
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//8
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 1 * 122;//9
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//10
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//11
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//12
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//13
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//14
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//15
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//16
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);


		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 93; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 217; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 122; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 31; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 366; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;
	case 'b':
		aux.rectTileset.x = 6 * 122;//1
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//2
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//3
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//4
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//5
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 2 * 122;//6
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//7
		aux.rectTileset.y = 3 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//8
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//9
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 3 * 122;//10
		aux.rectTileset.y = 4 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//11
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 4 * 122;//12
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//13
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//14
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 6 * 122;//15
		aux.rectTileset.y = 2 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 5 * 122;//16
		aux.rectTileset.y = 5 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);


		// Metemos a un vector de char si se puede traspasar el tile o no
		
		// Metemos los bordes al vector de bordes
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 305; auxPunto.y = yAux + 217; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 244; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 427; auxPunto.y = yAux + 155; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 62; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.A = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux + 62; auxBorde.B = auxPunto;
		auxPunto.x = xAux + 183; auxPunto.y = yAux; auxBorde.C = auxPunto;
		vectBordes.push_back(auxBorde);
		break;

	case 'n':
		aux.rectTileset.x = 0 * 122;//1
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//2
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//3
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 31;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//4
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//5
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//6
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 62;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//7
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//8
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//9
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//10
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 366;
		aux.y = yAux + 93;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//11
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 61;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//12
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//13
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 305;
		aux.y = yAux + 124;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//14
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 122;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//15
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 244;
		aux.y = yAux + 155;
		vecTile.push_back(aux);
		aux.rectTileset.x = 0 * 122;//16
		aux.rectTileset.y = 0 * 83;
		aux.x = xAux + 183;
		aux.y = yAux + 186;
		vecTile.push_back(aux);

		break;
		*/
	}

}

void EstadoPG::colocaTile(int & filaTile, int & xAux, int & yAux, Tile & aux ){
	//Posicion del Tile pequeño en el Tileset (16 tiles pequeños por cada Tile grande)
	aux.rectTileset.x = 1 * 122;//1
	aux.rectTileset.y = filaTile * 83;
	//Colocacion del primer tile pequeño
	aux.x = xAux + 183;
	aux.y = yAux;
	vecTile.push_back(aux);

	aux.rectTileset.x = 2 * 122;//2
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 122;
	aux.y = yAux + 31;
	vecTile.push_back(aux);

	aux.rectTileset.x = 3 * 122;//3
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 244;
	aux.y = yAux + 31;
	vecTile.push_back(aux);

	aux.rectTileset.x = 4 * 122;//4
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 61;
	aux.y = yAux + 62;
	vecTile.push_back(aux);

	aux.rectTileset.x = 5 * 122;//5
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 183;
	aux.y = yAux + 62;
	vecTile.push_back(aux);

	aux.rectTileset.x = 6 * 122;//6
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 305;
	aux.y = yAux + 62;
	vecTile.push_back(aux);

	aux.rectTileset.x = 7 * 122;//7
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux;
	aux.y = yAux + 93;
	vecTile.push_back(aux);

	aux.rectTileset.x = 8 * 122;//8
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 122;
	aux.y = yAux + 93;
	vecTile.push_back(aux);

	aux.rectTileset.x = 9 * 122;//9
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 244;
	aux.y = yAux + 93;
	vecTile.push_back(aux);

	aux.rectTileset.x = 10 * 122;//10
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 366;
	aux.y = yAux + 93;
	vecTile.push_back(aux);

	aux.rectTileset.x = 11 * 122;//11
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 61;
	aux.y = yAux + 124;
	vecTile.push_back(aux);

	aux.rectTileset.x = 12 * 122;//12
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 183;
	aux.y = yAux + 124;
	vecTile.push_back(aux);

	aux.rectTileset.x = 13 * 122;//13
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 305;
	aux.y = yAux + 124;
	vecTile.push_back(aux);

	aux.rectTileset.x = 14 * 122;//14
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 122;
	aux.y = yAux + 155;
	vecTile.push_back(aux);

	aux.rectTileset.x = 15 * 122;//15
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 244;
	aux.y = yAux + 155;
	vecTile.push_back(aux);

	aux.rectTileset.x = 3 * 122;//16
	aux.rectTileset.y = filaTile * 83;
	aux.x = xAux + 183;
	aux.y = yAux + 186;
	vecTile.push_back(aux);
}

void EstadoPG::meterBorde(Punto & auxPunto, int & xAux, int & yAux, TrianguloBorde & auxBorde){
	auxPunto.x = xAux + 244; auxPunto.y = yAux + 62; auxBorde.A = auxPunto;
	auxPunto.x = xAux + 61; auxPunto.y = yAux + 155; auxBorde.B = auxPunto;
	auxPunto.x = xAux + 122; auxPunto.y = yAux + 62; auxBorde.C = auxPunto;
	vectBordes.push_back(auxBorde);
	auxPunto.x = xAux + 183; auxPunto.y = yAux + 217; auxBorde.A = auxPunto;
	auxPunto.x = xAux + 427; auxPunto.y = yAux + 93; auxBorde.B = auxPunto;
	auxPunto.x = xAux + 366; auxPunto.y = yAux + 186; auxBorde.C = auxPunto;
	vectBordes.push_back(auxBorde);
}

void::EstadoPG::cargaMapa(std::string txt, std::vector<TrianguloBorde>& mapa){
	//mapa = new GrafoMapa();
	std::ifstream f; char aux = 'p';
	int ancho = 0;
	int alto = 0;
	f.open(txt, std::ios::in);
	f >> ancho;
	f >> alto;
	f.get(aux);
	for (size_t i = 0; i <= alto; i++)
	{
		for (size_t j = 0; j <= ancho; j++)
		{
			if (!f.eof()){
				f.get(aux);
				if (aux == '\n') f.get(aux);
				cargaTile(aux, i, j, mapa);
			}
		}
	}
	f.close();
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