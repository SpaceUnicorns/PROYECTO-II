// Grupo VJ31, Álvaro Rodríguez-Peral Bustos
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>


void cambio(std::vector<std::vector<int>>& map, int i, int j, int primero)
{
}

int leeTile(std::vector<std::vector<int>>& map)
{
	std::cout << "Entra Lee Tile\n";
	char tile;
	std::cin >> tile;
	while (tile == 56 || tile < 0) std::cin >> tile;
	switch (tile)
	{
	case 'a': //Nieve Full
		return 1;
		break;
	case 'b': //Nieve Rampa 1
		return 20;
		break;
	case 'c': //Nieve Rampa 2
		return 40;
		break;
	case 'd': //Bosque Full
		return 60;
		break;
	case 'e':
		return 80;
		break;
	case 'f':
		return 100;
		break;
	case 'g':
		return 120;
		break;
	case 'h':
		return 140;
		break;
	case 'i':
		return 160;
		break;
	case 'j':
		return 180;
		break;
	case 'k':
		return 200;
		break;
	case 'l':
		return 220;
		break;
	case 'm':
		return 240;
		break;
	case 'n':
		return 260;
		break;
	case '5':
		return 280;
		break;
	case 'o':
		return 300;
		break;
	case 'p':
		return 320;
		break;
	case 'q':
		return 340;
		break;
	case 'r':
		return 360;
		break;
	case 's':
		return 380;
		break;
	case 't':
		return 400;
		break;
	case 'u':
		return 420;
		break;
	case 'v':
		return 440;
		break;
	case 'w':
		return 460;
		break;
	case 'x':
		return 480;
		break;
	case 'y':
		return 500;
		break;
	case 'z':
		return 520;
		break;
	case 'A':
		return 540;
		break;
	case 'B':
		return 560;
		break;
	case 'C':
		return 580;
		break;
	case 'D':
		return 600;
		break;
	case 'E':
		return 620;
		break;
	case 'F':
		return 640;
		break;
	case 'G':
		return 660;
		break;
	case 'H':
		return 680;
		break;
	case 'I':
		return 700;
		break;
	case 'J':
		return 720;
		break;
	case 'K':
		return 740;
		break;
	case 'L':
		return 760;
		break;
	case 'M':
		return 780;
		break;
	case 'N':
		return 800;
		break;
	case '6':
		return 820;
		break;
	case 'O':
		return 840;
		break;
	case 'P':
		return 860;
		break;
	case 'Q':
		return 880;
		break;
	case 'R':
		return 900;
		break;
	case 'S':
		return 920;
		break;
	case 'T':
		return 940;
		break;
	case 'U':
		return 960;
		break;
	case 'V':
		return 980;
		break;
	case 'W':
		return 1000;
		break;
	case 'X':
		return 1020;
		break;
	case 'Y':
		return 1040;
		break;
	case 'Z':
		return 1060;
		break;
	case '1':
		return 1080;
		break;
	case '2':
		return 1100;
		break;
	case '7':		// Cabaña con objetos
		return 1140;
		break;
	case '8':		// Cabaña vacía
		return 1160;
		break;
	case '9':		//Bosque Esq SW NE
		return 1180;
		break;
	case '0':		//Bosque Esq NW SE
		return 1200;
		break;
	}
	std::cout << "Sale Lee Tile\n";
}

void resolver(std::ofstream& f, std::vector<std::vector<int>>& map, int alto, int ancho)
{
	int itMatriz = 0;
	std::cout << "Entra Resolver\n";

	for (size_t i = 0; i < (alto/2); i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			for (size_t k = 0; k < ancho; k++)
			{
				switch (j)
				{
				case 0:
					if (k == 0)
						f << "0,0,";
					f << std::to_string(map[itMatriz][k]) + ",";
					if (itMatriz > 0)
					{
						f << std::to_string(map[itMatriz - 1][k] + 10) + ",";
						f << std::to_string(map[itMatriz - 1][k] + 11) + ",";
						f << std::to_string(map[itMatriz - 1][k] + 12) + ",";
					}
					else
					{
						f << "0,0,0,";
					}
					break;
				case 1:
					if (k == 0)
						f << "0,";
					f << std::to_string(map[itMatriz][k] + 1) + ",";
					f << std::to_string(map[itMatriz][k] + 2) + ",";
					if (itMatriz > 0)
					{
						f << std::to_string(map[itMatriz - 1][k] + 13) + ",";
						f << std::to_string(map[itMatriz - 1][k] + 14) + ",";
					}
					else
					{
						f << "0,0,";
					}
					if (k == ancho - 1)
						f << "0,";
					break;
				case 2:
					if (k == 0)
						f << "0,";
					f << std::to_string(map[itMatriz][k] + 3) + ",";
					f << std::to_string(map[itMatriz][k] + 4) + ",";
					f << std::to_string(map[itMatriz][k] + 5) + ",";
					if (itMatriz > 0)
					{
						f << std::to_string(map[itMatriz - 1][k] + 15) + ",";
					}
					else
					{
						f << "0,";
					}
					if (k == ancho - 1)
						f << "0,";
					break;
				case 3:
					f << std::to_string(map[itMatriz][k] + 6) + ",";
					f << std::to_string(map[itMatriz][k] + 7) + ",";
					f << std::to_string(map[itMatriz][k] + 8) + ",";
					f << std::to_string(map[itMatriz][k] + 9) + ",";
					if (k == ancho - 1)
						f << "0,0,";
					break;
				case 4:
					if (k == 0 )
						f << "0,";
					f << std::to_string(map[itMatriz][k] + 10) + ",";
					f << std::to_string(map[itMatriz][k] + 11) + ",";
					f << std::to_string(map[itMatriz][k] + 12) + ",";
					if (itMatriz < alto - 1)
					{
						f << std::to_string(map[itMatriz + 1][k]) + ",";
					}
					else
					{
						f << "0,";
					}
					if (k == ancho - 1)
						f << "0,";
					break;
				case 5:
					if (k == 0 )
						f << "0,";
					f << std::to_string(map[itMatriz][k] + 13) + ",";
					f << std::to_string(map[itMatriz][k] + 14) + ",";
					if (itMatriz < alto - 1)
					{
						f << std::to_string(map[itMatriz + 1][k] + 1) + ",";
						f << std::to_string(map[itMatriz + 1][k] + 2) + ",";
					}
					else
					{
						f << "0,0,";
					}
					if (k == ancho - 1)
						f << "0,";
					break;
				case 6:
					if (k == 0)
						f << "0,0,";
					f << std::to_string(map[itMatriz][k] + 15) + ",";
					if (i < alto-1)
					{
						f << std::to_string(map[itMatriz + 1][k] + 3) + ",";
						f << std::to_string(map[itMatriz + 1][k] + 4) + ",";
						f << std::to_string(map[itMatriz + 1][k] + 5) + ",";
					}
					else
					{
						f << "0,0,0,";
					}
					break;
				case 7:
					if (k == 0){
						f << "0,0,";
					}
					if (itMatriz < alto -1)
					{
						f << std::to_string(map[itMatriz + 1][k] + 6) + ",";
						f << std::to_string(map[itMatriz + 1][k] + 7) + ",";
						f << std::to_string(map[itMatriz + 1][k] + 8) + ",";
						f << std::to_string(map[itMatriz + 1][k] + 9) + ",";
					}
					else
					{
						f << "0,0,0,0,";
					}
					break;
				}
			}
			f << "999,\n";
		}
		itMatriz+=2;
	}
	std::cout << "Sale Resolver\n";
}


// El coste total del algoritmo es O(n) la clase polinomio recorre el vector y va sumando lo evaluado para cada monomio.
bool resuelveCaso(std::ofstream& f) {
	// leer los datos de la entrada
	int ancho, alto;
	std::cout << "ResuelveCaso\n";
	//ALTURA / ANCHURA TILES GRANDES
	alto = 1;
	ancho = 3;
	std::vector<int> aux(ancho);
	std::vector<std::vector<int>> mapa (alto);

	for (size_t i = 0; i < alto; i++)
	{
		mapa[i] = aux;
	}
	for (size_t i = 0; i < alto; i++)
	{
		for (size_t j = 0; j < ancho; j++)
		{
			mapa[i][j] = leeTile(mapa);
		}

	}

	resolver(f, mapa, alto, ancho);


	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("Problema18.txt");
	std::ofstream f;
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 
	f.open("salida.txt");
	resuelveCaso(f);
	f.close();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}