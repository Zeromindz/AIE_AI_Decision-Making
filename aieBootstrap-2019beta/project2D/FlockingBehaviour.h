#pragma once
#include "IBehaviour.h"
#include <vector>

class FlockingBehaviour : public IBehaviour
{
public:
	FlockingBehaviour() {}
	~FlockingBehaviour() {}

	void Update(float _deltaTime);

	int GetSize() { return m_Flock.size(); }

	void DebugDraw(Agent* _agent, aie::Renderer2D* _renderer);

private:
	std::vector<Agent*> m_Flock;

};

