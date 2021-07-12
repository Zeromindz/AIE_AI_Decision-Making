#include "KeyboardBehaviour.h"
#include "Input.h"
#include "Agent.h"

void KeyboardBehaviour::Update(Agent* _agent, float _deltaTime, MovementInfo& _movementInfo)
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
	_movementInfo.m_Velocity = _movementInfo.m_Velocity + force.Scale(_deltaTime);
	// Option 1 --> capped speed
	//m_MovementInfo.m_Velocity = Truncate((GetVelocity() + (m_MovementInfo.m_Force.Scale(_deltaTime))), m_MovementInfo.m_MaxSpeed);

	// Add Velocity multiplied by delta time to Position
	_movementInfo.m_Position = _movementInfo.m_Position + _movementInfo.m_Velocity.Scale(_deltaTime);
	// Reduce speed over time by the friction factor
	_movementInfo.m_Velocity = _movementInfo.m_Velocity.Scale(_movementInfo.m_FrictionModifier);

	//_agent->AddForce(force);
	_movementInfo.m_Force = force;

}