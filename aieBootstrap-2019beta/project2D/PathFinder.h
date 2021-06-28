#pragma once
#include <Vector>
#include "GraphNode.h"
#include "Renderer2D.h"
#include "Heap.h"

#define GRID_SIZE 50

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	bool AStarPath(Vector2 _start, Vector2 _end, std::vector<Vector2>& _finalPath);
	bool CalculateDijkstraPath(Vector2 _start, Vector2 _end, std::vector<Vector2>& _finalPath);
	GraphNode* GetNodeByPos(Vector2 _pos);
	void Render(aie::Renderer2D* _renderer);

private:
	GraphNode* GetNeighbour(int _currentX, int _currentY, int _neighbour);

	GraphNode* m_Nodes[GRID_SIZE][GRID_SIZE];

	int GetHeuristic(GraphNode* neighbour, GraphNode* _end);
	Heap m_OpenListHeap;
	bool m_ClosedList[GRID_SIZE][GRID_SIZE];
};
