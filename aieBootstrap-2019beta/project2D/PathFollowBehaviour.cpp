#include "PathFollowBehaviour.h"
#include "PathFinder.h"
#include "Agent.h"


PathFollowBehaviour::PathFollowBehaviour(Agent* _target, Pathfinder* _pathfinder)
{
	m_Pathfinder = _pathfinder;
	m_Target = _target;
}

void PathFollowBehaviour::Update(Agent* _agent, float _deltaTime)
{
	Vector2 target = m_Target->GetPosition();

	Vector2 currentPos = _agent->GetPosition();
	// If the path is empty, generate new path
	if (m_Path.size() == 0)
	{
		m_Pathfinder->AStarPath(currentPos, target, m_Path);
	}
	// If the path is greater than 1
	if (m_Path.size() > 1)
	{
		Vector2 destination = m_Path[m_Path.size() - 2];
		Vector2 direction = destination - _agent->GetPosition();

		float mag = direction.Magnitude();

		if (mag != 0.0f)
		{
			direction.x /= mag;
			direction.y /= mag;
		}

		// Move the actor
		float x = _agent->GetPosition().x + direction.x * 100 * _deltaTime;
		float y = _agent->GetPosition().y + direction.y * 100 * _deltaTime;

		_agent->SetPosition({ x, y });

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

void PathFollowBehaviour::DebugDraw(Agent* _agent, aie::Renderer2D* _renderer)
{
	Vector2 startPos = _agent->GetPosition();
	Vector2 endPos = m_Target->GetPosition();
	
	GraphNode* startNode = m_Pathfinder->GetNodeByPos(startPos);
	GraphNode* endNode = m_Pathfinder->GetNodeByPos(endPos);
	
	// Draw Path
	_renderer->SetRenderColour(0.5f, 0.0f, 0.0f);
	for (int i = 0; i < m_Path.size(); ++i)
	{
		if (i + 1 < m_Path.size())
		{
			_renderer->DrawLine(m_Path[i].x, m_Path[i].y, m_Path[i + 1].x, m_Path[i + 1].y, 6.0f);
	
		}
	}

}

