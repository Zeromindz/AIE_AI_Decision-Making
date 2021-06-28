#include "Agent.h"
#include "Behaviour.h"

Agent::Agent()
{
	m_Texture = new aie::Texture("./textures/ship.png");
}

Agent::~Agent()
{
	// Delete the player's sprite.
	delete m_Texture;
	m_Texture = nullptr;
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
	// Draw the player's shadow and sprite.
	renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	renderer->DrawSprite(m_Texture, m_Position.x + 30, m_Position.y - 50);
	renderer->SetRenderColour(0.0f, 0.0f, 1.0f);
	renderer->DrawSprite(m_Texture, m_Position.x, m_Position.y);
}

void Agent::AddBehaviour(Behaviour* _behaviour)
{
	m_BehaviourList.push_back(_behaviour);
}
