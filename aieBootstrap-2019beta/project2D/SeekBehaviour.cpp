#include "SeekBehaviour.h"
#include <vector>
#include "Vector2.h"
#include "Agent.h"

void SeekBehaviour::Update(Agent* _agent, float _deltaTime, std::vector<Vector2> _path, MovementInfo& _movementInfo)
{
	m_Destination = _path[10];
	Vector2 v = m_Destination - _agent->GetPosition();

	if (v.x == 0 && v.y == 0)
	{
		return;
	}

	Vector2 desiredVelocity = v.Normalize().Scale(_agent->GetMaxSpeed());
	Vector2 steeringForce = desiredVelocity - _agent->GetVelocity();

	_agent->AddForce(steeringForce);

	return;
}
