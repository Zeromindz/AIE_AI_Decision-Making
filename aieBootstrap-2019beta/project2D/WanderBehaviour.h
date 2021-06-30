#pragma once
#include "IBehaviour.h"
#include "Renderer2D.h"

class WanderBehaviour : public IBehaviour 
{
public:
	WanderBehaviour();
	virtual ~WanderBehaviour() {}

	virtual void Update(Agent* _agent, float deltaTime, MovementInfo& _behaviour);
	
	//void Draw(Agent* _agent, aie::Renderer2D _renderer);

private: 
	Vector2 SetAngle(Vector2 _vector, float _value);

	float m_CircleDistance = 60;
	float m_CircleRadius = 500;
	float m_WanderAngle = 0;

	const float m_AngleChange = 100;

	// Debug
	//Vector2 debug_cirleCenter;
	//Vector2 debug_displacement;
};

