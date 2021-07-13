#include "Agent.h"
#include "IBehaviour.h"

Agent::Agent()
{

}

Agent::Agent(float _posX, float _posY)
{
	SetPosition({ _posX, _posY });
}

Agent::~Agent()
{

}

void Agent::Update(float _deltaTime)
{
	m_CurrentBehaviour->Update(this, _deltaTime);

}

void Agent::Draw(aie::Renderer2D* _renderer)
{
	if (m_CurrentBehaviour)
	{
		m_CurrentBehaviour->DebugDraw(this, _renderer);
	}
	else
	{
		printf("current behaviour is null\n");
	}

}

void Agent::AddBehaviour(IBehaviour* _behaviour)
{
	m_CurrentBehaviour = _behaviour;
	
}

Vector2 Agent::Truncate(Vector2 _v, float _max)
{
	float i = _max / _v.Magnitude();
	i = i < 1.0f ? i : 1.0f;
	return _v.Scale(i);
}
