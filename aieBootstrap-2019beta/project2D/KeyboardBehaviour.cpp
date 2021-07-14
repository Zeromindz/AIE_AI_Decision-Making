#include "KeyboardBehaviour.h"
#include "Input.h"
#include "Agent.h"

#include "DebugNew.h"

void KeyboardBehaviour::Update(Agent* _agent, float _deltaTime)
{
	aie::Input* input = aie::Input::GetInstance();

	Vector2 force = { 0, 0 };

	if (input->IsKeyDown(aie::INPUT_KEY_W))
		force.y = m_SpeedIncrement;
	if (input->IsKeyDown(aie::INPUT_KEY_S))
		force.y = -m_SpeedIncrement;
	if (input->IsKeyDown(aie::INPUT_KEY_A))
		force.x = -m_SpeedIncrement;
	if (input->IsKeyDown(aie::INPUT_KEY_D))
		force.x = m_SpeedIncrement;

	if (input->IsKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
	{
		force.Multiply(m_BoostMultiplier);
	}

	// V = V + (F * t)
	// Option 1 --> super speed
	_agent->SetVelocity(_agent->GetVelocity() + force.Scale(_deltaTime));
	// Option 1 --> capped speed
	//m_MovementInfo.m_Velocity = Truncate((GetVelocity() + (m_MovementInfo.m_Force.Scale(_deltaTime))), m_MovementInfo.m_MaxSpeed);

	// Add Velocity multiplied by delta time to Position
	_agent->SetPosition(_agent->GetPosition() + _agent->GetVelocity().Scale(_deltaTime));
	// Reduce speed over time by the friction factor
	_agent->SetVelocity(_agent->GetVelocity().Scale(_agent->GetFriction()));

	_agent->AddForce(force);

}

void KeyboardBehaviour::DebugDraw(Agent* _agent, aie::Renderer2D* _renderer)
{
	_renderer->SetRenderColour(0.0f, 0.0f, 1.0f);
	// Draw velocity indicator
	_renderer->DrawLine(_agent->GetPosition().x, _agent->GetPosition().y, _agent->GetPosition().x + _agent->GetVelocity().x, _agent->GetPosition().y + _agent->GetVelocity().y);
}

