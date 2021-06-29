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
		force.Multiply(3.0f);
	}
	

	_agent->AddForce(force);
}