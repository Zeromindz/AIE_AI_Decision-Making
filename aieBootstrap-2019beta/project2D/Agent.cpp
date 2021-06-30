#include "Agent.h"
#include "IBehaviour.h"


Agent::Agent()
{

}

Agent::Agent(float _posX, float _posY)
{
	SetPostition({_posX, _posY});
}

Agent::~Agent()
{

}

void Agent::Update(float _deltaTime)
{
	// Force is equal to zero
	m_MovementInfo.m_Force = { 0, 0 };

	// For each Behaviour in Behaviour list
	for (int i = 0; i < m_BehaviourList.size(); i++)
	{
		// Call the Behaviour’s Update function which will add a value to Force
		m_BehaviourList[i]->Update(this, _deltaTime, m_MovementInfo);
	}

	// V = V + (F * t)
	// Option 1 --> super speed
	m_MovementInfo.m_Velocity = m_MovementInfo.m_Velocity + m_MovementInfo.m_Force.Scale(_deltaTime);
	// Option 1 --> capped speed
	//m_MovementInfo.m_Velocity = Truncate((GetVelocity() + (m_MovementInfo.m_Force.Scale(_deltaTime))), m_MovementInfo.m_MaxSpeed);

	// Add Velocity multiplied by delta time to Position
	m_MovementInfo.m_Position = m_MovementInfo.m_Position + m_MovementInfo.m_Velocity.Scale(_deltaTime);
	// Reduce speed over time by the friction factor
	m_MovementInfo.m_Velocity = m_MovementInfo.m_Velocity.Scale(m_MovementInfo.m_FrictionModifier);
}

void Agent::Draw(aie::Renderer2D* _renderer)
{
	
}

void Agent::AddBehaviour(IBehaviour* _behaviour)
{
	m_BehaviourList.push_back(_behaviour);
}

Vector2 Agent::Truncate(Vector2 _v, float _max)
{
	float i = _max / _v.Magnitude();
	i = i < 1.0f ? i : 1.0f;
	return _v.Scale(i);
}
