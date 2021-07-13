#include "FollowBehaviour.h"
#include "Agent.h"

FollowBehaviour::FollowBehaviour(Agent* _target)
{
	m_Target = _target;
}

void FollowBehaviour::Update(Agent* _agent, float _deltaTime)
{
	Vector2 target = m_Target->GetPosition();
	Vector2 currentPos = _agent->GetPosition();

	Vector2 direction = target - currentPos;
	direction.Normalize();
	
	Vector2 finalForce = direction.Scale(m_ProjectileSpeed * _deltaTime * 100);
	Vector2 finalVelocity = _agent->GetVelocity() + finalForce.Scale(_deltaTime);
	Vector2 finalPosition = _agent->GetPosition() + finalVelocity.Scale(_deltaTime);

	_agent->AddForce(finalForce);

	_agent->SetVelocity(finalVelocity);
	
	_agent->SetPosition(finalPosition);
	// Reduce speed over time by the friction factor
	_agent->SetVelocity(finalVelocity.Scale(_agent->GetFriction()));


}
