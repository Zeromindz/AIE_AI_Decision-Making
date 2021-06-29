#include "FollowBehaviour.h"
#include "Agent.h"

FollowBehaviour::FollowBehaviour(Agent* _target)
{
	m_Target = _target;
}

void FollowBehaviour::Update(Agent* _agent, float _deltaTime, MovementInfo& _behaviour)
{
	Vector2 target = m_Target->GetPosition();
	Vector2 currentPos = _behaviour.m_Position;

	Vector2 direction = target - currentPos;
	direction.Normalize();

	_behaviour.m_Force = direction.Scale(_behaviour.m_MaxSpeed * _deltaTime * 100);
}
