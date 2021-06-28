#include "SeekBehaviour.h"

SeekBehaviour::SeekBehaviour()
{
	m_CurrentPos = { 0, 0 }; 
	m_TargetPos = { 0, 0 };
}

SeekBehaviour::~SeekBehaviour()
{
}

bool SeekBehaviour::Update(Agent* _agent, std::vector<Vector2> path, float _deltaTime)
{
	Vector2 force = {0, 0};
	Vector2 currentPos = _agent->GetPosition();
	for (int i = 0; i < path.size(); i++)
	{
		Vector2 targetPos = path[i];
	}

	force = (m_TargetPos - currentPos).Scale(m_SpeedIncrement);
	_agent->AddForce(force);

	return true;
}
