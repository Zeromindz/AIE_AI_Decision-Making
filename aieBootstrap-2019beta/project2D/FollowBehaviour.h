#pragma once
#include "IBehaviour.h"

class FollowBehaviour : public IBehaviour
{
public:
	FollowBehaviour(Agent* _target);
	~FollowBehaviour() {}

	void Update(Agent* _agent, float _deltaTime);

private:
	Agent* m_Target;

	float m_ProjectileSpeed = 100;
};

