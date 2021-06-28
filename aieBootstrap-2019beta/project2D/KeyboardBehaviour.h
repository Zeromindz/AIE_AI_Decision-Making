#pragma once
#include "Behaviour.h"

class KeyboardBehaviour : public Behaviour
{
public:
	KeyboardBehaviour();
	virtual ~KeyboardBehaviour();

	virtual bool Update(Agent* _agent, float _deltaTime);

private:
	float m_SpeedIncrement = 200.0f;

};

