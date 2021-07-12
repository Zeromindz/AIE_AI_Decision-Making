#include "Agent.h"
#include "IBehaviour.h"



Agent::Agent()
{

}

Agent::Agent(float _posX, float _posY)
{
	SetPostition({_posX, _posY});
}

Agent::~Agent()
{

}

void Agent::Update(float _deltaTime)
{
	m_CurrentBehaviour->Update(this, _deltaTime, m_MovementInfo);

}

void Agent::Draw(aie::Renderer2D* _renderer)
{
	
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
