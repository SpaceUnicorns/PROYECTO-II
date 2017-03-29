#pragma once
#include "micropather.h"
//#include "EstadoPG.h"
#include "ObjetoPG.h"


class GrafoMapa : public micropather::Graph
{
	std::vector<char> mapa, mapaAux;
	std::vector<int> niveles;
	int aux, nivelAct;
	micropather::MicroPather* pather;
public:
	GrafoMapa()
	{
		niveles.push_back(0);
		nivelAct = aux = 0;
		pather = new micropather::MicroPather(this, 50);	// Use a very small memory block to stress the pather
	}

	void solve(void* startState, void* endState, std::vector< void* >* path, float* totalCost)
	{
		pather->Solve(startState, endState, path, totalCost);
	}

	void solve(int startX, int startY, int endX, int endY, std::vector<void*>* camino, float* totalCost)
	{

		void* startState, *endState;
		transformaCoord(startX, startY);
		transformaCoord(endX, endY);
		startState = XYToNode(startX, startY);
		endState = XYToNode(endX, endY);
		int x, y, xx, yy;
		NodeToXY(startState, &x, &y);
		NodeToXY(endState, &xx, &yy);
		pather->Solve(&startState, &endState, camino, totalCost);
		/*for (unsigned int i = 0; i < path.size(); i++)
		{
			NodeToXY(path[i], &x, &y);
			camino->push_back(std::make_pair(x, y));
		}*/
	}
	void creaMapa(char c)
	{
		switch (c)
		{
		case 's':
			mapa.push_back('s');
			mapaAux.push_back('s');
			aux++;
			break;
		case 't':
			mapa.push_back('t');
			mapaAux.push_back('t');
			aux++;
			break;
		case 'q':
			mapa.push_back('X');
			mapaAux.push_back('X');
			aux++;
			break;
		case 'w':
			mapa.push_back('X');
			mapaAux.push_back('X');
			aux++;
			break;
		case 'e':
			mapa.push_back('X');
			mapaAux.push_back('X');
			aux++;
			break;
		case 'r':
			mapa.push_back('X');
			mapaAux.push_back('X');
			aux++;
			break;
		case 'X':
			mapa.push_back('X');
			mapaAux.push_back('X');
			aux++;
			break;
		case 'L':
			niveles[nivelAct] = aux;
			niveles.push_back(0);
			nivelAct++;
			aux = 0;
			break;

		}
	}
	void transformaCoord(int& x, int& y)
	{
		int cuadranteX;
		int cuadranteY;
		if (y < 62) cuadranteY = 0;
		if (x < 123) cuadranteX = 0;
		cuadranteY = (y / 61) * 2;
		cuadranteX = x / 122;

		int Px, Py;
		Px = x - cuadranteX * 122;
		Py = y - cuadranteY * 31;

		/* ver la posicion del objeto, teniendo en cuenta el offset de la camara:
		x/122 == cuadrante de x en el que esta
		y/62  == cuadrante de y en el que esta
		hallado este cuadrante siguen existiendo cinco posible posiciones finales
		El centro del cuadrante o cualquiera de sus esquinas que pertenecerían a otro tile

		_____________
		|    / \    |
		|  /     \  |
		|  \     /  |
		|____\_/____|

		*/

		if (((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) >= 0) && ((122 - Px)*(0 - Py) - (31 - Py)*(61 - Px) >= 0) && ((61 - Px)*(31 - Py) - (0 - Py)*(0 - Px) >= 0)){
			x = cuadranteX; y = cuadranteY;
		}
		else if (((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) >= 0) && ((122 - Px)*(62 - Py) - (31 - Py)*(61 - Px) >= 0) && ((61 - Px)*(31 - Py) - (62 - Py)*(0 - Px) >= 0)){
			x = cuadranteX; y = cuadranteY;
		}
		// Si la posicion del objeto no esta en ninguno de los dos triangulos centrales comprobamo su x y su y con el centro del cuadrante
		// Si ambas son mayores marcamos la casilla inferior derecha y asi sucesivamente
		else
		{
			if (Px > 61)
			{
				if (Py < 31)
				{
					if (cuadranteY % 2 != 0 || cuadranteY == 0)	{ x = cuadranteX + 1; y = cuadranteY - 1; }
					else { x = cuadranteX + 1 ; y = cuadranteY - 1; }
				}
				else
				{
					if (cuadranteY % 2 != 0 || cuadranteY == 0)	{ x = cuadranteX + 1; y = cuadranteY + 1; }
					else { x = cuadranteX + 1; y = cuadranteY + 1; }
				}
			}
			else
			{
				if (Py < 31)
				{
					if (cuadranteY % 2 != 0 || cuadranteY == 0)	{ x = cuadranteX; y = cuadranteY - 1; }
					else { x = cuadranteX; y = cuadranteY - 1; }
				}
				else
				{
					if (cuadranteY % 2 != 0 || cuadranteY == 0)	{ x = cuadranteX; y = cuadranteY + 1; }
					else { x = cuadranteX; y = cuadranteY + 1; }
				}
			}
		}
		y++;
		x--;
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x >= niveles[0]) x = niveles[0]-1;
		if (y >= niveles.size()) y = niveles.size()-1;
		



	}
	void actualizaMapa(std::vector<ObjetoJuego*> obj)
	{
		for (int i = 0; i < mapa.size(); i++){
			mapa[i] = mapaAux[i];
		}
		for (ObjetoJuego* o : obj)
		{
			if (static_cast<ObjetoPG*>(o)->encuentraComponente("ColisionBox")){

				SDL_Rect rec = static_cast<ObjetoPG*>(o)->getAbsRect();
				int x, y;
				x = rec.x + rec.w*0.5;
				y = rec.y + rec.h*0.8;
				transformaCoord(x,y);

				std::cout << y*niveles[0] + x << "\n";
				mapa[y*niveles[0] + x] = 'X';
			}
		}
	}

	void NodeToXY(void* node, int* x, int* y)
	{
		intptr_t index = (intptr_t)node;
		*y = index / niveles[0];
		*x = index - *y * niveles[0];
	}

	void* XYToNode(int x, int y)
	{
		return (void*)(y*niveles[0] + x);
	}

	/**
	Return the least possible cost between 2 states. For example, if your pathfinding
	is based on distance, this is simply the straight distance between 2 points on the
	map. If you pathfinding is based on minimum time, it is the minimal travel time
	between 2 points given the best possible terrain.
	*/
	virtual float LeastCostEstimate(void* stateStart, void* stateEnd)
	{
		int firstX, firstY, lastX, lastY;
		NodeToXY(stateStart, &firstX, &firstY);
		NodeToXY(stateEnd, &lastX, &lastY);

		int dx = abs(firstX - lastX);
		int dy = abs(firstY - lastY);
		return (float)sqrt((double)(dx*dx) + (double)(dy*dy));
	}

	/**
	Return the exact cost from the given state to all its neighboring states. This
	may be called multiple times, or cached by the solver. It *must* return the same
	exact values for every call to MicroPather::Solve(). It should generally be a simple,
	fast function with no callbacks into the pather.
	*/
	virtual void AdjacentCost(void* state, std::vector< micropather::StateCost > *adjacent)
	{
		micropather::StateCost nodeCost;
		int x, y;
		NodeToXY(state, &x, &y);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				if (y > 1){
					if (mapa[(y -2)*niveles[0] + x] == 'X')
						nodeCost = { XYToNode(x, y - 2), 999 };
					else
						nodeCost = { XYToNode(x, y - 2), 0.1f };
					adjacent->push_back(nodeCost);
				}
				break;
			case 1:
				if (y > 0 && x < niveles[0] - 1){
					if (y % 2 != 0 || y == 0){
						if (mapa[(y - 1)*niveles[0] + x + 1] == 'X')
							nodeCost = { XYToNode(x + 1, y - 1), 999 };
						else
							nodeCost = { XYToNode(x + 1, y - 1), 0.1f };
						adjacent->push_back(nodeCost);
					}
					else {
						if (y > 0){
							if (mapa[(y - 1)*niveles[0] + x] == 'X')
								nodeCost = { XYToNode(x, y - 1), 999 };
							else
								nodeCost = { XYToNode(x, y - 1), 0.1f };
						adjacent->push_back(nodeCost);
						}
					}
				}
				break;
			case 2:
				if (x < niveles[0] - 1){
					if (mapa[(y)*niveles[0] + x + 1] == 'X')
						nodeCost = { XYToNode(x + 1, y), 999 };
					else
						nodeCost = { XYToNode(x + 1, y), 0.1f };
					adjacent->push_back(nodeCost);
				}
				break;
			case 3:
				if (y < niveles.size() - 1 && x < niveles[0] - 1){
					if (y % 2 != 0 || y == 0){
						if (mapa[(y + 1)*niveles[0] + x + 1] == 'X')
							nodeCost = { XYToNode(x + 1, y + 1), 999 };
						else
							nodeCost = { XYToNode(x + 1, y + 1), 0.1f };
						adjacent->push_back(nodeCost);
					}
					else{
						if (y < niveles.size() - 1){
							if (mapa[(y + 1)*niveles[0] + x] == 'X')
								nodeCost = { XYToNode(x, y + 1), 999 };
							else
								nodeCost = { XYToNode(x, y + 1), 0.1f };
							adjacent->push_back(nodeCost);
						}
					}
				}
				break;
			case 4:
				if (y < niveles.size() - 3){
					if (mapa[(y + 2)*niveles[0] + x] == 'X')
						nodeCost = { XYToNode(x, y + 2), 999 };
					else
						nodeCost = { XYToNode(x, y + 2), 0.1f };
					adjacent->push_back(nodeCost);
				}
				break;
			case 5:
				if (y < niveles.size() - 1){
					if (y % 2 != 0 || y == 0){
						if (mapa[(y + 1)*niveles[0] + x] == 'X')
							nodeCost = { XYToNode(x, y + 1), 999 };
						else
							nodeCost = { XYToNode(x, y + 1), 0.1f };
						adjacent->push_back(nodeCost);
					}
					else {
						if (y < niveles.size() - 1 && x > 0){
							if (mapa[(y + 1)*niveles[0] + x] == 'X')
								nodeCost = { XYToNode(x - 1, y + 1), 999 };
							else
								nodeCost = { XYToNode(x - 1, y + 1), 0.1f };
							adjacent->push_back(nodeCost);
						}
					}
				}
				break;
			case 6:
				if (x > 0){
					if (mapa[(y)*niveles[0] + x - 1] == 'X')
						nodeCost = { XYToNode(x - 1, y), 999 };
					else
						nodeCost = { XYToNode(x - 1, y), 0.1f };
					adjacent->push_back(nodeCost);
				}
				break;
			case 7:
				if (y > 0){
					if (y % 2 != 0 || y == 0){
						if (mapa[(y - 1)*niveles[0] + x] == 'X')
							nodeCost = { XYToNode(x, y - 1), 999 };
						else
							nodeCost = { XYToNode(x, y - 1), 0.1f };
						adjacent->push_back(nodeCost);
					}
					else{
						if (y > 0 && x > 0){
							if (mapa[(y - 1)*niveles[0] + x - 1] == 'X')
								nodeCost = { XYToNode(x - 1, y - 1), 999 };
							else
								nodeCost = { XYToNode(x - 1, y - 1), 0.1f };
							adjacent->push_back(nodeCost);
						}
					}
				}
				break;
			}
		}
	}
	/**
	This function is only used in DEBUG mode - it dumps output to stdout. Since void*
	aren't really human readable, normally you print out some concise info (like "(1,2)")
	without an ending newline.
	*/
	virtual void  PrintStateInfo(void* state){}
};