#pragma once

#include <vector>
#include "GraphNode.h"

using namespace std;

class Heap
{
public:
	Heap();
	~Heap();

	void Push(GraphNode* _value);
	GraphNode* Pop();
	GraphNode* Peek();
	bool Contains(GraphNode* _neighbour);
	int Size();
	void Clear();

private:
	int GetParentIndex(int _index);
	int GetChild1Index(int _index);
	int GetChild2Index(int _index);

	vector<GraphNode*> m_Data;
};

