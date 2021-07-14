#include "FollowBehaviour.h"
#include "Agent.h"

#include "DebugNew.h"

FollowBehaviour::FollowBehaviour(Agent* _target)
{
	m_Target = _target;
}

void FollowBehaviour::Update(Agent* _agent, float _deltaTime)
{

	Vector2 direction = (m_Target->GetPosition() - _agent->GetPosition()).Normalize();

	Vector2 finalForce = direction.Scale(m_FollowSpeed * _deltaTime * 100);
	_agent->AddForce(finalForce);

	Vector2 finalVelocity = _agent->GetVelocity() + finalForce.Scale(_deltaTime);
	_agent->SetVelocity(finalVelocity);

	Vector2 finalPosition = _agent->GetPosition() + finalVelocity.Scale(_deltaTime);
	_agent->SetPosition(finalPosition);

	// Reduce speed over time by the friction factor
	_agent->SetVelocity(finalVelocity.Scale(_agent->GetFriction()));


}
