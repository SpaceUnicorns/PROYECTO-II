#pragma once
#include "micropather.h"
//#include "EstadoPG.h"
#include "ObjetoPG.h"


class GrafoMapa : public micropather::Graph
{
	std::vector<char> mapa;
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
		std::cout << "llego aqui\n";
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
			aux++;
			break;
		case 't':
			mapa.push_back('t');
			aux++;
			break;
		case 'X':
			mapa.push_back('X');
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
	/*	int cuadranteX;
		int cuadranteY = y / 31;
		if (cuadranteY % 2 == 0)
			cuadranteX = x / 61;
		else 
			cuadranteX = (x + 61) / 61;

		int Px, Py;
		Px = x - cuadranteX * 61;
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

	/*	if (((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) < 0) && ((122 - Px)*(0 - Py) - (31 - Py)*(61 - Px) < 0) && ((61 - Px)*(31 - Py) - (0 - Py)*(0 - Px) < 0)){
			x = cuadranteX; y = cuadranteY;
		}
		else if (((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) < 0) && ((122 - Px)*(62 - Py) - (31 - Py)*(61 - Px) < 0) && ((61 - Px)*(31 - Py) - (62 - Py)*(0 - Px) < 0)){
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
					x = cuadranteX + 1; y = cuadranteY - 1;
				}
				else
				{
					x = cuadranteX + 1; y = cuadranteY + 1;
				}
			}
			else
			{
				if (Py < 31)
				{
					x = cuadranteX - 1; y = cuadranteY - 1;
				}
				else
				{
					x = cuadranteX - 1; y = cuadranteY + 1;
				}
			}
		}
		*/
		y = y / 31;
		if (y % 2 != 0 || y == 0)x += 61;
 		x = x / 122;
		x -= 3;
		y += 3;

	}
	void actualizaMapa(std::vector<ObjetoJuego*> obj)
	{
		for (ObjetoJuego* o : obj)
		{
			if (static_cast<ObjetoPG*>(o)->encuentraComponente("ColisionBox")){

				SDL_Rect rec = static_cast<ObjetoPG*>(o)->getColisionBox();
				int cuadranteX = rec.x / 122;
				int cuadranteY = rec.y / 31;
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
				int Px, Py;
				Px = rec.x - cuadranteX * 122;
				Py = rec.y - cuadranteY * 62;
				// Dividimos el cudrante como si fueran 6 triangulos por comodidad si esta en alguno de los dos centrales añadimos una X al mapa en la posicion del cuadrante
				if (((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) < 0) && ((122 - Px)*(0 - Py) - (31 - Py)*(61 - Px) < 0) && ((61 - Px)*(31 - Py) - (0 - Py)*(0 - Px) < 0)){
					int aux1 = 0;
					for (int i = 0; i < cuadranteY; i++)
					{
						aux1 += niveles[i];
					}
					mapa[aux1 + cuadranteX] = 'X';
				}
				else if (((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) < 0) && ((122 - Px)*(62 - Py) - (31 - Py)*(61 - Px) < 0) && ((61 - Px)*(31 - Py) - (62 - Py)*(0 - Px) < 0)){
					int aux1 = 0;
					for (int i = 0; i < cuadranteY; i++)
					{
						aux1 += niveles[i];
					}
					mapa[aux1 + cuadranteX] = 'X';
				}
				// Si la posicion del objeto no esta en ninguno de los dos triangulos centrales comprobamo su x y su y con el centro del cuadrante
				// Si ambas son mayores marcamos la casilla inferior derecha y asi sucesivamente
				else
				{
					int aux1 = 0;
					if (Px >= 61)
					{
						if (Py < 31)
						{
							for (int i = 0; i < cuadranteY - 1; i++)
							{
								aux1 += niveles[i];
							}
							mapa[aux1 + cuadranteX + 1] = 'X';
						}
						else
						{
							for (int i = 0; i < cuadranteY + 1; i++)
							{
								aux1 += niveles[i];
							}
							mapa[aux1 + cuadranteX + 1] = 'X';
						}
					}
					else
					{
						if (Py < 31)
						{
							for (int i = 0; i < cuadranteY - 1; i++)
							{
								aux1 += niveles[i];
							}
							mapa[aux1 + cuadranteX - 1] = 'X';
						}
						else
						{
							for (int i = 0; i < cuadranteY + 1; i++)
							{
								aux1 += niveles[i];
							}
							mapa[aux1 + cuadranteX - 1] = 'X';
						}
					}
				}
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

		std::cout << x << " " << y << "\n";
		if (x == 4 && y == 0)
			std::cout << x << " " << y << "\n";
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 4:
				if (y > 1){
					if (mapa[(y -2)*niveles[0] + x] == 'X')
						nodeCost = { XYToNode(x, y - 2), 1 };
					else
						nodeCost = { XYToNode(x, y - 2), 0.1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 3:
				if (y % 2 != 0 || y == 0){
					if (y > 0 && x < niveles[0] - 1){
						if (mapa[(y - 1)*niveles[0] + x + 1] == 'X')
							nodeCost = { XYToNode(x + 1, y + 1), 1 };
						else
							nodeCost = { XYToNode(x + 1, y + 1), 0.14 };
						adjacent->push_back(nodeCost);
					}
					else {
						if (y > 0){
							if (mapa[(y - 1)*niveles[0] + x] == 'X')
								nodeCost = { XYToNode(x, y - 1), 1 };
							else
								nodeCost = { XYToNode(x, y - 1), 0.14 };
						adjacent->push_back(nodeCost);
						}
					}
				}
				break;
			case 6:
				if (x < niveles[0] - 1){
					if (mapa[(y)*niveles[0] + x + 1] == 'X')
						nodeCost = { XYToNode(x + 1, y), 1 };
					else
						nodeCost = { XYToNode(x + 1, y), 0.1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 1:
				if (y % 2 != 0 || y == 0){
					if (y < niveles.size() - 1 && x < niveles[0] - 1){
						if (mapa[(y + 1)*niveles[0] + x + 1] == 'X')
							nodeCost = { XYToNode(x + 1, y + 1), 1 };
						else
							nodeCost = { XYToNode(x + 1, y + 1), 0.14 };
						adjacent->push_back(nodeCost);
					}
					else{
						if (y < niveles.size() - 1){
							if (mapa[(y + 1)*niveles[0] + x] == 'X')
								nodeCost = { XYToNode(x, y + 1), 1 };
							else
								nodeCost = { XYToNode(x, y + 1), 0.14 };
							adjacent->push_back(nodeCost);
						}
					}
				}
				break;
			case 0:
				if (y < niveles.size() - 3){
					if (mapa[(y + 2)*niveles[0] + x] == 'X')
						nodeCost = { XYToNode(x, y + 2), 1 };
					else
						nodeCost = { XYToNode(x, y + 2), 0.1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 7:
				if (y % 2 != 0 || y == 0){
					if (y < niveles.size() - 1){
						if (mapa[(y + 1)*niveles[0] + x] == 'X')
							nodeCost = { XYToNode(x, y + 1), 1 };
						else
							nodeCost = { XYToNode(x, y + 1), 0.14 };
						adjacent->push_back(nodeCost);
					}
					else {
						if (y < niveles.size() - 1 && x > 0){
							if (mapa[(y + 1)*niveles[0] + x] == 'X')
								nodeCost = { XYToNode(x - 1, y + 1), 1 };
							else
								nodeCost = { XYToNode(x - 1, y + 1), 0.14 };
							adjacent->push_back(nodeCost);
						}
					}
				}
				break;
			case 2:
				if (x > 0){
					if (mapa[(y)*niveles[0] + x - 1] == 'X')
						nodeCost = { XYToNode(x - 1, y), 1 };
					else
						nodeCost = { XYToNode(x - 1, y), 0.1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 5:
				if (y % 2 != 0 || y == 0){
					if (y > 0){
						if (mapa[(y - 1)*niveles[0] + x] == 'X')
							nodeCost = { XYToNode(x, y - 1), 1 };
						else
							nodeCost = { XYToNode(x, y - 1), 0.14 };
						adjacent->push_back(nodeCost);
					}
					else{
						if (y > 0 && x > 0){
							if (mapa[(y - 1)*niveles[0] + x - 1] == 'X')
								nodeCost = { XYToNode(x - 1, y - 1), 1 };
							else
								nodeCost = { XYToNode(x - 1, y - 1), 0.14 };
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