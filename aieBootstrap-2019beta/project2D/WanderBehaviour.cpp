#include <time.h>
#include "WanderBehaviour.h"
#include "Agent.h"


WanderBehaviour::WanderBehaviour()
{
	srand(time(nullptr));
}

Vector2 WanderBehaviour::SetAngle(Vector2 _vector, float _value)
{
	float length = _vector.Magnitude();
	return { cosf(_value) * length, sinf(_value) * length };
}

void WanderBehaviour::Update(Agent* _agent, float deltaTime)
{
	if (_agent->GetVelocity().Magnitude() == 0)
	{
		_agent->SetVelocity({ 0, -1 });
	}

	// Store move direction
	Vector2 direction = _agent->GetVelocity().Normalize();
	

	// Store an offset vector from the player in direction of velocity
	Vector2 offset = direction.Scale(m_CircleDistance);
	// Store a position circleDistance from the agent, in the same direction as agent's velocity 
	Vector2 circleCenter = _agent->GetPosition() + offset;

	Vector2 displacement = {0, -1};
	displacement = displacement.Scale(m_CircleRadius);
	
	// Randomly change the vector direction by changing its current angle
	displacement = SetAngle(displacement, m_WanderAngle);
	
	// Change wander angle slightly so it wont have the same value next frame
	m_WanderAngle += (rand() % (int)m_AngleChange) - m_AngleChange * 0.5f;
	
	Vector2 wanderForce = circleCenter + displacement;

	_agent->AddForce(wanderForce);

	debug_cirleCenter = circleCenter;
	debug_displacement = displacement;
}

void WanderBehaviour::DebugDraw(Agent* _agent, aie::Renderer2D* _renderer)
{
	_renderer->SetRenderColour(0.0f, 1.0f, 0.0f);
	_renderer->DrawCircle(debug_cirleCenter.x, debug_cirleCenter.y, m_CircleRadius);
	//_renderer->DrawLine(debug_cirleCenter.x, debug_cirleCenter.y, debug_cirleCenter.x + debug_displacement.x, debug_cirleCenter.y + debug_displacement.y);
}

