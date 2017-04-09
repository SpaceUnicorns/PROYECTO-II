#pragma once
#include "micropather.h"
//#include "EstadoPG.h"
#include "ObjetoPG.h"


class GrafoMapa : public micropather::Graph
{
	std::vector<TrianguloBorde> mapa, mapaAux;
	std::vector<int> niveles;
	int aux, nivelAct;
	micropather::MicroPather* pather;
public:
	GrafoMapa()
	{
		niveles.push_back(0);
		nivelAct = aux = 0;
		pather = new micropather::MicroPather(this, 100);	// Use a very small memory block to stress the pather
	}

	void solve(void* startState, void* endState, std::vector< void* >* path, float* totalCost)
	{
		pather->Solve(startState, endState, path, totalCost);
	}

	void solve(int startX, int startY, int endX, int endY, std::vector<void*>* camino, float* totalCost)
	{

		void* startState, *endState;
		startState = XYToNode(startX, startY);
		endState = XYToNode(endX, endY);
		int x, y, xx, yy;
		pather->Solve(&startState, &endState, camino, totalCost);
	}

	void creaMapa(std::vector<TrianguloBorde>& c)
	{
		//niveles.resize(1);
		//niveles[0] = ancho*4;
		mapa = c;
		for (size_t i = 0; i < mapa.size(); i++)
		{
			mapaAux.push_back(mapa[i]);
		}
	}

	void actualizaMapa(std::vector<ObjetoJuego*> obj)
	{
		mapa.clear();
		for (int i = 0; i < mapaAux.size(); i++){
			mapa.push_back(mapaAux[i]);
		}
		for (ObjetoJuego* o : obj)
		{
			if (static_cast<ObjetoPG*>(o)->encuentraComponente("ColisionBox")){

				SDL_Rect rec = static_cast<ObjetoPG*>(o)->getAbsRect();
				int x, y;
				x = rec.x + rec.w*0.3;
				y = rec.y + rec.h*0.8;
				
				TrianguloBorde tr;
				tr.A.x = x; tr.A.y = y;
				tr.B.x = x + (rec.w*0.3); tr.B.y = y;
				tr.C.x = x + (rec.w*0.15); tr.C.y = y + (rec.h*0.2);

				//std::cout << y*niveles[0] + x << "\n";
				mapa.push_back(tr);
			}
		}
	}

	void NodeToXY(void* node, int* x, int* y)
	{
		Punto* index = (Punto*)node;
		*y = index->y;
		*x = index->x;
	}

	void* XYToNode(int x, int y)
	{
		Punto* node = new Punto();
		node->x = x;
		node->y = y;
		void* index = (void*)node;
		return index;
	}

	bool inTriangle(TrianguloBorde tr, Punto const & P){
		int x = triangleOrientation(tr);
		TrianguloBorde auxT;
		if (x >= 0){// Orientación positiva
			auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
			if (triangleOrientation(auxT) >= 0){
				auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
				if (triangleOrientation(auxT) >= 0){
					auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
					if (triangleOrientation(auxT) >= 0){
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;

		}
		else {//Orientación negativa
			auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
			if (triangleOrientation(auxT) < 0){
				auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
				if (triangleOrientation(auxT) < 0){
					auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
					if (triangleOrientation(auxT) < 0){
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
	}

	int triangleOrientation(TrianguloBorde const & tr){
		static TrianguloBorde s;
		return ((tr.A.x - tr.C.x)*(tr.B.y - tr.C.y) - (tr.A.y - tr.C.y)*(tr.B.x - tr.C.x));
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
		Punto p;
		p.x = x;
		p.y = y;
		bool col = false;
		int j = 0;
		std::cout << x << " " << y <<"\n";
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				p.y -= 62;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y ), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.1f };
				p.y += 62;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			case 1:
				p.y -= 31;
				p.x += 61;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.225f };
				p.y += 31;
				p.x -= 61;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			case 2:
				p.x += 122;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.15f };
				p.y -= 122;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			case 3:
				p.y += 31;
				p.x += 61;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.225f };
				p.y -= 31;
				p.x -= 61;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			case 4:
				p.y += 62;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.1f };
				p.y -= 62;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			case 5:
				p.y += 31;
				p.x -= 61;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.225f };
				p.y -= 31;
				p.x += 61;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			case 6:
				p.x -= 122;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.15f };
				p.x += 122;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			case 7:
				p.y -= 31;
				p.x -= 61;
				while (!col && j < mapa.size())
				{
					col = inTriangle(mapa[j], p);
					j++;
				}
				if (j != mapa.size())
					nodeCost = { XYToNode(p.x, p.y), 999 };
				else
					nodeCost = { XYToNode(p.x, p.y), 0.225f };
				p.y += 31;
				p.x += 61;
				col = false;
				j = 0;
				adjacent->push_back(nodeCost);
				break;
			}
		}
	}

	virtual bool IsThisTheEnd(void* state, void* endState)
	{
		Punto* aux = (Punto*)state;
		Punto* end = (Punto*)endState;

		SDL_Rect x;
		x.x = aux->x;
		x.y = aux->y;
		x.w = 122;
		x.h = 62;
		return aux->compruebaRadio(x, 69);
	}
	/**
	This function is only used in DEBUG mode - it dumps output to stdout. Since void*
	aren't really human readable, normally you print out some concise info (like "(1,2)")
	without an ending newline.
	*/
	virtual void  PrintStateInfo(void* state){}
};