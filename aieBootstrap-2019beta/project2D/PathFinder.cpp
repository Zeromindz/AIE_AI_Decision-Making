#include "Pathfinder.h"
#include "Heap.h"

#define NODE_SIZE 22
#define NODE_DRAW_SIZE 20

Pathfinder::Pathfinder()
{
	// Create all nodes and initialize their variables
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			m_Nodes[x][y] = new GraphNode();

			m_Nodes[x][y]->m_IndexX = x;
			m_Nodes[x][y]->m_IndexY = y;


			m_Nodes[x][y]->m_Position.x = (float)(x * NODE_SIZE);
			m_Nodes[x][y]->m_Position.y = (float)(y * NODE_SIZE);

			m_Nodes[x][y]->m_Prev = nullptr;
			m_Nodes[x][y]->m_GScore = 0;
			m_Nodes[x][y]->m_HScore = 0;
			m_Nodes[x][y]->m_FScore = 0;

			m_Nodes[x][y]->m_Blocked = false;

			if (x == GRID_SIZE / 2)
			{
				m_Nodes[x][y]->m_Blocked = false;
			}
		}
	}
	// Connect nodes to their neighbours
	// 
	// [ ] [ ] [ ]
	// [ ] [X] [ ]
	// [ ] [ ] [ ] 
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
			{
				m_Nodes[x][y]->m_Neighbors[n] = GetNeighbour(x, y, n);

				if (n == 0 || n == 2 || n == 5 || n == 7)
				{
					m_Nodes[x][y]->m_Costs[n] = 14;
				}
				else
				{
					m_Nodes[x][y]->m_Costs[n] = 10;
				}
			}
		}
	}
}

Pathfinder::~Pathfinder()
{
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			delete m_Nodes[x][y];
			m_Nodes[x][y] = nullptr;
		}
	}
}

//==========================================================================================|
//
// A* Pathfinding
//________________________________________________________________________________________/
bool Pathfinder::AStarPath(Vector2 _start, Vector2 _end, std::vector<Vector2>& _finalPath)
{
	_finalPath.clear();
	GraphNode* start = GetNodeByPos(_start);
	GraphNode* end = GetNodeByPos(_end);


	if (start == nullptr)
		return false;
	if (end == nullptr)
		return false;
	if (end->m_Blocked)
		return false;

	if (start == end)
	{
		_finalPath.push_back(end->m_Position);
		return true;
	}

	// Setup
	m_OpenListHeap.Clear();
	memset(m_ClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	//reset the node
	start->m_GScore = 0;
	start->m_HScore = 0;
	start->m_FScore = 0;
	start->m_Prev = nullptr;
	m_OpenListHeap.Push(start);

	//The algorithm
	while (m_OpenListHeap.Size() > 0)
	{
		GraphNode* current = m_OpenListHeap.Pop();

		// Add current to closed list
		m_ClosedList[current->m_IndexX][current->m_IndexY] = true;

		// If we've just added the end node to the list, then the path has been found
		if (current == end)
		{
			_finalPath.push_back(current->m_Position);
			while (current->m_Prev != nullptr)
			{
				current = current->m_Prev;
				_finalPath.push_back(current->m_Position);
			}
			return true;
		}
		// Process all neighbours
		for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
		{
			// Get neighbour
			GraphNode* neighbour = current->m_Neighbors[n];
			// Sanity checks
			if (neighbour == nullptr) // edge of map
				continue;
			if (neighbour->m_Blocked) // dont walk through walls
				continue;
			if (m_ClosedList[neighbour->m_IndexX][neighbour->m_IndexY]) //neighbour already in closed list
				continue;

			if (m_OpenListHeap.Contains(neighbour))
			{
				// Neighbour exists in the open list
				int newG = current->m_GScore + current->m_Costs[n];

				if (newG < neighbour->m_GScore)
				{
					// We found a cheaper path
					neighbour->m_GScore = newG;
					neighbour->m_FScore = neighbour->m_GScore + neighbour->m_HScore;
					neighbour->m_Prev = current;
				}
			}
			else
			{
				// Calculate move costs
				neighbour->m_GScore = current->m_GScore + current->m_Costs[n];
				neighbour->m_HScore = GetHeuristic(neighbour, end); // Put heuristic here
				neighbour->m_FScore = neighbour->m_GScore + neighbour->m_HScore;
				neighbour->m_Prev = current;
				m_OpenListHeap.Push(neighbour);

			}
		}
	}
	// Out of nodes, didnt find the path
	return false;
}

bool Pathfinder::CalculateDijkstraPath(Vector2 _start, Vector2 _end, std::vector<Vector2>& _finalPath)
{
	_finalPath.clear();
	GraphNode* start = GetNodeByPos(_start);
	GraphNode* end = GetNodeByPos(_end);


	if (start == nullptr)
		return false;
	if (end == nullptr)
		return false;
	if (end->m_Blocked)
		return false;

	if (start == end)
	{
		_finalPath.push_back(end->m_Position);
		return true;
	}

	// Setup
	m_OpenListHeap.Clear();
	memset(m_ClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	//reset the node
	start->m_GScore = 0;
	start->m_Prev = nullptr;
	m_OpenListHeap.Push(start);

	//The algorithm
	while (m_OpenListHeap.Size() > 0)
	{
		GraphNode* current = m_OpenListHeap.Pop();

		// Add current to closed list
		m_ClosedList[current->m_IndexX][current->m_IndexY] = true;

		// If we've just added the end node to the list, then the path has been found
		if (current == end)
		{
			_finalPath.push_back(current->m_Position);
			while (current->m_Prev != nullptr)
			{
				current = current->m_Prev;
				_finalPath.push_back(current->m_Position);
			}
			return true;
		}
		// Process all neighbours
		for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
		{
			// Get neighbour
			GraphNode* neighbour = current->m_Neighbors[n];
			// Sanity checks
			if (neighbour == nullptr) // edge of map
				continue;
			if (neighbour->m_Blocked) // dont walk through walls
				continue;
			if (m_ClosedList[neighbour->m_IndexX][neighbour->m_IndexY]) //neighbour already in closed list
				continue;

			if (m_OpenListHeap.Contains(neighbour))
			{
				// Neighbour exists in the open list
				int newG = current->m_GScore + current->m_Costs[n];
				if (newG < neighbour->m_GScore)
				{
					neighbour->m_GScore = newG;
					neighbour->m_Prev = current;
				}
			}
			else
			{
				// Calculate move costs
				neighbour->m_GScore = current->m_GScore + current->m_Costs[n];
				neighbour->m_Prev = current;
				m_OpenListHeap.Push(neighbour);

			}
		}
	}

	// Out of nodes, didnt find the path
	return false;
}

GraphNode* Pathfinder::GetNodeByPos(Vector2 _pos)
{
	int x = (int)((_pos.x / NODE_SIZE) + 0.5f);
	int y = (int)((_pos.y / NODE_SIZE) + 0.5f);

	if (x < 0 || x >= GRID_SIZE)
		return nullptr;
	if (y < 0 || y >= GRID_SIZE)
		return nullptr;

	return m_Nodes[x][y];
}

GraphNode* Pathfinder::GetNeighbour(int _currentX, int _currentY, int _neighbour)
{
	int x = _currentX;
	int y = _currentY;

	switch (_neighbour)
	{
	case 0: --x; --y; break;
	case 1:      --y; break;
	case 2: ++x; --y; break;
	case 3: --x;      break;
	case 4: ++x;      break;
	case 5: --x; ++y; break;
	case 6:      ++y; break;
	case 7: ++x; ++y; break;
	}

	if (x < 0 || x >= GRID_SIZE)
		return nullptr;
	if (y < 0 || y >= GRID_SIZE)
		return nullptr;

	return m_Nodes[x][y];
}

int Pathfinder::GetHeuristic(GraphNode* neighbour, GraphNode* _end)
{
	int dx = abs(neighbour->m_IndexX - _end->m_IndexX);
	int dy = abs(neighbour->m_IndexY - _end->m_IndexY);

	if (dx > dy)
	{
		return (14 * dy) + 10 * (dx - dy);
	}
	else
	{
		return (14 * dx) + 10 * (dy - dx);
	}
}

void Pathfinder::Render(aie::Renderer2D* _renderer)
{
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			// Draw nodes
			GraphNode* node = m_Nodes[x][y];
			if (node->m_Blocked)
			{
				_renderer->SetRenderColour(2.0f / 255, 80.0f / 255, 147.0f / 255); // Walls - Blue
			}
			else 
			{
				if (m_ClosedList[x][y])
				{
					float i = x;
					_renderer->SetRenderColour((60 + i) / 255, (200 + i) / 255, (19 + i) / 255); // Searched nodes - Red
				}
				else
				{
					_renderer->SetRenderColour(38.0f / 255, 38.0f / 255, 38.0f / 255); // Default ground - White
				}
			}

			// Draw cells
			_renderer->DrawBox(node->m_Position.x, node->m_Position.y, NODE_DRAW_SIZE, NODE_DRAW_SIZE);

			// Draw connections
			_renderer->SetRenderColour(0.0f, 1.0f, 0.0f, 0.1f); // Green
			for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
			{
				GraphNode* neighbour = node->m_Neighbors[n];
				if (neighbour)
				{
					//_renderer->DrawLine(node->m_Position.x, node->m_Position.y, neighbour->m_Position.x, neighbour->m_Position.y);
				}
			}
		}
	}
	// Reset colour back to default
	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f); // White
}

