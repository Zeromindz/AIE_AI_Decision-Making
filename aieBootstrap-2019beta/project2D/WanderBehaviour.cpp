#include <time.h>
#include "WanderBehaviour.h"
#include "Agent.h"


WanderBehaviour::WanderBehaviour()
{
	srand(time(nullptr));
}

void WanderBehaviour::Update(Agent* _agent, float deltaTime, MovementInfo& _behaviour)
{
	// Store velocity
	Vector2 velocity = _agent->GetVelocity();
	if (velocity.Magnitude() == 0)
	{
		velocity = { 0, -1 };
	}

	// Calculate circle center
	// m_circleDistance from the current agent position, in the same direction as the current velocity
	Vector2 circleCenter = velocity.Normalize().Scale(m_CircleDistance);
	//Vector2 circleCenter = {0, 0};

	Vector2 displacement = {0, -1};
	displacement = displacement.Scale(m_CircleRadius);

	// Randomly change the vector direction by changing its current angle
	displacement = SetAngle(displacement, m_WanderAngle);

	// change wander angle just a bit so it wont have the same value next frame
	m_WanderAngle += (rand() % (int)m_AngleChange) - m_AngleChange * 0.5f;

	//debug_cirleCenter = _agent->GetPosition() + circleCenter;
	//debug_displacement = displacement;

	Vector2 wanderForce = circleCenter + displacement;
	_agent->AddForce(wanderForce);

}

//void WanderBehaviour::Draw(Agent* _agent)
//{
//	_renderer.DrawCircle(debug_cirleCenter.x, debug_cirleCenter.y, m_CircleRadius);
//	_renderer.DrawLine(debug_cirleCenter.x, debug_cirleCenter.y, debug_cirleCenter.x + debug_displacement.x, debug_cirleCenter.y + debug_displacement.y);
//}

Vector2 WanderBehaviour::SetAngle(Vector2 _vector, float _value)
{
	float length = _vector.Magnitude();
	return { cosf(_value) * length, sinf(_value) * length };
}
