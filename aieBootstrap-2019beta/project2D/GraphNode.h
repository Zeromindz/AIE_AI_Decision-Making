#pragma once
#include "Vector2.h"

#define NEIGHBOUR_COUNT 8

class GraphNode
{
public:
	Vector2 m_Position;

	GraphNode* m_Prev;
	GraphNode* m_Neighbors[NEIGHBOUR_COUNT];

	int m_Costs[NEIGHBOUR_COUNT];
	int m_GScore;
	int m_HScore;
	int m_FScore;

	int m_IndexX;
	int m_IndexY;

	bool m_Blocked;
};
