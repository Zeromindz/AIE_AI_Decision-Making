#pragma once
#include "IBehaviour.h"
#include <vector>

class Pathfinder;

class PathFollowBehaviour : public IBehaviour
{
public:
	PathFollowBehaviour(Pathfinder* _pathfinder, Agent* _target);
	~PathFollowBehaviour() {}

	void Update(Agent* _agent, float _deltaTime, MovementInfo& _behaviour);

private:
	Agent* m_Target;
	Pathfinder* m_Pathfinder;
	std::vector<Vector2> m_Path;
};

