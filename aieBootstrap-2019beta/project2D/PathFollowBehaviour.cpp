#include "PathFollowBehaviour.h"
#include "PathFinder.h"
#include "Agent.h"

PathFollowBehaviour::PathFollowBehaviour(Pathfinder* _pathfinder, Agent* _target)
{
	m_Pathfinder = _pathfinder;
	m_Target = _target;
}

void PathFollowBehaviour::Update(Agent* _agent, float _deltaTime, MovementInfo& _behaviour)
{
	Vector2 target = m_Target->GetPosition();
	Vector2 currentPos = _behaviour.m_Position;
	// If the path is empty, generate new path
	if (m_Path.size() == 0)
	{
		m_Pathfinder->AStarPath(currentPos, target, m_Path);
	}
	// If the path is greater than 1
	if (m_Path.size() > 1)
	{
		Vector2 destination = m_Path[m_Path.size() - 2];
		Vector2 direction = destination - _behaviour.m_Position;

		float mag = direction.Magnitude();

		if (mag != 0.0f)
		{
			direction.x /= mag;
			direction.y /= mag;
		}

		// Move the actor
		_behaviour.m_Position.x += direction.x * 100 * _deltaTime;
		_behaviour.m_Position.y += direction.y * 100 * _deltaTime;

		// Check if we have arrived at node
		if (mag < 1.0f)
		{
			m_Path.clear();
		}

	}
	else
	{
		m_Path.clear();
	}
}

