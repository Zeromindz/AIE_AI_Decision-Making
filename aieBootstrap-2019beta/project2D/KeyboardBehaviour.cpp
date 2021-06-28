#include "KeyboardBehaviour.h"
#include "Vector2.h"
#include "Input.h"

KeyboardBehaviour::KeyboardBehaviour()
{
}

KeyboardBehaviour::~KeyboardBehaviour()
{
}

bool KeyboardBehaviour::Update(Agent* _agent, float _deltaTime)
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

	_agent->AddForce(force);

	return true;
}