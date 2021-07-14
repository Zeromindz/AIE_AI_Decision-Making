#include "Boid.h"
#include <math.h>

Boid::Boid(float _x, float _y)
{
	m_Texture = new aie::Texture("Assets/textures/ship.png");
	m_Acceleration = { 0, 0 };

	SetVelocity({ (float)(rand() % 3 - 2), (float)(rand() % 3 - 2) });
	SetPosition({ _x, _y });

	m_MaxSpeed = 10;
	m_MaxForce = 5;
}

Boid::~Boid()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void Boid::ApplyForce(const Vector2 _force)
{
	m_Acceleration.Add(m_Acceleration, _force);
}

void Boid::Update(const std::vector<Boid*>& _v, float _deltaTime)
{
	Flock(_v);

	// Make the slow down not as abrupt
	m_Acceleration.Multiply(.4);
	//Update velocity
	SetVelocity(GetVelocity() + m_Acceleration);

	SetPosition(GetPosition() + GetVelocity());
	//reset acceleraiton to 0 each cycle
	m_Acceleration.Multiply(0.0f);
}

Vector2 Boid::Separation(const std::vector<Boid*>& _boids)
{
	float desiredSeparation = 20;
	Vector2 steer = { 0, 0 };
	int count = 0;

	//For each boid in the system, check if it's too close
	for (int i = 0; i < _boids.size(); i++)
	{
		//Calculate distance from current boid to boid we're looking at
		Vector2 dist = _boids[i]->GetPosition() - GetPosition();
		float d = dist.Magnitude();

		// If this is a fellow boid and it's too close, move away from it
		if (d > 0 && d < desiredSeparation)
		{
			Vector2 diff = { 0, 0 };
			diff = (GetPosition() - _boids[i]->GetPosition()).Normalize();

			// Weight by distance
			diff.x = diff.x / d;
			diff.y = diff.y / d;

			steer.Add(steer, diff);
			count++;
		}
	}
	// Adds average difference of position to acceleration
	if (count > 0)
	{
		steer.x = steer.x / (float)count;
		steer.y = steer.y / (float)count;
	}
	if (steer.Magnitude() > 0)
	{
		// Steering = desired - velocity
		steer.Normalize();
		steer.Multiply(GetMaxSpeed());
		steer = steer - GetVelocity();
	}

	return steer;
}

// Calculates the average velocity of boids in the field of vision and manipulates the velocity of the current boid in order to match it
Vector2 Boid::Alignment(const std::vector<Boid*>& _boids)
{
	// field of vision
	float neighbourDist = 50;

	Vector2 sum = { 0, 0 };
	int count = 0;
	for (int i = 0; i < _boids.size(); i++)
	{
		float d = (_boids[i]->GetPosition() - GetPosition()).Magnitude();

		if (d > 0 && d < neighbourDist)
		{
			sum.Add(sum, _boids[i]->GetVelocity());
			count++;
		}

		// if there are boids close enough for alignment
		if (count > 0)
		{
			// divide sum by the number of close boids (average of velocity)
			sum.x / (float)count;
			sum.y / (float)count;
			sum.Normalize();
			sum.Multiply(GetMaxSpeed());

			Vector2 steer;
			// Steer = desired (average)
			steer = sum - GetVelocity();

			return steer;

		}
		else
		{
			Vector2 temp = { 0, 0 };
			return temp;
		}

	}
}

Vector2 Boid::Cohesion(const std::vector<Boid*>& _boids)
{
	float neighbourDist = 50;
	Vector2 sum = { 0, 0 };

	int count = 0;

	for (int i = 0; i < _boids.size(); i++)
	{
		float d = (_boids[i]->GetPosition() - GetPosition()).Magnitude();
		if (d > 0 && d < neighbourDist)
		{
			sum = sum + _boids[i]->GetPosition();
			count++;
		}
		if (count > 0)
		{
			sum.x = sum.x / count;
			sum.y = sum.y / count;
			return Seek(sum);
		}
		else
		{
			Vector2 temp = { 0, 0 };
			return temp;
		}
	}
}


Vector2 Boid::Seek(const Vector2& _v)
{
	Vector2 desired;
	// Vector pointing from the location to the target
	desired = desired - _v;
	// Normalize desired and scale to max speed;
	desired.Normalize();
	desired.Multiply(GetMaxSpeed());
	// Steering = desired - velocity
	m_Acceleration = desired - GetVelocity();
	
	return m_Acceleration;

}

void Boid::Flock(const std::vector<Boid*>& _v)
{
	Vector2 sep = Separation(_v);
	Vector2 ali = Alignment(_v);
	Vector2 coh = Cohesion(_v);

	// Arbitrary weights
	sep.Multiply(1.5f);
	ali.Multiply(1.0f);
	coh.Multiply(1.0f);

	// Add the force vectors to acceleration
	ApplyForce(sep);
	ApplyForce(ali);
	ApplyForce(coh);
}

void Boid::Draw(aie::Renderer2D* _renderer)
{
	Agent::Draw(_renderer);

	// Calculate normalized movement vector
	Vector2 moveDir = GetVelocity().Normalize();
	// Calculate sprite rotation angle
	float angle = atan2(moveDir.y, moveDir.x) - (3.141592653589793 / 2);

	_renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	_renderer->DrawSprite(m_Texture, GetPosition().x + 30, GetPosition().y - 50, 50, 50, angle);

	_renderer->SetRenderColour(3.0f / 255, 171.0f / 255, 14.0f / 255);
	_renderer->DrawSprite(m_Texture, GetPosition().x, GetPosition().y, 0, 0, angle);

	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
}
