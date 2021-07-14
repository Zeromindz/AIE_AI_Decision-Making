#pragma once
#include "Agent.h"
#include <vector>
#include "Texture.h"

class Boid : public Agent
{
public:
	Boid() {}
	Boid(float _x, float _y);
	~Boid();

	void ApplyForce(const Vector2 _force);

	void Update(const std::vector<Boid*>& _v, float _deltaTime);

	// If any other boids are within a given distance, computes a vector that distances the current boid from the boids that are too close.
	Vector2 Separation(const std::vector<Boid*>& _boids);
	// Computes a vector that causes the velocity of the current boid to match that of boids that are nearby.
	Vector2 Alignment(const std::vector<Boid*>& _boids);
	// Computes a vector that causes the current boid to seek the center of mass of nearby boids.
	Vector2 Cohesion(const std::vector<Boid*>& _boids);

	Vector2 Seek(const Vector2& _v);

	void Flock(const std::vector<Boid*>& _v);
	
	void Draw(aie::Renderer2D* _renderer);
	
private:
	Vector2 m_Acceleration;

	float m_MaxSpeed;
	float m_MaxForce;

	aie::Texture* m_Texture;

};

