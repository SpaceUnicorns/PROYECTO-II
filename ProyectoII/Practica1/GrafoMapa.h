#pragma once
#include "micropather.h"
#include "EstadoPG.h"

class GrafoMapa : public micropather::Graph
{
	std::vector<char> mapa;
	std::vector<int> niveles;
	int aux,nivelAct;
	micropather::MicroPather* pather;
public:
	GrafoMapa()
	{
		niveles.push_back(0);
		nivelAct = aux = 0;
		pather = new micropather::MicroPather(this, 20);	// Use a very small memory block to stress the pather
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
	void actualizaMapa(std::vector<ObjetoJuego*> obj)
	{
		for (ObjetoJuego* o : obj)
		{
			if (static_cast<ObjetoPG*>(o)->encuentraComponente("ColisionBox"));

			SDL_Rect rec = static_cast<ObjetoPG*>(o)->getColisionBox();
			int cuadarnteX = rec.x / 122;
			int cuadranteY = rec.y / 61;
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
		}
	}
	/**
	Return the least possible cost between 2 states. For example, if your pathfinding
	is based on distance, this is simply the straight distance between 2 points on the
	map. If you pathfinding is based on minimum time, it is the minimal travel time
	between 2 points given the best possible terrain.
	*/
	virtual float LeastCostEstimate(void* stateStart, void* stateEnd)
	{
		
	}

	/**
	Return the exact cost from the given state to all its neighboring states. This
	may be called multiple times, or cached by the solver. It *must* return the same
	exact values for every call to MicroPather::Solve(). It should generally be a simple,
	fast function with no callbacks into the pather.
	*/
	virtual void AdjacentCost(void* state, std::vector< micropather::StateCost > *adjacent){};

	/**
	This function is only used in DEBUG mode - it dumps output to stdout. Since void*
	aren't really human readable, normally you print out some concise info (like "(1,2)")
	without an ending newline.
	*/
	virtual void  PrintStateInfo(void* state){}
};