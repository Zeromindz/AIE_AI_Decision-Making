#pragma once
#include "Behaviour.h"

class SeekBehaviour : public Behaviour
{
public:
	SeekBehaviour();
	virtual ~SeekBehaviour();

	virtual bool Update(Agent* _agent, std::vector<Vector2> _path, float _deltaTime);

private:
	float m_SpeedIncrement = 100.0f;

	Vector2 m_CurrentPos;
	Vector2 m_TargetPos;
};

