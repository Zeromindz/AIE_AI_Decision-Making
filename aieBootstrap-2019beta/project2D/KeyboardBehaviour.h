#pragma once
#include "IBehaviour.h"

class KeyboardBehaviour : public IBehaviour
{
public:
	KeyboardBehaviour() { }
	virtual ~KeyboardBehaviour() {}

	void Update(Agent* _agent, float _deltaTime);
	void DebugDraw(Agent* _agent, aie::Renderer2D* _renderer);

private:
	float m_SpeedIncrement = 200.0f;
	float m_BoostMultiplier = 3.0f;
};

