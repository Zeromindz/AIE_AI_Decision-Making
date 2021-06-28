#include "Agent.h"
#include "Behaviour.h"

Agent::Agent()
{
	
}

Agent::~Agent()
{
	
}

void Agent::Update(float _deltaTime)
{
	// Force is equal to zero
	m_Force = { 0, 0 };

	// For each Behaviour in Behaviour list
	for (int i = 0; i < m_BehaviourList.size(); i++)
	{
		// Call the Behaviour’s Update function which will add a value to Force
		m_BehaviourList[i]->Update(this, _deltaTime);
	}

	// Add Force multiplied by delta time to Velocity
	m_Velocity = m_Velocity + m_Force.Scale(_deltaTime);
	// Add Velocity multiplied by delta time to Position
	m_Position = m_Position + m_Velocity.Scale(_deltaTime);
}

void Agent::Draw(aie::Renderer2D* renderer)
{
	
}

void Agent::AddBehaviour(Behaviour* _behaviour)
{
	m_BehaviourList.push_back(_behaviour);
}
