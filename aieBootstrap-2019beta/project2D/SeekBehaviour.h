#pragma once
#include "IBehaviour.h"

class SeekBehaviour : public IBehaviour
{
public:
	SeekBehaviour() {}
	virtual ~SeekBehaviour() {}

	//bool Update(Agent* _agent, std::vector<Vector2> _path, float _deltaTime);
	void Update(Agent* _agent, float _deltaTime, std::vector<Vector2> path);
	void SetDestination(Vector2 _dest) { m_Destination = _dest; }

private:

	Vector2 m_Destination;
};

