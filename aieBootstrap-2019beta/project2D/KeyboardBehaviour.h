#pragma once
#include "IBehaviour.h"

class KeyboardBehaviour : public IBehaviour
{
public:
	KeyboardBehaviour() {}
	virtual ~KeyboardBehaviour() {}

	void Update(Agent* _agent, float _deltaTime, MovementInfo &_movementInfo);

private:
	float m_SpeedIncrement = 200.0f;
	float m_BoostMultiplier = 3.0f;
};

