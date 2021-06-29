#pragma once
#include "IBehaviour.h"

class FollowBehaviour : public IBehaviour
{
public:
	FollowBehaviour(Agent* _target);
	~FollowBehaviour() {}

	void Update(Agent* _agent, float _deltaTime, MovementInfo& _behaviour);

private:
	Agent* m_Target;

};

