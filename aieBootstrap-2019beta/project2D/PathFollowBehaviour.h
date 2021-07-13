#pragma once
#include "IBehaviour.h"
#include <vector>

class Pathfinder;

class PathFollowBehaviour : public IBehaviour
{
public:
	PathFollowBehaviour(Agent* _target, Pathfinder* _pathfinder);
	~PathFollowBehaviour() {}

	void Update(Agent* _agent, float _deltaTime);
	void DebugDraw(Agent* _agent, aie::Renderer2D* _renderer);

private:
	Agent* m_Target;
	Pathfinder* m_Pathfinder;
	std::vector<Vector2> m_Path;
};

