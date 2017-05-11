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
	case '3':		// Tile Vacio
		return 1220;
		break;
	case '4':
		return 1120;// Desn Esq Inv NW
		break;
	case '7':		// Cabaña con objetos
		return 1140;
		break;
	case '8':		// Cabaña vacía
		return 1160;
		break;
	case '9':		// Bosque Esq SW NE
		return 1180;
		break;
	case '0':		// Bosque Esq NW SE
		return 1200;
		break;
	case 'ª':		// Cueva Suelo Full (65)
		return 1240;
		break;
	case '+':		// Cueva Suelo N (66)
		return 1260;
		break;
	case 'Ç':		// Cueva Suelo S (67)
		return 1280;
		break;
	case '-':		// Cueva Suelo E (68)
		return 1300;
		break;
	case '.':		// Cueva Suelo w (69)
		return 1320;
		break;
	case ',':		// Cueva Suelo SE (70)
		return 1340;
		break;
	case '!':		// Cueva Suelo SW (71)
		return 1360;
		break;
	case '¡':		// Cueva Suelo SN (72)
		return 1380;
		break;
	case '¿':		// Cueva Suelo NW (73)
		return 1400;
		break;
	case '<':		// Cueva WSE (75)
		return 1440;
		break;
	case '#':		// Cueva Bajada NW (76)
		return 1460;
		break;
	case '$':		// Cueva Pilar NE (77)
		return 1480;
		break;
	case '%':		// Cueva Pilar SW (78)
		return 1500;
		break;
	case '&':		// Cueva Esquina Techo SW (79)
		return 1520;
		break;
	case '*':		// Cueva Esq Techo NE (80)
		return 1540;
		break;
	case '>':		// Cueva Esq T NE S SW (81)
		return 1560;
		break;
	case '/':		// Cueva Esq T SW NE (82)
		return 1580;
		break;
	case '(':		// Cueva Esq Suelo NW (83)
		return 1600;
		break;
	case ')':		// Cueva Esq Suelo NE (84)
		return 1620;
		break;
	case ':':		// Cueva Esq Suelo SW (85)
		return 1640;
		break;
	case ';':		// Cueva Techo S (86)
		return 1660;
		break;
	case '[':		// Cueva Techo N (87)
		return 1680;
		break;
	case ']':		// Cueva Techo W (88)
		return 1700;
		break;
	case '{':		// Cueva Techo SW (89)
		return 1720;
		break;
	case '}':		// Cueva Techo NE (90)
		return 1740;
		break;
	case '@':		// Cueva Techo FULL (91)
		return 1760;
		break;
	case '|':		// Rampa Alvaro (92)
		return 1780;
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
	alto = 10;
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